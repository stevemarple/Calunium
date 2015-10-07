#include <ctype.h>

/* ADCTest.ino
 * Author: Steve Marple
 * License: GNU General Public License version 2 
 *
 * Example sketch to demonstrate using the analogue to digital
 * converters, and how to change the analogue reference.
 *
 * The output of all ADCs are continously printed to the serial port,
 * with a 1s delay between each set of readings. The analogue
 * reference can be changed during operation by sending one of the
 * following characters:
 *     1: Set analog reference to INTERNAL1V1");
 *     2: Set analog reference to INTERNAL2V56");
 *     d: Set analog reference to DEFAULT (Vcc)");
 *     e: Set analog reference to EXTERNAL");
 * Sending h (or ?) prints help information about the characters which
 * are accepted.
 */

char *str = "DEFAULT (Vcc)";
void setup(void)
{
  Serial.begin(9600);
  analogReference(DEFAULT);
}


void loop(void)
{
  if (Serial.available()) {
    char c = Serial.read();
    switch (tolower(c)) {
    case '1':
      analogReference(INTERNAL1V1);
      str = "INTERNAL1V1";
      break;
    case '2':
      analogReference(INTERNAL2V56);
      str = "INTERNAL2V56";
      break;
    case 'd':
      analogReference(DEFAULT);
      str = "DEFAULT (Vcc)";
      break;
    case 'e':
      analogReference(EXTERNAL);
      str = "EXTERNAL";
      break;
    case 'h':
    case '?':
      Serial.println("Help: ");
      Serial.println("  1: Set analog reference to INTERNAL1V1");
      Serial.println("  2: Set analog reference to INTERNAL2V56");
      Serial.println("  d: Set analog reference to DEFAULT (Vcc)");
      Serial.println("  e: Set analog reference to EXTERNAL");
      break;
      
    };
    
  }
  delay(10);
  Serial.println("===== ===== ===== =====");
  Serial.print("Analog reference: ");
  Serial.println(str);
  for (int i = 0; i < NUM_ANALOG_INPUTS; ++i) {
    Serial.print("A");
    Serial.print(i);
    Serial.print(" (");
    Serial.print(analogInputToDigitalPin(i));
    Serial.print("): ");
    Serial.println(analogRead(analogInputToDigitalPin(i)));
  }
  delay(1000);
}
