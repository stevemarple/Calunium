/*
 * RTCInterrupts.ino
 * Author: Steve Marple
 * License: Gnu General Public License version 2 
 *
 * Example sketch to switch off the real-time clock square wave
 * output. You might wish to do this to help conserve the RTC battery.
 *
 * Requirements:
 *   Arduino >= 1.0
 *   RealTimeClockDS1307, see
 *     https://github.com/davidhbrown/RealTimeClockDS1307
 *
 *   Calunium configuration:
 *     RTC (DS1307 or similar) fitted, with battery
 */

#include <Wire.h>
#include <RealTimeClockDS1307.h>

void setup(void)
{
  // Enable inputs 6 and 15 in case the jumpers for the square-wave
  // output are fitted
  pinMode(6, INPUT);
  pinMode(15, INPUT); 

  pinMode(SS, OUTPUT); // Prevent SPI slave mode from happening
  Wire.begin();
  Serial.begin(9600);

  RTC.sqwDisable(HIGH);
  Serial.println("Real time clock square-wave output set HIGH");
}

void loop(void) 
{
  ;
}
