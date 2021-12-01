add_executable(w5x00_ftp_client
        w5x00_ftp_client.c
        )

target_link_libraries(w5x00_ftp_client PRIVATE
        pico_stdlib
        hardware_spi
        hardware_dma
        hardware_clocks
        ETHERNET_FILES
        FTPCLIENT_FILES
        SPI_FILES
        )

pico_enable_stdio_usb(w5x00_ftp_client 1)
pico_enable_stdio_uart(w5x00_ftp_client 0)

pico_add_extra_outputs(w5x00_ftp_client)
