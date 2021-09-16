add_library(SNTP_FILES STATIC
        sntp.c
        sntp.h
        )

target_include_directories(SNTP_FILES PUBLIC
        ../../Ethernet
        )

target_link_libraries(SNTP_FILES PUBLIC
        pico_stdlib
        ETHERNET_FILES
        )
