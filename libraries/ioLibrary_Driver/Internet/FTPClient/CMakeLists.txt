add_library(FTPCLIENT_FILES STATIC
        ftpc.c
        ftpc.h
        stdio_private.h
        )

target_include_directories(FTPCLIENT_FILES PUBLIC
        ../../Ethernet
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(FTPCLIENT_FILES PUBLIC
        pico_stdlib
        ETHERNET_FILES
        )
