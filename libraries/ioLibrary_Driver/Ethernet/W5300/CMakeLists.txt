add_library(W5300_FILES STATIC
        w5300.c
        w5300.h
        )

target_include_directories(W5300_FILES PUBLIC
        ../../Ethernet
        )

target_link_libraries(W5300_FILES PUBLIC
        pico_stdlib
        ETHERNET_FILES
        )