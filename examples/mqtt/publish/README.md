# How to Test MQTT Publish Example



## Step 1: Prepare software

The following serial terminal program and MQTT broker are required for MQTT Publish example test, download and install from below links.

- [**Tera Term**][link-tera_term]
- [**Mosquitto**][link-mosquitto]



## Step 2: Prepare hardware

If you are using W5100S-EVB-Pico or W5500-EVB-Pico, you can skip '1. Combine...'

1. Combine WIZnet Ethernet HAT with Raspberry Pi Pico.

2. Connect ethernet cable to WIZnet Ethernet HAT, W5100S-EVB-Pico or W5500-EVB-Pico ethernet port.

3. Connect Raspberry Pi Pico, W5100S-EVB-Pico or W5500-EVB-Pico to desktop or laptop using 5 pin micro USB cable.



## Step 3: Setup MQTT Publish Example

To test the MQTT Publish example, minor settings shall be done in code.

1. Setup SPI port and pin in 'w5x00_spi.h' in 'RP2040-HAT-C/port/ioLibrary_Driver/' directory.

Setup the SPI interface you use.

```cpp
/* SPI */
#define SPI_PORT spi0

#define PIN_SCK 18
#define PIN_MOSI 19
#define PIN_MISO 16
#define PIN_CS 17
#define PIN_RST 20
```

If you want to test with the MQTT Publish example using SPI DMA, uncomment USE_SPI_DMA.

```cpp
/* Use SPI DMA */
//#define USE_SPI_DMA // if you want to use SPI DMA, uncomment.
```

2. Setup network configuration such as IP in 'w5x00_mqtt_publish.c' which is the MQTT Publish example in 'RP2040-HAT-C/examples/mqtt/publish/' directory.

Setup IP and other network settings to suit your network environment.

```cpp
/* Network */
static wiz_NetInfo g_net_info =
    {
        .mac = {0x00, 0x08, 0xDC, 0x12, 0x34, 0x56}, // MAC address
        .ip = {192, 168, 11, 2},                     // IP address
        .sn = {255, 255, 255, 0},                    // Subnet Mask
        .gw = {192, 168, 11, 1},                     // Gateway
        .dns = {8, 8, 8, 8},                         // DNS server
        .dhcp = NETINFO_STATIC                       // DHCP enable/disable
};
```

3. Setup MQTT configuration in w5x00_mqtt_publish.c' in 'RP2040-HAT-C/examples/mqtt/publish/' directory.

In the MQTT configuration, the broker IP is the IP of your desktop or laptop where broker will be created.

```cpp
/* Port */
#define PORT_MQTT 1883

/* MQTT */
#define MQTT_CLIENT_ID "rpi-pico"
#define MQTT_USERNAME "wiznet"
#define MQTT_PASSWORD "0123456789"
#define MQTT_PUBLISH_TOPIC "publish_topic"
#define MQTT_PUBLISH_PAYLOAD "Hello, World!"
#define MQTT_KEEP_ALIVE 60 // 60 milliseconds

static uint8_t g_mqtt_broker_ip[4] = {192, 168, 11, 3};
```



## Step 4: Build

1. After completing the MQTT Publish example configuration, click 'build' in the status bar at the bottom of Visual Studio Code or press the 'F7' button on the keyboard to build.

2. When the build is completed, 'w5x00_mqtt_publish.uf2' is generated in 'RP2040-HAT-C/build/examples/mqtt/publish/' directory.



## Step 5: Upload and Run

1. While pressing the BOOTSEL button of Raspberry Pi Pico, W5100S-EVB-Pico or W5500-EVB-Pico power on the board, the USB mass storage 'RPI-RP2' is automatically mounted.

![][link-raspberry_pi_pico_usb_mass_storage]

2. Drag and drop 'w5x00_mqtt_publish.uf2' onto the USB mass storage device 'RPI-RP2'.

3. Connect to the serial COM port of Raspberry Pi Pico, W5100S-EVB-Pico or W5500-EVB-Pico that is open with Tera Term.

![][link-connect_to_serial_com_port]

4. Run Mosquitto to be used as the broker.

![][link-run_mosquitto]

5. Create broker using Mosquitto by executing the following command. If the broker is created normally, the broker's IP is the current IP of your desktop or laptop, and the port is 1883 by default.

```cpp
mosquitto -c mosquitto.conf -v
```

![][link-create_mqtt_broker_using_mosquitto]

6. Reset your board.

7. If the MQTT Publish example works normally on Raspberry Pi Pico, W5100S-EVB-Pico or W5500-EVB-Pico, you can see the network information of Raspberry Pi Pico, W5100S-EVB-Pico or W5500-EVB-Pico, connecting to the broker and publishing the message.

![][link-see_network_information_of_raspberry_pi_pico_connecting_to_broker_and_publishing_message_1]

![][link-see_network_information_of_raspberry_pi_pico_connecting_to_broker_and_publishing_message_2]



## Appendix

- In Mosquitto versions earlier than 2.0 the default is to allow clients to connect without authentication. In 2.0 and up, you must choose your authentication options explicitly before clients can connect. Therefore, if you are using version 2.0 or later, refer to following link to setup 'mosquitto.conf' in the directory where Mosquitto is installed.

    - [**Authentication Methods**][link-authentication_methods]



<!--
Link
-->

[link-tera_term]: https://osdn.net/projects/ttssh2/releases/
[link-mosquitto]: https://mosquitto.org/download/
[link-raspberry_pi_pico_usb_mass_storage]: https://github.com/Wiznet/RP2040-HAT-C/blob/main/static/images/mqtt/publish/raspberry_pi_pico_usb_mass_storage.png
[link-connect_to_serial_com_port]: https://github.com/Wiznet/RP2040-HAT-C/blob/main/static/images/mqtt/publish/connect_to_serial_com_port.png
[link-run_mosquitto]: https://github.com/Wiznet/RP2040-HAT-C/blob/main/static/images/mqtt/publish/run_mosquitto.png
[link-create_mqtt_broker_using_mosquitto]: https://github.com/Wiznet/RP2040-HAT-C/blob/main/static/images/mqtt/publish/create_mqtt_broker_using_mosquitto.png
[link-see_network_information_of_raspberry_pi_pico_connecting_to_broker_and_publishing_message_1]: https://github.com/Wiznet/RP2040-HAT-C/blob/main/static/images/mqtt/publish/see_network_information_of_raspberry_pi_pico_connecting_to_broker_and_publishing_message_1.png
[link-see_network_information_of_raspberry_pi_pico_connecting_to_broker_and_publishing_message_2]: https://github.com/Wiznet/RP2040-HAT-C/blob/main/static/images/mqtt/publish/see_network_information_of_raspberry_pi_pico_connecting_to_broker_and_publishing_message_2.png
[link-authentication_methods]: https://mosquitto.org/documentation/authentication-methods/
