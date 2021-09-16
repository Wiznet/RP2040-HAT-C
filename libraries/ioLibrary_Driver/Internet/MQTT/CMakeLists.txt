add_library(MQTT_FILES STATIC
        mqtt_interface.c
		mqtt_interface.h
        MQTTClient.c
		MQTTClient.h
        )

add_subdirectory(MQTTPacket)

target_include_directories(MQTT_FILES PUBLIC
		../../Ethernet
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/MQTTPacket/src
        )

target_link_libraries(MQTT_FILES PUBLIC
        pico_stdlib
		ETHERNET_FILES
		MQTTPACKET_FILES
        )
