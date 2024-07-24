/*
 * Copyright (c) 2023 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <string.h>

#include "pico/stdlib.h"
#include "pico/error.h"

#include "hardware/dma.h"
#include "hardware/clocks.h"

#include "wiznet_spi_pio.h"

#include "wiznet_spi_pio.pio.h"



#ifndef PIO_SPI_PREFERRED_PIO
#define PIO_SPI_PREFERRED_PIO 1
#endif

#define PADS_DRIVE_STRENGTH PADS_BANK0_GPIO0_DRIVE_VALUE_12MA
#define IRQ_SAMPLE_DELAY_NS 100

#define SPI_PROGRAM_NAME wiznet_spi_write_read
#define SPI_PROGRAM_FUNC __CONCAT(SPI_PROGRAM_NAME, _program)
#define SPI_PROGRAM_GET_DEFAULT_CONFIG_FUNC __CONCAT(SPI_PROGRAM_NAME, _program_get_default_config)
#define SPI_OFFSET_WRITE_BITS __CONCAT(SPI_PROGRAM_NAME, _offset_write_bits)
#define SPI_OFFSET_WRITE_END __CONCAT(SPI_PROGRAM_NAME, _offset_write_end)
#define SPI_OFFSET_READ_END __CONCAT(SPI_PROGRAM_NAME, _offset_read_end)

//#define ENABLE_SPI_DUMPING 1
#define ENABLE_SPI_DUMPING 0

#if ENABLE_SPI_DUMPING
static uint32_t counter = 0;
#define DUMP_SPI_TRANSACTIONS(A) A
#else
#define DUMP_SPI_TRANSACTIONS(A)
#endif


// All wiznet spi operations must start with writing a 3 byte header
#define SPI_HEADER_LEN 3

// First byte of wiznet header indicates read or write
#define WIZNET_CONTROL_READ 0x0F
#define WIZNET_CONTROL_WRITE 0xF0

#ifndef PICO_WIZNET_SPI_PIO_INSTANCE_COUNT
#define PICO_WIZNET_SPI_PIO_INSTANCE_COUNT 1
#endif

typedef struct spi_pio_state {
    wiznet_spi_funcs_t *funcs;
    const wiznet_spi_config_t *spi_config;
    pio_hw_t *pio;
    uint8_t pio_func_sel;
    int8_t pio_offset;
    int8_t pio_sm;
    int8_t dma_out;
    int8_t dma_in;
    uint8_t spi_header[SPI_HEADER_LEN];
    uint8_t spi_header_count;
} spi_pio_state_t;
static spi_pio_state_t spi_pio_state[PICO_WIZNET_SPI_PIO_INSTANCE_COUNT];
static spi_pio_state_t *active_state;

static void wiznet_spi_pio_close(wiznet_spi_handle_t funcs);
static wiznet_spi_funcs_t *get_wiznet_spi_pio_impl(void);

// Initialise our gpios
static void pio_spi_gpio_setup(spi_pio_state_t *state) {

    // Setup MOSI, MISO and IRQ
    gpio_init(state->spi_config->data_out_pin);
    gpio_set_dir(state->spi_config->data_out_pin, GPIO_OUT);
    gpio_put(state->spi_config->data_out_pin, false);

    // Setup CS
    gpio_init(state->spi_config->cs_pin);
    gpio_set_dir(state->spi_config->cs_pin, GPIO_OUT);
    gpio_put(state->spi_config->cs_pin, true);

    // Setup IRQ
    gpio_init(state->spi_config->irq_pin);
    gpio_set_dir(state->spi_config->irq_pin, GPIO_IN);
    gpio_set_pulls(state->spi_config->irq_pin, false, false);
}

wiznet_spi_handle_t wiznet_spi_pio_open(const wiznet_spi_config_t *spi_config) {
    spi_pio_state_t *state;
    for(int i = 0; i < count_of(spi_pio_state); i++) {
        if (!spi_pio_state[i].funcs) {
            state = &spi_pio_state[i];
            break;
        }
    }
    assert(state);
    if (!state) return NULL;
    state->spi_config = spi_config;
    state->funcs = get_wiznet_spi_pio_impl();

    pio_spi_gpio_setup(state);

    pio_hw_t *pios[2] = {pio0, pio1};
    uint pio_index = PIO_SPI_PREFERRED_PIO;

    if (!pio_can_add_program(pios[pio_index], &SPI_PROGRAM_FUNC)) {
        pio_index ^= 1;
        if (!pio_can_add_program(pios[pio_index], &SPI_PROGRAM_FUNC)) {
            return NULL;
        }
    }

    state->pio = pios[pio_index];
    state->dma_in = -1;
    state->dma_out = -1;

    static_assert(GPIO_FUNC_PIO1 == GPIO_FUNC_PIO0 + 1, "");
    state->pio_func_sel = GPIO_FUNC_PIO0 + pio_index;
    state->pio_sm = (int8_t)pio_claim_unused_sm(state->pio, false);
    if (state->pio_sm < 0) {
        wiznet_spi_pio_close(&state->funcs);
        return NULL;
    }

    state->pio_offset = pio_add_program(state->pio, &SPI_PROGRAM_FUNC);    

    pio_sm_config sm_config = SPI_PROGRAM_GET_DEFAULT_CONFIG_FUNC(state->pio_offset);

    sm_config_set_clkdiv_int_frac(&sm_config, state->spi_config->clock_div_major, state->spi_config->clock_div_minor);
    hw_write_masked(&padsbank0_hw->io[state->spi_config->clock_pin],
                    (uint)PADS_DRIVE_STRENGTH << PADS_BANK0_GPIO0_DRIVE_LSB,
                    PADS_BANK0_GPIO0_DRIVE_BITS
    );
    hw_write_masked(&padsbank0_hw->io[state->spi_config->clock_pin],
                    (uint)1 << PADS_BANK0_GPIO0_SLEWFAST_LSB,
                    PADS_BANK0_GPIO0_SLEWFAST_BITS
    );

    sm_config_set_out_pins(&sm_config, state->spi_config->data_out_pin, 1);
    sm_config_set_in_pins(&sm_config, state->spi_config->data_in_pin);
    sm_config_set_set_pins(&sm_config, state->spi_config->data_out_pin, 1);
    sm_config_set_sideset(&sm_config, 1, false, false);
    sm_config_set_sideset_pins(&sm_config, state->spi_config->clock_pin);

    sm_config_set_in_shift(&sm_config, false, true, 8);
    sm_config_set_out_shift(&sm_config, false, true, 8);
    hw_set_bits(&state->pio->input_sync_bypass, 1u << state->spi_config->data_in_pin);
    pio_sm_set_config(state->pio, state->pio_sm, &sm_config);
    pio_sm_set_consecutive_pindirs(state->pio, state->pio_sm, state->spi_config->clock_pin, 1, true);
    gpio_set_function(state->spi_config->data_out_pin, state->pio_func_sel);
    gpio_set_function(state->spi_config->clock_pin, state->pio_func_sel);

    // Set data pin to pull down and schmitt
    gpio_set_pulls(state->spi_config->data_in_pin, false, true);
    gpio_set_input_hysteresis_enabled(state->spi_config->data_in_pin, true);

    pio_sm_exec(state->pio, state->pio_sm, pio_encode_set(pio_pins, 1));

    state->dma_out = (int8_t) dma_claim_unused_channel(false); // todo: Should be able to use one dma channel?
    state->dma_in = (int8_t) dma_claim_unused_channel(false);
    if (state->dma_out < 0 || state->dma_in < 0) {
        wiznet_spi_pio_close(&state->funcs);
        return NULL;
    }
    return &state->funcs;
}

static void wiznet_spi_pio_close(wiznet_spi_handle_t handle) {
    spi_pio_state_t *state = (spi_pio_state_t *)handle;
    if (state) {
        if (state->pio_sm >= 0) {
            if (state->pio_offset != -1)
                pio_remove_program(state->pio, &SPI_PROGRAM_FUNC, state->pio_offset);

            pio_sm_unclaim(state->pio, state->pio_sm);
        }
        if (state->dma_out >= 0) {
            dma_channel_unclaim(state->dma_out);
            state->dma_out = -1;
        }
        if (state->dma_in >= 0) {
            dma_channel_unclaim(state->dma_in);
            state->dma_in = -1;
        }
        state->funcs = NULL;
    }
}

static void cs_set(spi_pio_state_t *state, bool value) {
    gpio_put(state->spi_config->cs_pin, value);
}

static __noinline void ns_delay(uint32_t ns) {
    // cycles = ns * clk_sys_hz / 1,000,000,000
    uint32_t cycles = ns * (clock_get_hz(clk_sys) >> 16u) / (1000000000u >> 16u);
    busy_wait_at_least_cycles(cycles);
}

static void wiznet_spi_pio_frame_start(void) {
    assert(active_state);

    gpio_set_function(active_state->spi_config->data_out_pin, active_state->pio_func_sel);
    gpio_set_function(active_state->spi_config->clock_pin, active_state->pio_func_sel);
    gpio_pull_down(active_state->spi_config->clock_pin);

    // Pull CS low
    cs_set(active_state, false);
}

static void wiznet_spi_pio_frame_end(void) {
    assert(active_state);

    // from this point a positive edge will cause an IRQ to be pending
    cs_set(active_state, true);

    // we need to wait a bit in case the irq line is incorrectly high
#ifdef IRQ_SAMPLE_DELAY_NS
    ns_delay(IRQ_SAMPLE_DELAY_NS);
#endif
}

#if ENABLE_SPI_DUMPING
static void dump_bytes(const uint8_t *bptr, uint32_t len) {
    unsigned int i = 0;

    for (i = 0; i < len;) {
        if ((i & 0x0f) == 0) {
            printf("\n");
        } else if ((i & 0x07) == 0) {
            printf(" ");
        }
        printf("%02x ", bptr[i++]);
    }
    printf("\n");
}
#endif

// send tx then receive rx
// rx can be null if you just want to send, but tx and tx_length must be valid
static bool pio_spi_transfer(spi_pio_state_t *state, const uint8_t *tx, size_t tx_length, uint8_t *rx, size_t rx_length) {
    assert(state);
    if (!state || (tx == NULL)) {
        return false;
    }

    if (rx != NULL && tx != NULL) {    
        assert(tx && tx_length && rx_length);
        DUMP_SPI_TRANSACTIONS(
                printf("[%lu] bus TX/RX %u bytes rx %u:", counter++, tx_length, rx_length);
                dump_bytes(tx, tx_length);
        )

        pio_sm_set_enabled(state->pio, state->pio_sm, false); // disable sm
        pio_sm_set_wrap(state->pio, state->pio_sm, state->pio_offset + SPI_OFFSET_WRITE_BITS, state->pio_offset + SPI_OFFSET_READ_END - 1); 
        pio_sm_clear_fifos(state->pio, state->pio_sm); // clear fifos from previous run
        pio_sm_set_pindirs_with_mask(state->pio, state->pio_sm, 1u << state->spi_config->data_out_pin, 1u << state->spi_config->data_out_pin);
        pio_sm_restart(state->pio, state->pio_sm);
        pio_sm_clkdiv_restart(state->pio, state->pio_sm);
        pio_sm_put(state->pio, state->pio_sm, tx_length * 8 - 1); // set x
        pio_sm_exec(state->pio, state->pio_sm, pio_encode_out(pio_x, 32));
        pio_sm_put(state->pio, state->pio_sm, rx_length - 1); // set y
        pio_sm_exec(state->pio, state->pio_sm, pio_encode_out(pio_y, 32));
        pio_sm_exec(state->pio, state->pio_sm, pio_encode_jmp(state->pio_offset)); // setup pc
        dma_channel_abort(state->dma_out);
        dma_channel_abort(state->dma_in);

        dma_channel_config out_config = dma_channel_get_default_config(state->dma_out);
        channel_config_set_dreq(&out_config, pio_get_dreq(state->pio, state->pio_sm, true));
        channel_config_set_transfer_data_size(&out_config, DMA_SIZE_8);
        dma_channel_configure(state->dma_out, &out_config, &state->pio->txf[state->pio_sm], tx, tx_length, true);

        dma_channel_config in_config = dma_channel_get_default_config(state->dma_in);
        channel_config_set_dreq(&in_config, pio_get_dreq(state->pio, state->pio_sm, false));
        channel_config_set_write_increment(&in_config, true);
        channel_config_set_read_increment(&in_config, false);
        channel_config_set_transfer_data_size(&in_config, DMA_SIZE_8);
        dma_channel_configure(state->dma_in, &in_config, rx, &state->pio->rxf[state->pio_sm], rx_length, true);

        pio_sm_set_enabled(state->pio, state->pio_sm, true);
        __compiler_memory_barrier();

        dma_channel_wait_for_finish_blocking(state->dma_out);
        dma_channel_wait_for_finish_blocking(state->dma_in);

        __compiler_memory_barrier();
    } else if (tx != NULL) {
        assert(tx_length);
        DUMP_SPI_TRANSACTIONS(
                printf("[%lu] bus TX only %u bytes:", counter++, tx_length);
                dump_bytes(tx, tx_length);
        )
        pio_sm_set_enabled(state->pio, state->pio_sm, false);
        pio_sm_set_wrap(state->pio, state->pio_sm, state->pio_offset + SPI_OFFSET_WRITE_BITS, state->pio_offset + SPI_OFFSET_WRITE_END - 1);
        pio_sm_clear_fifos(state->pio, state->pio_sm);
        pio_sm_restart(state->pio, state->pio_sm);
        pio_sm_clkdiv_restart(state->pio, state->pio_sm);
        pio_sm_put(state->pio, state->pio_sm, tx_length * 8 - 1);
        pio_sm_exec(state->pio, state->pio_sm, pio_encode_out(pio_x, 32));
        pio_sm_put(state->pio, state->pio_sm, tx_length - 1);
        pio_sm_exec(state->pio, state->pio_sm, pio_encode_out(pio_y, 32));
        pio_sm_exec(state->pio, state->pio_sm, pio_encode_set(pio_pins, 0));
        pio_sm_set_consecutive_pindirs(state->pio, state->pio_sm, state->spi_config->data_out_pin, 1, true);
        pio_sm_exec(state->pio, state->pio_sm, pio_encode_jmp(state->pio_offset + SPI_OFFSET_WRITE_BITS));
        dma_channel_abort(state->dma_out);

        dma_channel_config out_config = dma_channel_get_default_config(state->dma_out);
        channel_config_set_dreq(&out_config, pio_get_dreq(state->pio, state->pio_sm, true));

        channel_config_set_transfer_data_size(&out_config, DMA_SIZE_8);
        dma_channel_configure(state->dma_out, &out_config, &state->pio->txf[state->pio_sm], tx, tx_length, true);

        const uint32_t fDebugTxStall = 1u << (PIO_FDEBUG_TXSTALL_LSB + state->pio_sm);
        state->pio->fdebug = fDebugTxStall;
        pio_sm_set_enabled(state->pio, state->pio_sm, true);
        while (!(state->pio->fdebug & fDebugTxStall)) {
            tight_loop_contents(); // todo timeout
        }
        __compiler_memory_barrier();
        pio_sm_set_enabled(state->pio, state->pio_sm, false);
        pio_sm_set_consecutive_pindirs(state->pio, state->pio_sm, state->spi_config->data_in_pin, 1, false);
    } else if (rx != NULL) {
        panic_unsupported(); // shouldn't be used
#if 0
        assert(rx_length);
        DUMP_SPI_TRANSACTIONS(
                printf("[%lu] bus RX only %u bytes:\n", counter++, rx_length);
        )
        pio_sm_set_enabled(state->pio, state->pio_sm, false); // disable sm
        pio_sm_set_wrap(state->pio, state->pio_sm, state->pio_offset + SPI_OFFSET_WRITE_BITS, state->pio_offset + SPI_OFFSET_READ_END - 1);  // stall on write at the end of the read
        pio_sm_clear_fifos(state->pio, state->pio_sm); // clear fifos from previous run
        pio_sm_restart(state->pio, state->pio_sm);
        pio_sm_clkdiv_restart(state->pio, state->pio_sm);
        pio_sm_put(state->pio, state->pio_sm, rx_length - 1);
        pio_sm_exec(state->pio, state->pio_sm, pio_encode_out(pio_y, 32)); // y is bytes to be read
        pio_sm_exec(state->pio, state->pio_sm, pio_encode_jmp(state->pio_offset + SPI_OFFSET_READ_BYTE)); // setup pc
        dma_channel_abort(state->dma_in);

        dma_channel_config in_config = dma_channel_get_default_config(state->dma_in);
        channel_config_set_dreq(&in_config, pio_get_dreq(state->pio, state->pio_sm, false));
        channel_config_set_write_increment(&in_config, true);
        channel_config_set_read_increment(&in_config, false);
        channel_config_set_transfer_data_size(&in_config, DMA_SIZE_8);
        dma_channel_configure(state->dma_in, &in_config, rx, &state->pio->rxf[state->pio_sm], rx_length, true);

        pio_sm_set_enabled(state->pio, state->pio_sm, true);
        __compiler_memory_barrier();

        dma_channel_wait_for_finish_blocking(state->dma_in);

        __compiler_memory_barrier();
#endif
    }
    pio_sm_exec(state->pio, state->pio_sm, pio_encode_mov(pio_pins, pio_null)); // for next time we turn output on

    DUMP_SPI_TRANSACTIONS(
        if (rx_length > 0) {
            printf("RXed:");
            dump_bytes(rx, rx_length);
            printf("\n");
        }
    )

    return true;
}

// To read a byte we must first have been asked to write a 3 byte spi header
static uint8_t wiznet_spi_pio_read_byte(void) {
    assert(active_state);    
    assert(active_state->spi_header_count == SPI_HEADER_LEN);
    uint8_t ret;
    if (!pio_spi_transfer(active_state, active_state->spi_header, active_state->spi_header_count, &ret, 1)) {
        panic("spi failed read");
    }
    active_state->spi_header_count = 0;
    return ret;
}

// This is not used when the burst functions are provided
static void wiznet_spi_pio_write_byte(uint8_t wb) {
    panic_unsupported(); // shouldn't be used
}

// To read a buffer we must first have been asked to write a 3 byte spi header
static void wiznet_spi_pio_read_buffer(uint8_t* pBuf, uint16_t len) {

    assert(active_state);
    assert(active_state->spi_header_count == SPI_HEADER_LEN);
    if (!pio_spi_transfer(active_state, active_state->spi_header, active_state->spi_header_count, pBuf, len)) {
        panic("spi failed reading buffer");
    }
    active_state->spi_header_count = 0;
}

// If we have been asked to write a spi header already, then write it and the rest of the buffer
// or else if we've been given enough data for just the spi header, save it until the next call
// or we're writing a byte in which case we're given a buffer including the spi header
static void wiznet_spi_pio_write_buffer(uint8_t* pBuf, uint16_t len) {
    assert(active_state);
    if (len == SPI_HEADER_LEN && active_state->spi_header_count == 0) {
        memcpy(active_state->spi_header, pBuf, SPI_HEADER_LEN); // expect another call
        active_state->spi_header_count = SPI_HEADER_LEN;
    } else {
        if (active_state->spi_header_count == SPI_HEADER_LEN) {
            if (!pio_spi_transfer(active_state, active_state->spi_header, SPI_HEADER_LEN, NULL, 0)) {
                panic("spi failed writing header");
            }
            active_state->spi_header_count = 0;
        }
        assert(active_state->spi_header_count == 0);
        if (!pio_spi_transfer(active_state, pBuf, len, NULL, 0)) {
            panic("spi failed writing buffer");
        }
    }
}

static void wiznet_spi_pio_set_active(wiznet_spi_handle_t handle) {
    active_state = (spi_pio_state_t *)handle;
}

static void wiznet_spi_pio_set_inactive(void) {
    active_state = NULL;
}

static void wizchip_spi_pio_reset(wiznet_spi_handle_t handle) {
    spi_pio_state_t *state = (spi_pio_state_t *)handle;
    gpio_set_dir(state->spi_config->reset_pin, GPIO_OUT);
    gpio_put(state->spi_config->reset_pin, 0);
    sleep_ms(100);
    gpio_put(state->spi_config->reset_pin, 1);
    sleep_ms(100);
}

static wiznet_spi_funcs_t *get_wiznet_spi_pio_impl(void) {
    static wiznet_spi_funcs_t funcs = {
        .close = wiznet_spi_pio_close,
        .set_active = wiznet_spi_pio_set_active,
        .set_inactive = wiznet_spi_pio_set_inactive,
        .frame_start = wiznet_spi_pio_frame_start,
        .frame_end = wiznet_spi_pio_frame_end,
        .read_byte = wiznet_spi_pio_read_byte,
        .write_byte = wiznet_spi_pio_write_byte,
        .read_buffer = wiznet_spi_pio_read_buffer,
        .write_buffer = wiznet_spi_pio_write_buffer,
        .reset = wizchip_spi_pio_reset,
    };
    return &funcs;
}