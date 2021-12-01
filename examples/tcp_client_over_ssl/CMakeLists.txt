add_executable(w5x00_tcp_client_over_ssl
	w5x00_tcp_client_over_ssl.c
        )

target_link_libraries(w5x00_tcp_client_over_ssl PRIVATE
        pico_stdlib
        hardware_spi
        hardware_dma
        ETHERNET_FILES
        SPI_FILES
        TIMER_FILES        
        mbedcrypto
        mbedx509
        mbedtls
        )

pico_enable_stdio_usb(w5x00_tcp_client_over_ssl 1)
pico_enable_stdio_uart(w5x00_tcp_client_over_ssl 0)

pico_add_extra_outputs(w5x00_tcp_client_over_ssl)
