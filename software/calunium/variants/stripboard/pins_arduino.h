/*
  pins_arduino.h - Pin definition functions for Arduino
  Part of Arduino - http://www.arduino.cc/

  Copyright (c) 2007 David A. Mellis

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library; if not, write to the
  Free Software Foundation, Inc., 59 Temple Place, Suite 330,
  Boston, MA  02111-1307  USA

  $Id: wiring.h 249 2007-02-03 16:52:51Z mellis $
*/

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

#include <avr/pgmspace.h>

const static uint8_t SS   = 10;
const static uint8_t MOSI = 11;
const static uint8_t MISO = 12;
const static uint8_t SCK  = 13;

const static uint8_t SDA = 20;
const static uint8_t SCL = 21;
const static uint8_t LED_BUILTIN = 13;

const static uint8_t A0 = 24;
const static uint8_t A1 = 25;
const static uint8_t A2 = 26;
const static uint8_t A3 = 27;
const static uint8_t A4 = 28;
const static uint8_t A5 = 29;
const static uint8_t A6 = 30;
const static uint8_t A7 = 31;

/* Digital pin to PCINT
 * 0	24
 * 1	25
 * 2	26
 * 3	27
 * 4	8
 * 5	9
 * 6	10
 * 7	11
 * 8	30
 * 9	29
 * 10	12
 * 11	13
 * 12	14
 * 13	15
 * 14	23
 * 15	22
 * 16	21
 * 17	20
 * 18	19
 * 19	18
 * 20	17
 * 21	16
 * 22	28
 * 23	31
 * 24	1
 * 25	0
 * 26	2
 * 27	3
 * 28	4
 * 29	5
 * 30	6
 * 31	7
 */

#define digitalPinToPCIR(p) (((p) >= 0 && (p) <= 31) ? (&PCICR) : ((uint8_t *)0))
#define digitalPinToPCICRbit(p) \
  (((p) >= 24 && (p) <= 31) ? 0 :					\
   (((p) >= 4 && (p) <= 7) || ((p) >= 10 && (p) <= 13)) ? 1 :		\
   ((p) >= 14 && (p) <= 21) ? 2 : 3)
#define digitalPinToPCMSK(p) \
  (((p) >= 24 && (p) <= 31) ? &PCMSK0 :			      \
   (((p) >= 4 && (p) <= 7) || ((p) >= 10 && (p) <= 13)) ? &PCMSK1 : \
   ((p) >= 14 && (p) <= 21) ? &PCMSK2 : \
   (((p) >= 0 && (p) <= 3) || (p) == 8 || (p) == 9 || (p) == 22 || (p) == 23) ? &PCMSK3 : ((uint8_t *)0))
#define digitalPinToPCMSKbit(p)			\
  (((p) == 0) ? 0 :				\
   ((p) == 1) ? 1 :				\
   ((p) == 2) ? 2 :				\
   ((p) == 3) ? 3 :				\
   ((p) == 4) ? 0 :				\
   ((p) == 5) ? 1 :				\
   ((p) == 6) ? 2 :				\
   ((p) == 7) ? 3 :				\
   ((p) == 8) ? 6 :				\
   ((p) == 9) ? 5 :				\
   ((p) == 10) ? 4 :				\
   ((p) == 11) ? 5 :				\
   ((p) == 12) ? 6 :				\
   ((p) == 13) ? 7 :				\
   ((p) == 14) ? 7 :				\
   ((p) == 15) ? 6 :				\
   ((p) == 16) ? 5 :				\
   ((p) == 17) ? 4 :				\
   ((p) == 18) ? 3 :				\
   ((p) == 19) ? 2 :				\
   ((p) == 20) ? 1 :				\
   ((p) == 21) ? 0 :				\
   ((p) == 22) ? 4 :				\
   ((p) == 23) ? 7 :				\
   ((p) == 24) ? 1 :				\
   ((p) == 25) ? 0 :				\
   ((p) == 26) ? 2 :				\
   ((p) == 27) ? 3 :				\
   ((p) == 28) ? 4 :				\
   ((p) == 29) ? 5 :				\
   ((p) == 30) ? 6 :				\
   ((p) == 31) ? 7 : 0)

#ifdef ARDUINO_MAIN

const uint16_t PROGMEM port_to_mode_PGM[] = {
	NOT_A_PORT,
	(uint16_t) &DDRA,
	(uint16_t) &DDRB,
	(uint16_t) &DDRC,
	(uint16_t) &DDRD,
};

const uint16_t PROGMEM port_to_output_PGM[] = {
	NOT_A_PORT,
	(uint16_t) &PORTA,
	(uint16_t) &PORTB,
	(uint16_t) &PORTC,
	(uint16_t) &PORTD,
};

const uint16_t PROGMEM port_to_input_PGM[] = {
	NOT_A_PIN,
	(uint16_t) &PINA,
	(uint16_t) &PINB,
	(uint16_t) &PINC,
	(uint16_t) &PIND,
};

const uint8_t PROGMEM digital_pin_to_port_PGM[] = {
	// PORTLIST		
	// -------------------------------------------		
	PD	, //  0, PD0 (PCINT24/RXD0/T3)
	PD	, //  1, PD1 (PCINT25/TXD0)
	PD	, //  2, PD2 (PCINT26/RXD1/INT0)
	PD	, //  3, PD3 (PCINT27/TXD1/INT1)
	PB      , //  4, PB0 (PCINT8/XCK0/T0)
	PB      , //  5, PB1 (PCINT9/CLKO/T1)
	PB      , //  6, PB2 (PCINT10/INT2/AIN0)
	PB      , //  7, PB3 (PCINT11/OC0A/AIN1)

	PD      , //  8, PD6 (PCINT30/OC2B/ICP)
	PD      , //  9, PD5 (PCINT29/OC1A)
	PB      , // 10, PB4 (PCINT12/OC0B/!SS)
	PB      , // 11, PB5 (PCINT13/ICP3/MOSI)
	PB      , // 12, PB6 (PCINT14/OC3A/MISO)
	PB      , // 13, PB7 (PCINT15/OC3B/SCK)
	// Reminder are provisonal. This mapping makes SDA/SCL have
	// same digital numbers as for Mega2560
	PC      , // 14, PC7 (TOSC2/PCINT23)
	PC      , // 15, PC6 (TOSC1/PCINT22)

	PC      , // PC5 (TDI/PCINT21)
	PC      , // PC4 (TDO/PCINT20)
	PC      , // PC3 (TMS/PCINT19)
	PC      , // PC2 (TCK/PCINT18) 
	PC      , // PC1 (SDA/PCINT17) [D20]
	PC      , // PC0 (SCL/PCINT16) [D21]
	PD      , // PD4 (PCINT28/XCK1/OC1B)
	PD      , // PD7 (OC2A/PCINT31)

	PA,
	PA,
	PA,
	PA,
	PA,
	PA,
	PA,
	PA,
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = {
	// PIN IN PORT		
	// -------------------------------------------		
        _BV( 0 )        , // PD0 (PCINT24/RXD0/T3)
	_BV( 1 )        , // PD1 (PCINT25/TXD0)
	_BV( 2 )        , // PD2 (PCINT26/RXD1/INT0)
	_BV( 3 )        , // PD3 (PCINT27/TXD1/INT1)
	_BV( 0 )        , // PB0 (PCINT8/XCK0/T0)
	_BV( 1 )        , // PB1 (PCINT9/CLKO/T1)
	_BV( 2 )        , // PB2 (PCINT10/INT2/AIN0)
	_BV( 3 )        , // PB3 (PCINT11/OC0A/AIN1)

	_BV( 6 )        , // PD6 (PCINT30/OC2B/ICP)
	_BV( 5 )        , // PD5 (PCINT29/OC1A)
	_BV( 4 )        , // PB4 (PCINT12/OC0B/!SS)
	_BV( 5 )        , // PB5 (PCINT13/ICP3/MOSI)
	_BV( 6 )        , // PB6 (PCINT14/OC3A/MISO)
	_BV( 7 )        , // PB7 (PCINT15/OC3B/SCK)
	_BV( 7 )        , // PC7 (TOSC2/PCINT23)
	_BV( 6 )        , // PC6 (TOSC1/PCINT22)

	_BV( 5 )        , // PC5 (TDI/PCINT21)
	_BV( 4 )        , // PC4 (TDO/PCINT20)
	_BV( 3 )        , // PC3 (TMS/PCINT19)
	_BV( 2 )        , // PC2 (TCK/PCINT18) 
	_BV( 1 )        , // PC1 (SDA/PCINT17) [D20]
	_BV( 0 )        , // PC0 (SCL/PCINT16) [D21]
	_BV( 4 )        , // PD4 (PCINT28/XCK1/OC1B)
	_BV( 7 )        , // PD7 (OC2A/PCINT31)

	_BV ( 1 )       , // PA1 (ADC1/PCINT1)
	_BV ( 0 )       , // PA0 (ADC0/PCINT0)
	_BV ( 2 )       , // PA2 (ADC2/PCINT2)
	_BV ( 3 )       , // PA3 (ADC3/PCINT3)
	_BV ( 4 )       , // PA4 (ADC4/PCINT4)
	_BV ( 5 )       , // PA5 (ADC5/PCINT5)
	_BV ( 6 )       , // PA6 (ADC6/PCINT6)
	_BV ( 7 )       , // PA7 (ADC7/PCINT7)
};

const uint8_t PROGMEM digital_pin_to_timer_PGM[] = {
	// TIMERS		
	// -------------------------------------------		
	NOT_ON_TIMER, 	/* D0  - PD0 */
	NOT_ON_TIMER, 	/* D1  - PD1 */
	NOT_ON_TIMER, 	/* D2  - PD2 */
	NOT_ON_TIMER, 	/* D3  - PD3 */
	NOT_ON_TIMER, 	/* D4  - PB0 */
	NOT_ON_TIMER, 	/* D5  - PB1 */
	NOT_ON_TIMER, 	/* D6  - PB2 */
	TIMER0A,     	/* D7  - PB3 */

	TIMER2B,     	/* D8  - PD6 */
	TIMER1A,     	/* D9  - PD5 */
	TIMER0B,	/* D10 - PB4 */
	NOT_ON_TIMER, 	/* D11 - PB5 */
	TIMER3A, // NOT_ON_TIMER, 	/* D12 - PB6 */
	TIMER3B, // NOT_ON_TIMER,	/* D13 - PB7 */
	//  *** The remaining mappings are provisional  ***
	NOT_ON_TIMER,   /* D  - PC7 */
	NOT_ON_TIMER,   /* D  - PC6 */

	NOT_ON_TIMER,   /* D  - PC5 */
	NOT_ON_TIMER,   /* D  - PC4 */
	NOT_ON_TIMER,   /* D  - PC3 */
	NOT_ON_TIMER,   /* D  - PC2 */
	NOT_ON_TIMER,   /* D  - PC1 */
	NOT_ON_TIMER, 	/* D  - PC0 */
	TIMER1B,     	/* D  - PD4 */
	TIMER2A,     	/* D  - PD7 */
	
	NOT_ON_TIMER,   /* D  - PA1 */
	NOT_ON_TIMER,   /* D  - PA0 */
	NOT_ON_TIMER,   /* D  - PA2 */
	NOT_ON_TIMER,   /* D  - PA3 */
	NOT_ON_TIMER,   /* D  - PA4 */
	NOT_ON_TIMER,   /* D  - PA5 */
	NOT_ON_TIMER,   /* D  - PA6 */
	NOT_ON_TIMER,   /* D  - PA7 */

};

#endif

#endif
