add_library(ETHERNET_FILES STATIC
        socket.c
        socket.h
        wizchip_conf.c
        wizchip_conf.h
        )

add_subdirectory(W5100S)

target_include_directories(ETHERNET_FILES PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
#        ${CMAKE_CURRENT_SOURCE_DIR}/W5100
        ${CMAKE_CURRENT_SOURCE_DIR}/W5100S
#        ${CMAKE_CURRENT_SOURCE_DIR}/W5200
#        ${CMAKE_CURRENT_SOURCE_DIR}/W5300
#        ${CMAKE_CURRENT_SOURCE_DIR}/W5500		
        )

target_link_libraries(ETHERNET_FILES PUBLIC
        pico_stdlib
#	W5100_FILES
        W5100S_FILES
#	W5200_FILES
#	W5300_FILES
#	W5500_FILES
        )
