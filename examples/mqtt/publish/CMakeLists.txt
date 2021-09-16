add_executable(w5x00_mqtt_publish
        w5x00_mqtt_publish.c
        )

target_include_directories(w5x00_mqtt_publish PUBLIC
        ${CMAKE_SOURCE_DIR}/libraries/ioLibrary_Driver/Ethernet
        ${CMAKE_SOURCE_DIR}/libraries/ioLibrary_Driver/Internet/MQTT
        )

target_link_libraries(w5x00_mqtt_publish PUBLIC
        pico_stdlib
        hardware_spi
        hardware_dma
        ETHERNET_FILES
        MQTT_FILES
        )

pico_enable_stdio_usb(w5x00_mqtt_publish 1)
pico_enable_stdio_uart(w5x00_mqtt_publish 0)

pico_add_extra_outputs(w5x00_mqtt_publish)
