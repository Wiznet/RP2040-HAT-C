add_executable(w5x00_mqtt_publish
        w5x00_mqtt_publish.c
        )

target_link_libraries(w5x00_mqtt_publish PRIVATE
        pico_stdlib
        hardware_spi
        hardware_dma
        ETHERNET_FILES
        MQTT_FILES        
        SPI_FILES
        )

pico_enable_stdio_usb(w5x00_mqtt_publish 1)
pico_enable_stdio_uart(w5x00_mqtt_publish 0)

pico_add_extra_outputs(w5x00_mqtt_publish)
