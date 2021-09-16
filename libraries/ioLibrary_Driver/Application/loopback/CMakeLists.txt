add_library(LOOPBACK_FILES STATIC
        loopback.c
        loopback.h
        )

target_include_directories(LOOPBACK_FILES PUBLIC
        ../../Ethernet
        )

target_link_libraries(LOOPBACK_FILES PUBLIC
        pico_stdlib
        ETHERNET_FILES
        )
