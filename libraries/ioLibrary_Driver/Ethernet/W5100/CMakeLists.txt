add_library(W5100_FILES STATIC
        w5100.c
        w5100.h
        )

target_include_directories(W5100_FILES PUBLIC
        ../../Ethernet
        )

target_link_libraries(W5100_FILES PUBLIC
        pico_stdlib
        ETHERNET_FILES
        )