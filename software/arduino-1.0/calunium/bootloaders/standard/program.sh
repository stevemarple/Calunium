#!/bin/sh
MCU=m1284p
PORT=usb
PROGRAMMER=dragon_jtag

avrdude -p $MCU -P $PORT -c $PROGRAMMER -e -Ulock:w:0xFF:m -Uefuse:w:0xfd:m -Uhfuse:w:0x98:m -Ulfuse:w:0xFF:m -Ulock:w:0x0F:m

avrdude -p $MCU -P $PORT -c $PROGRAMMER -F -U flash:w:atmega1284p_12MHz.hex


