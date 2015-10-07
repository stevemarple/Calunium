# ADCTest.ino
 
Example sketch to demonstrate using the analogue to digital
converters, and how to change the analogue reference.

The output of all ADCs are continously printed to the serial port,
with a 1s delay between each set of readings. The analogue
reference can be changed during operation by sending one of the
following characters:
    1: Set analog reference to INTERNAL1V1");
    2: Set analog reference to INTERNAL2V56");
    d: Set analog reference to DEFAULT (Vcc)");
    e: Set analog reference to EXTERNAL");
Sending h (or ?) prints help information about the characters which
are accepted.

Author: Steve Marple
License: GNU General Public License version 2 

