add_library(DNS_FILES STATIC
        dns.c
        dns.h
        )

target_include_directories(DNS_FILES PUBLIC
        ../../Ethernet
        )

target_link_libraries(DNS_FILES PUBLIC
        pico_stdlib
        ETHERNET_FILES
        )
