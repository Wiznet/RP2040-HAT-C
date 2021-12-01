add_executable(w5x00_mqtt_subscribe
        w5x00_mqtt_subscribe.c
        )

target_link_libraries(w5x00_mqtt_subscribe PRIVATE
        pico_stdlib
        hardware_spi
        hardware_dma
        ETHERNET_FILES
        MQTT_FILES        
        SPI_FILES
        )

pico_enable_stdio_usb(w5x00_mqtt_subscribe 1)
pico_enable_stdio_uart(w5x00_mqtt_subscribe 0)

pico_add_extra_outputs(w5x00_mqtt_subscribe)
