# Software examples

These software examples should work unchanged on a Calunium, for other
ATmega*4 devices you may need to use a different pin number; make sure
you use the same MCU pin as here. Arduino users will probably need to
make some changes; see the comments in the code.

## RTCInterrupts

An example sketch which uses Calunium's on-board real-time clock to
create interrupts which are processed by the INT2 interrupt service
routine.

## RTCPinChangeInterrupts

An example sketch which uses Calunium's on-board real-time clock to
create pin-change interrupts.

## RTCTimerCounter

An example sketch which uses Calunium's on-board real-time clock to
drive the counter stage of timer/counter2. When the counter reaches a
predetermined value (but not overflow) an interrupt is generated.

## RTCSquareWaveOff

An example sketch to turn off the square wave output of the real-time
clock.
