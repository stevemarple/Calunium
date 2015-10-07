/*
 * RTCInterrupts.ino
 * Author: Steve Marple
 * License: Gnu General Public License version 2 
 *
 * Example sketch to demonstrate the real-time clock outputting a 1Hz
 * square wave which is used as an interrupt. The interrupt service
 * routine indicates that it has been called by setting
 * clockedTicked. Every run of loop() checks if the clockedTicked is
 * true; if so it is set to false and a tick mark (#) printed to the
 * console. The current seconds value is printed every 200ms, from
 * this it can be deduced that a falling interrupt setting is needed
 * to mark the start of the second boundary.
 *
 * Requirements:
 *   Arduino >= 1.0
 *   RealTimeClockDS1307, see
 *     https://github.com/davidhbrown/RealTimeClockDS1307
 *
 *   Calunium configuration:
 *     RTC (DS1307 or similar) fitted, with battery
 *     RTC square wave routed to D6 (JP4 fitted for SQW)
 */

#include <Wire.h>
#include <RealTimeClockDS1307.h>

uint8_t rtcInput = 6;

// Use an 8-bit variable to obtain atomic read/write access. Disabling
// interrupts is therefore not needed.
volatile uint8_t clockTicked = false;

void rtcISR(void)
{
  clockTicked = true;
}

void setup(void)
{
  pinMode(SS, OUTPUT); // Prevent SPI slave mode from happening
  Wire.begin();
  Serial.begin(9600);
  pinMode(rtcInput, INPUT);

  // Enable inputs on this pin 15 in case JP1 fitted to route SQW there also
  pinMode(15, INPUT); 

  RTC.sqwEnable(RealTimeClockDS1307::SQW_1Hz);
  attachInterrupt(2, rtcISR, FALLING);
}

unsigned long last = 0;
void loop(void) 
{
  if (clockTicked) {
    clockTicked = false;
    Serial.println("#"); 
  }

  unsigned long now = millis();
  if (now > last + 200) {
    last = now;
    char buffer[20];
    RTC.readClock();
    Serial.println(RTC.getSeconds());
  }
}
