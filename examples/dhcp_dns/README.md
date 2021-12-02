# How to Test DHCP & DNS Example



## Step 1: Prepare software

The following serial terminal program is required for DHCP & DNS example test, download and install from below link.

- [**Tera Term**][link-tera_term]



## Step 2: Prepare hardware

If you are using W5100S-EVB-Pico, you can skip '1. Combine...'

1. Combine WIZnet Ethernet HAT with Raspberry Pi Pico.

2. Connect ethernet cable to WIZnet Ethernet HAT or W5100S-EVB-Pico ethernet port.

3. Connect Raspberry Pi Pico or W5100S-EVB-Pico to desktop or laptop using 5 pin micro USB cable.



## Step 3: Setup DHCP & DNS Example

To test the DHCP & DNS example, minor settings shall be done in code.

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

If you want to test with the DHCP & DNS example using SPI DMA, uncomment USE_SPI_DMA.

```cpp
/* Use SPI DMA */
//#define USE_SPI_DMA // if you want to use SPI DMA, uncomment.
```

2. Setup network configuration such as IP in 'w5x00_dhcp_dns.c', which is the DHCP & DNS example in 'RP2040-HAT-C/examples/dhcp_dns/' directory.

Setup IP, other network settings to suit your network environment and whether to use DHCP.

```cpp
/* Network */
static wiz_NetInfo g_net_info =
    {
        .mac = {0x00, 0x08, 0xDC, 0x12, 0x34, 0x56}, // MAC address
        .ip = {192, 168, 11, 2},                     // IP address
        .sn = {255, 255, 255, 0},                    // Subnet Mask
        .gw = {192, 168, 11, 1},                     // Gateway
        .dns = {8, 8, 8, 8},                         // DNS server
        .dhcp = NETINFO_DHCP                         // DHCP enable/disable
};
```

3. Setup DNS configuration

Setup the domain name that you want to get IP in 'w5x00_dhcp_dns.c' in 'RP2040-HAT-C/examples/dhcp_dns/' directory.

```cpp
/* DNS */
static uint8_t g_dns_target_domain[] = "www.wiznet.io";
```



## Step 4: Build

1. After completing the DHCP & DNS example configuration, click 'build' in the status bar at the bottom of Visual Studio Code or press the 'F7' button on the keyboard to build.

2. When the build is completed, 'w5x00_dhcp_dns.uf2' is generated in 'RP2040-HAT-C/build/examples/dhcp_dns/' directory.



## Step 5: Upload and Run

1. While pressing the BOOTSEL button of Raspberry Pi Pico or W5100S-EVB-Pico power on the board, the USB mass storage 'RPI-RP2' is automatically mounted.

![][link-raspberry_pi_pico_usb_mass_storage]

2. Drag and drop 'w5x00_dhcp_dns.uf2' onto the USB mass storage device 'RPI-RP2'.

3. Connect to the serial COM port of Raspberry Pi Pico or W5100S-EVB-Pico with Tera Term.

![][link-connect_to_serial_com_port]

4. Reset your board.

5. If the DHCP & DNS example works normally on Raspberry Pi Pico or W5100S-EVB-Pico, you can see the network information, IP automatically assigned by DHCP of Raspberry Pi Pico or W5100S-EVB-Pico and the IP get from the domain name.

![][link-see_network_information_ip_assigned_by_dhcp_of_raspberry_pi_pico_and_get_ip_through_dns]



<!--
Link
-->

[link-tera_term]: https://osdn.net/projects/ttssh2/releases/
[link-raspberry_pi_pico_usb_mass_storage]: https://github.com/Wiznet/RP2040-HAT-C/blob/main/static/images/dhcp_dns/raspberry_pi_pico_usb_mass_storage.png
[link-connect_to_serial_com_port]: https://github.com/Wiznet/RP2040-HAT-C/blob/main/static/images/dhcp_dns/connect_to_serial_com_port.png
[link-see_network_information_ip_assigned_by_dhcp_of_raspberry_pi_pico_and_get_ip_through_dns]: https://github.com/Wiznet/RP2040-HAT-C/blob/main/static/images/dhcp_dns/see_network_information_ip_assigned_by_dhcp_of_raspberry_pi_pico_and_get_ip_through_dns.png
