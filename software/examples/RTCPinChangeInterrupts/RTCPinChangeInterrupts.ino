/*
 * RTCPinChangeInterrupts.ino
 * Author: Steve Marple
 * License: Gnu General Public License version 2 
 *
 * Example sketch to demonstrate the real-time clock outputting a 1Hz
 * square wave which is used as a pin-change interrupt. The interrupt
 * service routine indicates that it has been called by setting
 * pinChanged. Every run of loop() checks if pinChanged is true; if so
 * it is set to false and a mark (#) printed to the console. The
 * current seconds value is printed every 200ms. The interrupt service
 * routine is called on rising and falling edges.
 *
 * Requirements:
 *   Arduino >= 1.0
 *   RealTimeClockDS1307, see
 *     https://github.com/davidhbrown/RealTimeClockDS1307
 *   Calunium configuration:
 *     RTC (DS1307 or similar) fitted, with battery
 *     RTC square wave routed to D6 (JP4 fitted for SQW)
 */

#include <Wire.h>
#include <RealTimeClockDS1307.h>

#define NO_PORTA_PINCHANGES
#define NO_PORTB_PINCHANGES
#define NO_PORTD_PINCHANGES
#define DISABLE_PCINT_MULTI_SERVICE

// The pin number used for the real-time clock
#define RTC_INPUT 15

// Use an 8-bit variable to obtain atomic read/write access. Disabling
// interrupts is therefore not needed.
volatile uint8_t pinChanged = false;

// Only one ISR needs to be defined, but which is it?
#if digitalPinToPCICRbit(RTC_INPUT) == 0
ISR(PCINT0_vect){
  pinChanged = true;
}
#endif
#if digitalPinToPCICRbit(RTC_INPUT) == 1
ISR(PCINT1_vect){
  pinChanged = true;
}
#endif
#if digitalPinToPCICRbit(RTC_INPUT) == 2
ISR(PCINT2_vect){
  pinChanged = true;
}
#endif
#if digitalPinToPCICRbit(RTC_INPUT) == 3
ISR(PCINT3_vect){
  pinChanged = true;
}
#endif

void setupPinChangeInterrupts(void)
{
  *(digitalPinToPCMSK(RTC_INPUT)) |= _BV(digitalPinToPCMSKbit(RTC_INPUT));
  *(digitalPinToPCIR(RTC_INPUT)) |= _BV(digitalPinToPCICRbit(RTC_INPUT));
}

void setup(void)
{
  pinMode(SS, OUTPUT); // Prevent SPI slave mode from happening
  Wire.begin();
  Serial.begin(9600);
  pinMode(RTC_INPUT, INPUT);

  // For Calunium: enable inputs on this pin 6 in case JP1 fitted to
  // route SQW there also
  pinMode(6, INPUT); 

  setupPinChangeInterrupts();
  RTC.sqwEnable(RealTimeClockDS1307::SQW_1Hz);
}

unsigned long last = 0;
void loop(void) 
{
  if (pinChanged) {
    pinChanged = false;
    Serial.println("#"); 
  }

  unsigned long now = millis();
  if (now > last + 200) {
    last = now;
    RTC.readClock();
    Serial.println(RTC.getSeconds());
  }
}
