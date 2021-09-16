add_library(W5100S_FILES STATIC
        w5100s.c
        w5100s.h
        )

target_include_directories(W5100S_FILES PUBLIC
        ../../Ethernet
        )

target_link_libraries(W5100S_FILES PUBLIC
        pico_stdlib
        ETHERNET_FILES
        )
