add_executable(w5x00_tcp_client_over_ssl
	w5x00_tcp_client_over_ssl.c
        )

target_include_directories(w5x00_tcp_client_over_ssl PUBLIC
        ${CMAKE_SOURCE_DIR}/libraries/ioLibrary_Driver/Ethernet
        ${CMAKE_SOURCE_DIR}/libraries/mbedtls/include
        ${CMAKE_SOURCE_DIR}/libraries/mbedtls/library
        )

target_link_libraries(w5x00_tcp_client_over_ssl PUBLIC
        pico_stdlib
        hardware_spi
        hardware_dma
        ETHERNET_FILES
        mbedcrypto
        mbedx509
        mbedtls
        )

pico_enable_stdio_usb(w5x00_tcp_client_over_ssl 1)
pico_enable_stdio_uart(w5x00_tcp_client_over_ssl 0)

pico_add_extra_outputs(w5x00_tcp_client_over_ssl)
