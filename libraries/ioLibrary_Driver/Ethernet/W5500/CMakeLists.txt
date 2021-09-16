add_library(W5500_FILES STATIC
        w5500.c
        w5500.h
        )

target_include_directories(W5500_FILES PUBLIC
        ../../Ethernet
        )

target_link_libraries(W5500_FILES PUBLIC
        pico_stdlib
        ETHERNET_FILES
        )