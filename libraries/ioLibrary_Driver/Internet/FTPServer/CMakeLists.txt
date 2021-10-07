add_library(FTPSERVER_FILES STATIC
        ftpd.c
        ftpd.h
        stdio_private.h
        )

target_include_directories(FTPSERVER_FILES PUBLIC
        ../../Ethernet
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(FTPSERVER_FILES PUBLIC
        pico_stdlib
        ETHERNET_FILES
        )
