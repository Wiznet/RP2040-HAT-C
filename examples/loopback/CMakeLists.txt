add_executable(w5x00_loopback
        w5x00_loopback.c
        )

target_link_libraries(w5x00_loopback PRIVATE
        pico_stdlib
        hardware_spi
        hardware_dma
        LOOPBACK_FILES
        ETHERNET_FILES
        SPI_FILES
        )

pico_enable_stdio_usb(w5x00_loopback 1)
pico_enable_stdio_uart(w5x00_loopback 0)

pico_add_extra_outputs(w5x00_loopback)
