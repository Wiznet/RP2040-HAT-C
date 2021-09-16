add_executable(w5x00_sntp
        w5x00_sntp.c
        )

target_include_directories(w5x00_sntp PUBLIC
        ${CMAKE_SOURCE_DIR}/libraries/ioLibrary_Driver/Ethernet
		${CMAKE_SOURCE_DIR}/libraries/ioLibrary_Driver/Internet/sntp
        )

target_link_libraries(w5x00_sntp PUBLIC
        pico_stdlib
        hardware_spi
        hardware_dma
        ETHERNET_FILES
		SNTP_FILES
        )

pico_enable_stdio_usb(w5x00_sntp 1)
pico_enable_stdio_uart(w5x00_sntp 0)

pico_add_extra_outputs(w5x00_sntp)
