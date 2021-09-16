add_library(W5200_FILES STATIC
        w5200.c
        w5200.h
        )

target_include_directories(W5200_FILES PUBLIC
        ../../Ethernet
        )

target_link_libraries(W5200_FILES PUBLIC
        pico_stdlib
        ETHERNET_FILES
        )