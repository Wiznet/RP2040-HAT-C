add_executable(w5x00_http_server
        w5x00_http_server.c
        )

target_link_libraries(w5x00_http_server PRIVATE
        pico_stdlib
        hardware_spi
        hardware_dma
        ETHERNET_FILES
        HTTPSERVER_FILES
        SPI_FILES
        )

pico_enable_stdio_usb(w5x00_http_server 1)
pico_enable_stdio_uart(w5x00_http_server 0)

pico_add_extra_outputs(w5x00_http_server)
