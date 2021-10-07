add_executable(w5x00_ftp_client
        w5x00_ftp_client.c
        )

target_include_directories(w5x00_ftp_client PUBLIC
        ${CMAKE_SOURCE_DIR}/libraries/ioLibrary_Driver/Ethernet
        ${CMAKE_SOURCE_DIR}/libraries/ioLibrary_Driver/Internet/FTPClient
		${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(w5x00_ftp_client PUBLIC
        pico_stdlib
        hardware_spi
        hardware_dma
        hardware_clocks
        ETHERNET_FILES
        FTPCLIENT_FILES
        )

pico_enable_stdio_usb(w5x00_ftp_client 1)
pico_enable_stdio_uart(w5x00_ftp_client 0)

pico_add_extra_outputs(w5x00_ftp_client)
