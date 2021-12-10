# Ethernet
add_library(ETHERNET_FILES STATIC)

target_sources(ETHERNET_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet/socket.c
        ${WIZNET_DIR}/Ethernet/wizchip_conf.c	
        )

target_include_directories(ETHERNET_FILES INTERFACE
        ${WIZNET_DIR}/Ethernet
#        ${WIZNET_DIR}/Ethernet/W5100
        ${WIZNET_DIR}/Ethernet/W5100S
#        ${WIZNET_DIR}/Ethernet/W5200
#        ${WIZNET_DIR}/Ethernet/W5300
#        ${WIZNET_DIR}/Ethernet/W5500
        )

target_link_libraries(ETHERNET_FILES PUBLIC
#        W5100_FILES
        W5100S_FILES
#        W5200_FILES
#        W5300_FILES
#        W5500_FILES
        )

# W5100
#add_library(W5100_FILES STATIC)
#
#target_sources(W5100_FILES PUBLIC
#        ${WIZNET_DIR}/Ethernet/W5100/w5100.c
#        )
#
#target_include_directories(W5100_FILES INTERFACE
#        ${WIZNET_DIR}/Ethernet
#        ${WIZNET_DIR}/Ethernet/W5100
#        )
#
# target_link_libraries(W5100_FILES PRIVATE
#        ETHERNET_FILES
#        )

# W5100S
add_library(W5100S_FILES STATIC)

target_sources(W5100S_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet/W5100S/w5100s.c
        )

target_include_directories(W5100S_FILES INTERFACE
        ${WIZNET_DIR}/Ethernet
        ${WIZNET_DIR}/Ethernet/W5100S
        )

target_link_libraries(W5100S_FILES PRIVATE
        ETHERNET_FILES
        )

# W5200
#add_library(W5200_FILES STATIC)
#
#target_sources(W5200_FILES PUBLIC
#        ${WIZNET_DIR}/Ethernet/W5200/w5200.c
#        )
#
#target_include_directories(W5200_FILES INTERFACE
#        ${WIZNET_DIR}/Ethernet
#        ${WIZNET_DIR}/Ethernet/W5200
#        )
#
#target_link_libraries(W5200_FILES PRIVATE
#        ETHERNET_FILES
#        )

# W5300
#add_library(W5300_FILES STATIC)
#
#target_sources(W5300_FILES PUBLIC
#        ${WIZNET_DIR}/Ethernet/W5300/w5300.c
#        )
#
#target_include_directories(W5300_FILES INTERFACE
#        ${WIZNET_DIR}/Ethernet
#        ${WIZNET_DIR}/Ethernet/W5300
#        )
#
#target_link_libraries(W5300_FILES PRIVATE
#        ETHERNET_FILES
#        )

# W5500
#add_library(W5500_FILES STATIC)
#
#target_sources(W5500_FILES PUBLIC
#        ${WIZNET_DIR}/Ethernet/W5500/w5500.c
#        )
#
#target_include_directories(W5500_FILES INTERFACE
#        ${WIZNET_DIR}/Ethernet
#        ${WIZNET_DIR}/Ethernet/W5500
#        )
#
#target_link_libraries(W5500_FILES PRIVATE
#        ETHERNET_FILES
#        )

# Loopback
add_library(LOOPBACK_FILES STATIC)

target_sources(LOOPBACK_FILES PUBLIC
        ${WIZNET_DIR}/Application/loopback/loopback.c
        )

target_include_directories(LOOPBACK_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet
        ${WIZNET_DIR}/Application/loopback
        )

# DHCP
add_library(DHCP_FILES STATIC)

target_sources(DHCP_FILES PUBLIC
        ${WIZNET_DIR}/Internet/DHCP/dhcp.c
        )

target_include_directories(DHCP_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet
        ${WIZNET_DIR}/Internet/DHCP
        )

# DNS
add_library(DNS_FILES STATIC)

target_sources(DNS_FILES PUBLIC
        ${WIZNET_DIR}/Internet/DNS/dns.c
        )

target_include_directories(DNS_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet
        ${WIZNET_DIR}/Internet/DNS
        )

# FTP Client
add_library(FTPCLIENT_FILES STATIC)

target_sources(FTPCLIENT_FILES PUBLIC
        ${WIZNET_DIR}/Internet/FTPClient/ftpc.c
        )

target_include_directories(FTPCLIENT_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet
        ${WIZNET_DIR}/Internet/FTPClient
        )

# FTP Server
add_library(FTPSERVER_FILES STATIC)

target_sources(FTPSERVER_FILES PUBLIC
        ${WIZNET_DIR}/Internet/FTPServer/ftpd.c
        )

target_include_directories(FTPSERVER_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet
        ${WIZNET_DIR}/Internet/FTPServer
        )

# HTTP Server
add_library(HTTPSERVER_FILES STATIC)

target_sources(HTTPSERVER_FILES PUBLIC
        ${WIZNET_DIR}/Internet/httpServer/httpParser.c
        ${WIZNET_DIR}/Internet/httpServer/httpServer.c
        ${WIZNET_DIR}/Internet/httpServer/httpUtil.c
        )

target_include_directories(HTTPSERVER_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet
        ${WIZNET_DIR}/Internet/httpServer
        )

# MQTT
add_library(MQTT_FILES STATIC)

target_sources(MQTT_FILES PUBLIC
        ${WIZNET_DIR}/Internet/MQTT/mqtt_interface.c
        ${WIZNET_DIR}/Internet/MQTT/MQTTClient.c
        ${WIZNET_DIR}/Internet/MQTT/MQTTPacket/src/MQTTConnectClient.c
        ${WIZNET_DIR}/Internet/MQTT/MQTTPacket/src/MQTTConnectServer.c
        ${WIZNET_DIR}/Internet/MQTT/MQTTPacket/src/MQTTDeserializePublish.c
        ${WIZNET_DIR}/Internet/MQTT/MQTTPacket/src/MQTTFormat.c
        ${WIZNET_DIR}/Internet/MQTT/MQTTPacket/src/MQTTPacket.c
        ${WIZNET_DIR}/Internet/MQTT/MQTTPacket/src/MQTTSerializePublish.c
        ${WIZNET_DIR}/Internet/MQTT/MQTTPacket/src/MQTTSubscribeClient.c
        ${WIZNET_DIR}/Internet/MQTT/MQTTPacket/src/MQTTSubscribeServer.c
        ${WIZNET_DIR}/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeClient.c
        ${WIZNET_DIR}/Internet/MQTT/MQTTPacket/src/MQTTUnsubscribeServer.c
        )

target_include_directories(MQTT_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet
        ${WIZNET_DIR}/Internet/MQTT
        ${WIZNET_DIR}/Internet/MQTTPacket/src	
        ) 

# SNTP
add_library(SNTP_FILES STATIC)

target_sources(SNTP_FILES PUBLIC
        ${WIZNET_DIR}/Internet/SNTP/sntp.c
        )

target_include_directories(SNTP_FILES PUBLIC
        ${WIZNET_DIR}/Ethernet
        ${WIZNET_DIR}/Internet/SNTP
        )
