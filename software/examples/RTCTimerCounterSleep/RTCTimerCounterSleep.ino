/*
 * RTCTimerCounterSleep.ino
 * Author: Steve Marple
 * License: Gnu General Public License version 2 
 *
 * Example sketch to demonstrate sleep. Waking is controlled by the
 * real-time clock outputting a 4096Hz square wave which is used as an
 * input by timer/counter2 on the ATmega1284P. An interrupt service
 * routine is called when timer/counter2 has reached its TOP (not MAX
 * or overflow) value; the ISR sets isrRan to true. Every run of
 * loop() checks if the isrRan is true; if so it is set to false and
 * the current time is printed to the console. The state of
 * LED_BUILTIN is also toggled, to flash the on-board LED.
 *
 * Precautions must be taken when then asynchronous mode of
 * timer/counter2 is used to enable wakeup, see comment in the code
 * below. Using a 1Hz signal instead of the 4096Hz signal is possible
 * but the time taken to return to sleep in increased.
 *
 * To run this sketch on a standard Arduino (ATmega168 or ATmega328)
 * you will need to use timer/counter1; define USE_CT to be 1. Use D5
 * for the input. Using timer/counter2 might be possible if your
 * ATmega328 uses the internal oscillator and the crystal is not
 * fitted.
 * 
 * This sketch will not work in asynchronous mode with an Arduino
 * Mega(2560) since the TOSC1 pin is not connected to the shield
 * headers; use one of the synchronous counters instead.
 *
 * Requirements:
 *   Arduino >= 1.0
 *   RealTimeClockDS1307, see
 *     https://github.com/davidhbrown/RealTimeClockDS1307
 *
 *   Calunium configuration:
 *     RTC (DS1307 or similar) fitted, with battery
 *     RTC square wave routed to D15 (JP1 fitted)
 */

#include <Wire.h>
#include <RealTimeClockDS1307.h>

#include <avr/sleep.h>

bool ledValue = true;

// Use an 8-bit variable to obtain atomic read/write access. Disabling
// interrupts is therefore not needed as long as only this variable is
// accessed.
volatile bool isrRan = false;

// With a 4096Hz input and divide by 1024 prescaler there are 4 counts
// per second; wakeup every 5 seconds (count = 20)
#define WAKEUP_COUNT 20

// Select which timer/counter to use
#define USE_CT 2

#if USE_CT == 1
ISR(TIMER1_COMPA_vect)
{
  isrRan = true;
}

// Configure counter/timer1. Count the falling edges to have the ticks
// occuring on the second boundary. 
void setupTimer1(void)
{
  noInterrupts();
  ASSR = _BV(AS2);
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = (WAKEUP_COUNT - 1);
  TCCR1B |= _BV(WGM12); // CTC mode
  TCCR1B |= (_BV(CS12) | _BV(CS11)); // External clock source, falling edge
  TCCR2B |= (_BV(CS12) | _BV(CS11) | _BV(CS10));  // Divide by 1024
  TIMSK1 |= _BV(OCIE1A);
  interrupts();
}

#elif USE_CT == 2
ISR(TIMER2_COMPA_vect)
{
  isrRan = true;
}

// Configure counter/timer2 in asynchronous mode, counting the rising
// edge of signals on TOSC1. This always triggers on the rising edge;
// if connecting SQW from a DS1307 then this means the ticks occur
// halfway through the second at 1Hz.
void setupTimer2(void)
{
  noInterrupts();
  ASSR = (_BV(EXCLK) | _BV(AS2));
  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;
  OCR2A = (WAKEUP_COUNT - 1); // Have the ISR called every 4th (n+1) tick
  TCCR2A |= _BV(WGM21); // CTC mode
  TCCR2B |= (_BV(CS22) | _BV(CS21) | _BV(CS20));  // Divide by 1024
  TIMSK2 |= _BV(OCIE2A);
  interrupts();
}

#else
#error "Not configured for this timer"
#endif

void doSleep(uint8_t mode)
{
  noInterrupts();
  set_sleep_mode(mode); // Set the mode
  sleep_enable();       // Make sleeping possible
  interrupts();         // Make sure wake up is possible!
  sleep_cpu();          // Now go to sleep

  // Now awake again
  sleep_disable();      // Make sure sleep can't happen until we are ready

  /*
   * Fix a suspected bug in the two-wire hardware which stops it
   * working after sleep. See
   * http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&t=22549
   */
  TWCR &= ~(_BV(TWSTO) + _BV(TWEN));
  TWCR |= _BV(TWEN); 
}


void setup(void)
{
  pinMode(SS, OUTPUT); // Prevent SPI slave mode from happening
  Wire.begin();
  Serial.begin(9600);

  // For calunium: enable inputs on pin 6 in case JP4 is fitted and
  // routing SQW there also
  pinMode(6, INPUT); 

  // Setup the LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, ledValue);
  
#if USE_CT == 1
  // Use counter/timer1. On Calunium digital pin 5 is T1, adjust for
  // if necessary your board.
  pinMode(5, INPUT); // Make T1 pin an input
  setupTimer1();

#elif USE_CT == 2
  pinMode(15, INPUT);
  setupTimer2();
#else
#error "Not configured for this timer"
#endif

  // Set up the RTC output
  RTC.sqwEnable(RealTimeClockDS1307::SQW_4kHz);
  Serial.println("Done setup()");
  delay(100);
}


unsigned long last = 0;
void loop(void) 
{
  // Print if the interrupt service routine was called, and the
  // current number of seconds in the minute
  if (isrRan) {
    isrRan = false;
    ledValue = !ledValue;
    digitalWrite(LED_BUILTIN, ledValue);
    Serial.print("***** ISR called: ");
    RTC.readClock();
    Serial.println(RTC.getSeconds());
  }

  Serial.print("In loop()"); 

  /*
   * Now sleep, but see caveat from the data sheet:
   *
   * If Timer/Counter2 is used to wake the device up from Power-save
   * or ADC Noise Reduction mode, precautions must be taken if the
   * user wants to re-enter one of these modes: The interrupt logic
   * needs one TOSC1 cycle to be reset. If the time between wake-up
   * and reentering sleep mode is less than one TOSC1 cycle, the
   * interrupt will not occur, and the device will fail to wake up. If
   * the user is in doubt whether the time before re-entering
   * Power-save or ADC Noise Reduction mode is sufficient, the
   * following algorithm can be used to ensure that one TOSC1 cycle
   * has elapsed:
   *
   * - a. Write a value to TCCR2x, TCNT2, or OCR2x.
   * - b. Wait until the corresponding Update Busy Flag in ASSR returns to zero.
   * - c. Enter Power-save or ADC Noise Reduction mode.
   */

#if USE_CT == 2
  OCR2A = (WAKEUP_COUNT - 1);
  while (ASSR & _BV(OCR2AUB))
    ; 
#endif

  doSleep(SLEEP_MODE_PWR_SAVE);
}


