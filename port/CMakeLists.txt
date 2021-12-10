# ioLibrary_Driver
add_library(SPI_FILES STATIC)

target_sources(SPI_FILES PUBLIC
        ${PORT_DIR}/ioLibrary_Driver/w5x00_spi.c
        )

target_include_directories(SPI_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet
        ${PORT_DIR}/ioLibrary_Driver
        ${PORT_DIR}
        )

target_link_libraries(SPI_FILES PRIVATE
        pico_stdlib
        hardware_spi
        hardware_dma
        hardware_clocks
        )

# timer
add_library(TIMER_FILES STATIC)

target_sources(TIMER_FILES PUBLIC
        ${PORT_DIR}/timer/timer.c
        )

target_include_directories(TIMER_FILES PUBLIC
        ${PORT_DIR}/timer
        )

target_link_libraries(TIMER_FILES PRIVATE
        pico_stdlib      
        )
