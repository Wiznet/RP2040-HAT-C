# Getting Started with Ethernet Examples

These sections will guide you through a series of steps from configuring development environment to running ethernet examples using the **WIZnet's ethernet products**.

- [**Development environment configuration**](#development_environment_configuration)
- [**Hardware requirements**](#hardware_requirements)
- [**Ethernet example structure**](#ethernet_example_structure)
- [**Ethernet example testing**](#ethernet_example_testing)
- [**How to use port directory**](#how_to_use_port_directory)



<a name="development_environment_configuration"></a>
## Development environment configuration

To test the ethernet examples, the development environment must be configured to use Raspberry Pi Pico.

The ethernet examples were tested by configuring the development environment for **Windows**. Please refer to the '**9.2. Building on MS Windows**' section of '**Getting started with Raspberry Pi Pico**' document below and configure accordingly.

- [**Getting started with Raspberry Pi Pico**][link-getting_started_with_raspberry_pi_pico]

**Visual Studio Code** was used during development and testing of ethernet examples, the guide document in each directory was prepared also base on development with Visual Studio Code. Please refer to corresponding document.



<a name="hardware_requirements"></a>
## Hardware requirements

The ethernet examples use **Raspberry Pi Pico** and **WIZnet Ethernet HAT** - ethernet I/O module built on WIZnet's [**W5100S**][link-w5100s] ethernet chip or **W5100S-EVB-Pico** - ethernet I/O module built on [**RP2040**][link-rp2040] and WIZnet's [**W5100S**][link-w5100s] ethernet chip.

- [**Raspberry Pi Pico**][link-raspberry_pi_pico]

![][link-raspberry_pi_pico_main]

- [**WIZnet Ethernet HAT**][link-wiznet_ethernet_hat]

![][link-wiznet_ethernet_hat_main]

- [**W5100S-EVB-Pico**][link-w5100s-evb-pico]

![][link-w5100s-evb-pico_main]



<a name="ethernet_example_structure"></a>
## Ethernet example structure

Examples are available at '**RP2040-HAT-C/examples/**' directory. As of now, following examples are provided.

- [**DHCP & DNS**][link-dhcp_dns]
- [**FTP**][link-ftp]
	- [**Client**][link-ftp_client]
	- [**Server**][link-ftp_server]
- [**HTTP**][link-http]
	- [**Server**][link-http_server]
- [**Loopback**][link-loopback]
- [**MQTT**][link-mqtt]
	- [**Publish**][link-mqtt_publish]
	- [**Publish & Subscribe**][link-mqtt_publish_subscribe]
	- [**Subscribe**][link-mqtt_subscribe]
- [**SNTP**][link-sntp]
- [**TCP Client over SSL**][link-tcp_client_over_ssl]

Note that **ioLibrary_Driver**, **mbedtls**, **pico-sdk** are needed to run ethernet examples.

- **ioLibrary_Driver** library is applicable to WIZnet's W5x00 ethernet chip.
- **mbedtls** library supports additional algorithms and support related to SSL and TLS connections.
- **pico-sdk** is made available by Pico to enable developers to build software applications for the Pico platform.
- **pico-extras** has additional libraries that are not yet ready for inclusion the Pico SDK proper, or are just useful but don't necessarily belong in the Pico SDK.

Libraries are located in the '**RP2040-HAT-C/libraries/**' directory.

- [**ioLibrary_Driver**][link-iolibrary_driver]
- [**mbedtls**][link-mbedtls]
- [**pico-sdk**][link-pico_sdk]
- [**pico-extras**][link-pico_extras]

If you want to modify the code that MCU-dependent and use a MCU other than **RP2040**, you can modify it in the **RP2040-HAT-C/port/** directory.

port is located in the '**RP2040-HAT-C/port/**' directory.

- [**ioLibrary_Driver**][link-port_iolibrary_driver]
- [**mbedtls**][link-port_mbedtls]
- [**timer**][link-port_timer]

The structure of this **RP2040-HAT-C 2.0.0** version has changed a lot compared to the previous version. If you want to refer to the previous version, please refer to the link below.

- [**RP2040-HAT-C 1.0.0 version**][link-rp2040_hat_c_1_0_0_version]



<a name="Ethernet_example_testing"></a>
## Ethernet example testing

1. Download

If the ethernet examples are cloned, the library set as a submodule is an empty directory. Therefore, if you want to download the library set as a submodule together, clone the ethernet examples with the following Git command.

```cpp
/* Change directory */
// change to the directory to clone
cd [user path]

// e.g.
cd D:/RP2040

/* Clone */
git clone --recurse-submodules https://github.com/Wiznet/RP2040-HAT-C.git
```

With Visual Studio Code, the library set as a submodule is automatically downloaded, so it doesn't matter whether the library set as a submodule is an empty directory or not, so refer to it.

2. Patch

With Visual Studio Code, each library set as a submodule is automatically patched, but if you do not use Visual Studio Code, each library set as a submodule must be manually patched with the Git commands below in each library directory.

- ioLibrary_Driver

```cpp
/* Change directory */
// change to the 'ioLibrary_Driver' library directory
cd [user path]/RP2040-HAT-C/libraries/ioLibrary_Driver

// e.g.
cd D:/RP2040/RP2040-HAT-C/libraries/ioLibrary_Driver

/* Patch */
git apply ../../patches/01_iolibrary_driver_ethernet_chip.patch
git apply ../../patches/02_iolibrary_driver_ftp_client.patch
```

3. Test

Please refer to 'README.md' in each example directory to find detail guide for testing ethernet examples.



<a name="how_to_use_port_directory"></a>
## How to use port directory

We moved the MCU dependent code to the port directory. The tree of port is shown below.

```
RP2040-HAT-C
┣ port
    ┣ ioLibrary_Driver
    ┃   ┣ w5x00_spi.c
    ┃   ┗ w5x00_spi.h
    ┣ mbedtls
    ┃   ┗ inc
    ┃   ┃   ┗ ssl_config.h
    ┣ timer
    ┃   ┣ timer.c
    ┃   ┗ timer.h
    ┣ CMakeLists.txt
    ┗ port_common.h
```

- **ioLibrary_Driver**

If you want to change things related to SPI, such as the SPI port number and SPI read/write function, or use a different MCU without using the RP2040, you need to change the code in the '**RP2040-HAT-C/port/ioLibrary_Driver/**' directory. Here is information about functions.

```cpp
/*! \brief Set CS pin
 *  \ingroup w5x00_spi
 *
 * Set chip select pin of spi0 to low(Active low).
 *
 * \param none
 */
static inline void wizchip_select(void);

/*! \brief Set CS pin
 *  \ingroup w5x00_spi
 *
 * Set chip select pin of spi0 to high(Inactive high).
 *
 * \param none
 */
static inline void wizchip_deselect(void);

/*! \brief Read from an SPI device, blocking
 *  \ingroup w5x00_spi
 * Set spi_read_blocking function.
 * Read byte from SPI to rx_data buffer.
 * Blocks until all data is transferred. No timeout, as SPI hardware always transfers at a known data rate.
 *
 * \param none
 */
static uint8_t wizchip_read(void);

/*! \brief Write to an SPI device, blocking
 *  \ingroup w5x00_spi
 * Set spi_write_blocking function.
 * Write byte from tx_data buffer to SPI device.
 * Blocks until all data is transferred. No timeout, as SPI hardware always transfers at a known data rate.
 *
 * \param tx_data Buffer of data to write
 */
static void wizchip_write(uint8_t tx_data);

#ifdef USE_SPI_DMA
/*! \brief Configure all DMA parameters and optionally start transfer
 *  \ingroup w5x00_spi
 *
 * Configure all DMA parameters and read from DMA
 *
 * \param pBuf Buffer of data to read
 * \param len element count (each element is of size transfer_data_size)
 */
static void wizchip_read_burst(uint8_t *pBuf, uint16_t len);

/*! \brief Configure all DMA parameters and optionally start transfer
 *  \ingroup w5x00_spi
 *
 * Configure all DMA parameters and write to DMA
 *
 * \param pBuf Buffer of data to write
 * \param len element count (each element is of size transfer_data_size)
 */
static void wizchip_write_burst(uint8_t *pBuf, uint16_t len);
#endif

/*! \brief Enter a critical section
 *  \ingroup w5x00_spi
 * Set ciritical section enter blocking function.
 * If the spin lock associated with this critical section is in use, then this
 * method will block until it is released.
 *
 * \param none
 */
static void wizchip_critical_section_lock(void);

/*! \brief Release a critical section
 *  \ingroup w5x00_spi
 * Set ciritical section exit function.
 * Release a critical section.
 *
 * \param none
 */
static void wizchip_critical_section_unlock(void);

/*! \brief Initialize SPI instances and Set DMA channel
 *  \ingroup w5x00_spi
 * Set GPIO to spi0.
 * Puts the SPI into a known state, and enable it.
 * Set DMA channel completion channel.
 *
 * \param none
 */
void wizchip_spi_initialize(void);

/*! \brief Initialize a critical section structure
 *  \ingroup w5x00_spi
 * The critical section is initialized ready for use.
 * Registers callback function for critical section for WIZchip.
 *
 * \param none
 */
void wizchip_cris_initialize(void);

/*! \brief W5x00 chip reset
 *  \ingroup w5x00_spi
 *
 * Set a reset pin and reset.
 *
 * \param none
 */
void wizchip_reset(void);

/*! \brief Initialize WIZchip
 *  \ingroup w5x00_spi
 * Set callback function to read/write byte using SPI.
 * Set callback function for WIZchip select/deselect.
 * Set memory size of W5x00 chip and monitor PHY link status.
 *
 * \param none
 */
void wizchip_initialize(void);

/*! \brief Check chip version
 *  \ingroup w5x00_spi
 *
 * Get version information.
 *
 * \param none
 */
void wizchip_check(void);

/* Network */
/*! \brief Initialize network
 *  \ingroup w5x00_spi
 *
 * Set network information.
 *
 * \param net_info network information.
 */
void network_initialize(wiz_NetInfo net_info);

/*! \brief Print network information
 *  \ingroup w5x00_spi
 *
 * Print network information about MAC address, IP address, Subnet mask, Gateway, DHCP and DNS address.
 *
 * \param net_info network information.
 */
void print_network_information(wiz_NetInfo net_info);

/* Clock */
/*! \brief Attempt to set a system clock frequency in khz
 *  \ingroup w5x00_spi
 * Set a system clock frequency in khz.
 * Configure the specified clock.
 *
 * \param none
 */
void set_clock_khz(void);
```

- **timer**

If you want to change things related to the **timer**. Also, if you use a different MCU without using the RP2040, you need to change the code in the '**RP2040-HAT-C/port/timer/**' directory. Here is information about functions.

```cpp
/*! \brief Initialize timer callback function
 * \ingroup timer
 *
 * Add a repeating timer that is called repeatedly at the specified interval in microseconds.
 *
 * \param callback the repeating timer callback function
 */
void wizchip_1ms_timer_initialize(void (*callback)(void));

/*! \brief Assign timer callback function
 * \ingroup timer
 *
 * 1ms timer callback function.
 *
 * \param t Information about a repeating timer
 */
bool wizchip_1ms_timer_callback(struct repeating_timer *t);

/* Delay */
/*! \brief Wait for the given number of milliseconds before returning
 * \ingroup timer
 *
 * This method attempts to perform a lower power sleep (using WFE) as much as possible.
 *
 * \param ms the number of milliseconds to sleep
 */
void wizchip_delay_ms(uint32_t ms);
```



<!--
Link
-->

[link-cmake_configure]: https://github.com/Wiznet/RP2040-HAT-C/blob/main/static/images/getting_started/cmake_configure.png
[link-getting_started_with_raspberry_pi_pico]: https://datasheets.raspberrypi.org/pico/getting-started-with-pico.pdf
[link-w5100s]: https://docs.wiznet.io/Product/iEthernet/W5100S/overview
[link-rp2040]: https://www.raspberrypi.org/products/rp2040/
[link-raspberry_pi_pico]: https://www.raspberrypi.org/products/raspberry-pi-pico/
[link-raspberry_pi_pico_main]: https://github.com/Wiznet/RP2040-HAT-C/blob/main/static/images/getting_started/raspberry_pi_pico_main.png
[link-wiznet_ethernet_hat]: https://docs.wiznet.io/Product/Open-Source-Hardware/wiznet_ethernet_hat
[link-wiznet_ethernet_hat_main]: https://github.com/Wiznet/RP2040-HAT-C/blob/main/static/images/getting_started/wiznet_ethernet_hat_main.png
[link-w5100s-evb-pico]: https://docs.wiznet.io/Product/iEthernet/W5100S/w5100s-evb-pico
[link-w5100s-evb-pico_main]: https://github.com/Wiznet/RP2040-HAT-C/blob/main/static/images/getting_started/w5100s-evb-pico_main.png
[link-dhcp_dns]: https://github.com/Wiznet/RP2040-HAT-C/tree/main/examples/dhcp_dns
[link-ftp]: https://github.com/Wiznet/RP2040-HAT-C/tree/main/examples/ftp
[link-ftp_client]: https://github.com/Wiznet/RP2040-HAT-C/tree/main/examples/ftp/client
[link-ftp_server]: https://github.com/Wiznet/RP2040-HAT-C/tree/main/examples/ftp/server
[link-http]: https://github.com/Wiznet/RP2040-HAT-C/tree/main/examples/http
[link-http_server]: https://github.com/Wiznet/RP2040-HAT-C/tree/main/examples/http/server
[link-loopback]: https://github.com/Wiznet/RP2040-HAT-C/tree/main/examples/loopback
[link-mqtt]: https://github.com/Wiznet/RP2040-HAT-C/tree/main/examples/mqtt
[link-mqtt_publish]: https://github.com/Wiznet/RP2040-HAT-C/tree/main/examples/mqtt/publish
[link-mqtt_publish_subscribe]: https://github.com/Wiznet/RP2040-HAT-C/tree/main/examples/mqtt/publish_subscribe
[link-mqtt_subscribe]: https://github.com/Wiznet/RP2040-HAT-C/tree/main/examples/mqtt/subscribe
[link-sntp]: https://github.com/Wiznet/RP2040-HAT-C/tree/main/examples/sntp
[link-tcp_client_over_ssl]: https://github.com/Wiznet/RP2040-HAT-C/tree/main/examples/tcp_client_over_ssl
[link-iolibrary_driver]: https://github.com/Wiznet/ioLibrary_Driver
[link-mbedtls]: https://github.com/ARMmbed/mbedtls
[link-pico_sdk]: https://github.com/raspberrypi/pico-sdk
[link-pico_extras]: https://github.com/raspberrypi/pico-extras
[link-port_iolibrary_driver]: https://github.com/Wiznet/RP2040-HAT-C/tree/main/port/ioLibrary_Driver
[link-port_mbedtls]: https://github.com/Wiznet/RP2040-HAT-C/tree/main/port/mbedtls/inc
[link-port_timer]: https://github.com/Wiznet/RP2040-HAT-C/tree/main/port/timer
[link-rp2040_hat_c_1_0_0_version]: https://github.com/Wiznet/RP2040-HAT-C/tree/3e60654e71f9afdd586c3368f8994dc03c6274e4
