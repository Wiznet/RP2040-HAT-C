add_library(MQTTPACKET_FILES STATIC
        MQTTConnect.h
        MQTTConnectClient.c
        MQTTConnectServer.c
        MQTTDeserializePublish.c
		MQTTFormat.c
		MQTTFormat.h
		MQTTPacket.c
		MQTTPacket.h
		MQTTPublish.h
		MQTTSerializePublish.c
		MQTTSubscribe.h
		MQTTSubscribeClient.c
		MQTTSubscribeServer.c
		MQTTUnsubscribe.h
		MQTTUnsubscribeClient.c
		MQTTUnsubscribeServer.c
		StackTrace.h
        )

target_include_directories(MQTTPACKET_FILES PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(MQTTPACKET_FILES PUBLIC
        pico_stdlib
        )
