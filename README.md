# Calunium

Calunium is an Arduino clone using the ATmega164A, ATmega164PA
ATmega324A, ATmega324PA, ATmega644A, ATmega644PA, ATmega1284 or
ATmega1284P microcontroller. The layout is designed for easy assembly
and maximum compatibility with the Arduino Uno, with additional
functionality being compatible with the Arduino Mega(2560).

## License

Unless indicated otherwise hardware is released under the Creative
Commons Attribution-ShareAlike 3.0 Unported (CC BY-SA 3.0)
http://creativecommons.org/licenses/by-sa/3.0/

Unless indicated otherwise software is released under the GNU Lesser
General Public License, version 2.1.
http://www.gnu.org/licenses/lgpl-2.1.html

## Versions

A brief description of the versions is given below. In each case
peripherals can be omitted form the build if not need.

### Stripboard version

The analogue pin mapping differs slightly for the stripboard
version. For more information see
http://blog.stevemarple.co.uk/2011/08/introducing-calunium-arduino-clone.html

### PCB version 1

Includes a real-time clock and LM61 temperature sensor. Standard
Arduino headers and JTAG, FTDI and auxillary power connectors. USB
connector for power and V-USB interface (not confirmed to work). Can
be operated at 3.3V or 5V depending upon build configuration. Not
jumper selectable. For more information see
http://blog.stevemarple.co.uk/2011/11/calunium-pcb-version.html.

### PCB version 2

Includes real-time clock, micro-SD socket, RFM12B radio module, and
LM61 temperature sensor. Arduino 1.0 headers with IOREF and dedicated
I2C pins. JTAG, FTDI and auxillary power connectors.  USB connector
for power only. Jumper-selectable 3.3V or 5V operation. For more
information see
http://blog.stevemarple.co.uk/2012/12/calunium-version-2.html

### PCB version 2.1

Includes MCP2200 USB-UART converter, real-time clock, micro-SD socket,
RFM12B radio module, and LM61 temperature sensor. Arduino 1.0 headers
with IOREF and dedicated I2C pins. JTAG and auxillary power
connectors. If the MCP2200 is fitted then the FTDI connector cannot be
fitted, but the USB socket is enabled for data. If the MCP2200 is not
fitted the FTDI connector can be, but the USB socket is for power
only. Jumper-selectable 3.3V or 5V operation. For more information see

The headers include
IOREF and dedicated I2C pins. For more information see
http://blog.stevemarple.co.uk/2013/02/calunium-version-21.html and
http://blog.stevemarple.co.uk/2012/12/calunium-version-2.html.

## Bootloader

Xboot and OptiBoot bootloaders are included. To avoid too many items
in boards menu the optiboot versions are commented out.

The xboot source files can be found at
https://github.com/stevemarple/xboot.
