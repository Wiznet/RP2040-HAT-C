add_library(HTTPSERVER_FILES STATIC
        httpParser.c
        httpParser.h
        httpServer.c
        httpServer.h
        httpUtil.c
        httpUtil.h
        )

target_include_directories(HTTPSERVER_FILES PUBLIC
        ../../Ethernet
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(HTTPSERVER_FILES PUBLIC
        pico_stdlib
        ETHERNET_FILES
        )
