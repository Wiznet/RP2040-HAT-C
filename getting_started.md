# Ethernet Example Getting Started

These sections will guide you through a series of steps from configuring development environment to running ethernet examples using the **WIZnet's ethernet products**.

- [**Development environment configuration**](#development_environment_configuration)
- [**Hardware requirements**](#hardware_requirements)
- [**Ethernet example structure**](#ethernet_example_structure)
- [**Ethernet example testing**](#ethernet_example_testing)



<a name="development_environment_configuration"></a>
## Development environment configuration

To test the ethernet examples, the development environment must be configured to use Raspberry Pi Pico.

The ethernet examples were tested by configuring the development environment for **Windows**. Please refer to the '**9.2. Building on MS Windows**' section of '**Getting started with Raspberry Pi Pico**' document below and configure accordingly.

- [**Getting started with Raspberry Pi Pico**][link-getting_started_with_raspberry_pi_pico]



<a name="hardware_requirements"></a>
## Hardware requirements

The ethernet examples use **Raspberry Pi Pico** and **WIZnet Ethernet HAT** ethernet I/O module built on WIZnet's [**W5100S**][link-w5100s] ethernet chip or **W5100S-EVB-Pico** ethernet I/O module built on [**RP2040**][link-rp2040] and WIZnet's [**W5100S**][link-w5100s] ethernet chip.

- [**Raspberry Pi Pico**][link-raspberry_pi_pico]

![][link-raspberry_pi_pico_main]

- [**WIZnet Ethernet HAT**][link-wiznet_ethernet_hat]

![][link-wiznet_ethernet_hat_main]

- [**W5100S-EVB-Pico**][link-w5100s-evb-pico]

![][link-w5100s-evb-pico_3d_main]



<a name="ethernet_example_structure"></a>
## Ethernet example structure

Ethernet examples are available at '**RP2040-HAT-C/examples/**' directory. As of now, following examples are provided.

- [**DHCP & DNS**][link-dhcp_dns]
- [**HTTP**][link-http]
	- [**Server**][link-http_server]
- [**Loopback**][link-loopback]
- [**MQTT**][link-mqtt]
	- [**Publish**][link-mqtt_publish]
	- [**Subscribe**][link-mqtt_subscribe]
- [**SNTP**][link-sntp]
- [**TCP Client over SSL**][link-tcp_client_over_ssl]

Note that **ioLibrary_Driver** is needed to run ethernet examples. This library is applicable to WIZnet's W5x00 ethernet chip and is located in the '**RP2040-HAT-C/libraries/**' directory.

- [**ioLibrary_Driver**][link-ioLibrary_driver]



<a name="Ethernet_example_testing"></a>
## Ethernet example testing

Please refer to 'README.md' in each examples directory to find detail guide for testing ethernet examples.



<!--
Link
-->

[link-getting_started_with_raspberry_pi_pico]: https://datasheets.raspberrypi.org/pico/getting-started-with-pico.pdf
[link-w5100s]: https://docs.wiznet.io/Product/iEthernet/W5100S/overview
[link-rp2040]: https://www.raspberrypi.org/products/rp2040/
[link-raspberry_pi_pico]: https://www.raspberrypi.org/products/raspberry-pi-pico/
[link-raspberry_pi_pico_main]: https://github.com/Wiznet/RP2040-HAT-C/blob/main/static/images/getting_started/raspberry_pi_pico_main.png
[link-wiznet_ethernet_hat]: https://docs.wiznet.io/Product/Open-Source-Hardware/wiznet_ethernet_hat
[link-wiznet_ethernet_hat_main]: https://github.com/Wiznet/RP2040-HAT-C/blob/main/static/images/getting_started/wiznet_ethernet_hat_main.png
[link-w5100s-evb-pico]: https://docs.wiznet.io/Product/iEthernet/W5100S/w5100s-evb-pico
[link-w5100s-evb-pico_3d_main]: https://github.com/Wiznet/RP2040-HAT-C/blob/main/static/images/getting_started/w5100s-evb-pico_3d_main.png
[link-dhcp_dns]: https://github.com/Wiznet/RP2040-HAT-C/tree/main/examples/dhcp_dns
[link-http]: https://github.com/Wiznet/RP2040-HAT-C/tree/main/examples/http
[link-http_server]: https://github.com/Wiznet/RP2040-HAT-C/tree/main/examples/http/server
[link-loopback]: https://github.com/Wiznet/RP2040-HAT-C/tree/main/examples/loopback
[link-mqtt]: https://github.com/Wiznet/RP2040-HAT-C/tree/main/examples/mqtt
[link-mqtt_publish]: https://github.com/Wiznet/RP2040-HAT-C/tree/main/examples/mqtt/publish
[link-mqtt_subscribe]: https://github.com/Wiznet/RP2040-HAT-C/tree/main/examples/mqtt/subscribe
[link-sntp]: https://github.com/Wiznet/RP2040-HAT-C/tree/main/examples/sntp
[link-tcp_client_over_ssl]: https://github.com/Wiznet/RP2040-HAT-C/tree/main/examples/tcp_client_over_ssl
[link-ioLibrary_driver]: https://github.com/Wiznet/ioLibrary_Driver
