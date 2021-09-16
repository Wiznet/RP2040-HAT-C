add_executable(w5x00_dhcp_dns
        w5x00_dhcp_dns.c
        )

target_include_directories(w5x00_dhcp_dns PUBLIC
        ${CMAKE_SOURCE_DIR}/libraries/ioLibrary_Driver/Ethernet
        ${CMAKE_SOURCE_DIR}/libraries/ioLibrary_Driver/Internet/dhcp
        ${CMAKE_SOURCE_DIR}/libraries/ioLibrary_Driver/Internet/dns
        )

target_link_libraries(w5x00_dhcp_dns PUBLIC
        pico_stdlib
        hardware_spi
        hardware_dma
        ETHERNET_FILES
        DHCP_FILES
        DNS_FILES
        )

pico_enable_stdio_usb(w5x00_dhcp_dns 1)
pico_enable_stdio_uart(w5x00_dhcp_dns 0)

pico_add_extra_outputs(w5x00_dhcp_dns)
