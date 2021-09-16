add_library(DHCP_FILES STATIC
        dhcp.c
        dhcp.h
        )

target_include_directories(DHCP_FILES PUBLIC
        ../../Ethernet
        )

target_link_libraries(DHCP_FILES PUBLIC
        pico_stdlib
        ETHERNET_FILES
        )
