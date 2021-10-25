# Ethernet
add_library(ETHERNET_FILES STATIC)

target_sources(ETHERNET_FILES PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet/socket.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet/wizchip_conf.c	
    )

target_include_directories(ETHERNET_FILES PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet
#    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet/W5100
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet/W5100S
#    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet/W5200
#    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet/W5300
#    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet/W5500
    )

target_link_libraries(ETHERNET_FILES PUBLIC
    pico_stdlib
#    W5100_FILES
    W5100S_FILES
#    W5200_FILES
#    W5300_FILES
#    W5500_FILES
    )

# W5100
#add_library(W5100_FILES STATIC)
#
#target_sources(W5100_FILES PUBLIC
#    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet/W5100/w5100.c
#    )
#
#target_include_directories(W5100_FILES PUBLIC
#    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet
#    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet/W5100
#    )
#
#target_link_libraries(W5100_FILES PUBLIC
#    pico_stdlib
#    ETHERNET_FILES
#    )

# W5100S
add_library(W5100S_FILES STATIC)

target_sources(W5100S_FILES PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet/W5100S/w5100s.c
    )

target_include_directories(W5100S_FILES PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet/W5100S
    )

target_link_libraries(W5100S_FILES PUBLIC
    pico_stdlib
    ETHERNET_FILES
    )

# W5200
#add_library(W5200_FILES STATIC)
#
#target_sources(W5200_FILES PUBLIC
#    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet/W5200/w5200.c
#    )
#
#target_include_directories(W5200_FILES PUBLIC
#    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet
#    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet/W5200
#    )
#
#target_link_libraries(W5200_FILES PUBLIC
#    pico_stdlib
#    ETHERNET_FILES
#    )

# W5300
#add_library(W5300_FILES STATIC)
#
#target_sources(W5300_FILES PUBLIC
#    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet/W5300/w5300.c
#    )
#
#target_include_directories(W5300_FILES PUBLIC
#    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet
#    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet/W5300
#    )
#
#target_link_libraries(W5300_FILES PUBLIC
#    pico_stdlib
#    ETHERNET_FILES
#    )

# W5500
#add_library(W5500_FILES STATIC)
#
#target_sources(W5500_FILES PUBLIC
#    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet/W5500/w5500.c
#    )
#
#target_include_directories(W5500_FILES PUBLIC
#    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet
#    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet/W5500
#    )
#
#target_link_libraries(W5500_FILES PUBLIC
#    pico_stdlib
#    ETHERNET_FILES
#    )

# Loopback
add_library(LOOPBACK_FILES STATIC)

target_sources(LOOPBACK_FILES PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Application/loopback/loopback.c
    )

target_include_directories(LOOPBACK_FILES PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Application/loopback
    )

target_link_libraries(LOOPBACK_FILES PUBLIC
    pico_stdlib
    ETHERNET_FILES
    )

# DHCP
add_library(DHCP_FILES STATIC)

target_sources(DHCP_FILES PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Internet/DHCP/dhcp.c
    )

target_include_directories(DHCP_FILES PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Internet/DHCP
    )

target_link_libraries(DHCP_FILES PUBLIC
    pico_stdlib
    ETHERNET_FILES
    )

# DNS
add_library(DNS_FILES STATIC)

target_sources(DNS_FILES PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Internet/DNS/dns.c
    )

target_include_directories(DNS_FILES PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Internet/DNS
    )

target_link_libraries(DNS_FILES PUBLIC
    pico_stdlib
    ETHERNET_FILES
    )

# FTP Client
add_library(FTPCLIENT_FILES STATIC)

target_sources(FTPCLIENT_FILES PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Internet/FTPClient/ftpc.c
    )

target_include_directories(FTPCLIENT_FILES PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Internet/FTPClient
    )

target_link_libraries(FTPCLIENT_FILES PUBLIC
    pico_stdlib
    ETHERNET_FILES
    )

# FTP Server
add_library(FTPSERVER_FILES STATIC)

target_sources(FTPSERVER_FILES PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Internet/FTPServer/ftpd.c
    )

target_include_directories(FTPSERVER_FILES PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Internet/FTPServer
    )

target_link_libraries(FTPSERVER_FILES PUBLIC
    pico_stdlib
    ETHERNET_FILES
    )

# HTTP Server
add_library(HTTPSERVER_FILES STATIC)

target_sources(HTTPSERVER_FILES PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Internet/httpServer/httpParser.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Internet/httpServer/httpServer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Internet/httpServer/httpUtil.c
    )

target_include_directories(HTTPSERVER_FILES PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Internet/httpServer
    )

target_link_libraries(HTTPSERVER_FILES PUBLIC
    pico_stdlib
    ETHERNET_FILES
    )

# MQTT
add_library(MQTT_FILES STATIC)

target_sources(MQTT_FILES PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Internet/MQTT/mqtt_interface.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Internet/MQTT/MQTTClient.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Internet/MQTT/MQTTPacket/src/MQTTFormat.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Internet/MQTT/MQTTPacket/src/MQTTPacket.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.c
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.c
    )

target_include_directories(MQTT_FILES PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Internet/MQTT
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Internet/MQTTPacket/src	
    )

target_link_libraries(MQTT_FILES PUBLIC
    pico_stdlib
    ETHERNET_FILES
    )

# SNTP
add_library(SNTP_FILES STATIC)

target_sources(SNTP_FILES PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Internet/SNTP/sntp.c
    )

target_include_directories(SNTP_FILES PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Ethernet
    ${CMAKE_CURRENT_SOURCE_DIR}/ioLibrary_Driver/Internet/SNTP
    )

target_link_libraries(SNTP_FILES PUBLIC
    pico_stdlib
    ETHERNET_FILES
    )

# Add subdirectory
add_subdirectory(mbedtls)
