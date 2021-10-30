/* wavetable_arduino_uno_256v_8b.ino
 * weigu.lu 
 * PWM output on pin 11 connected to low-pass 100nF, 270 Ohm
 */

#include "sine_table_256_values_8_bit.h"

const uint8_t PIN_PWM_TIMER2A = 11; // PWM output on Uno
const uint8_t TABLE_POINTER_INCREMENT = 10; // every value
uint8_t table_pointer = 0;

/* Timer1 interrupt gets table values and outputs them */
ISR(TIMER1_COMPA_vect){   
  OCR2A = SINE_256V_8B[table_pointer];
  table_pointer = table_pointer + TABLE_POINTER_INCREMENT;  
}

void setup() {   
  pinMode(PIN_PWM_TIMER2A, OUTPUT);  
  cli();         // stop interrupts
  /* Set Timer2 register to FastPWM */
  TCCR2A = 0xA3;
  TCCR2B = 0x01; // no prescaling (f_PWM = 16MHz/256 = 62,5kHz)
  /* Set Timer1 for Timer interrupt */
  TCCR1A = 0;  
  TCCR1B = 0x09; // turn on CTC mode no prescaler
  OCR1A = 159;   // f = 16MHz / (OCCR1A - 1) = 100kHz
  TIMSK1 = 0x02; // enable timer compare interrupt
  sei();         //allow interrupts
}

void loop() { // everything in the ISR
}

  //Phase += frequency ;               // DDS phase erhoehen
  //LO=DDStable[(phase>>20) & 0xFFF] ; // get value from table
  //mix=ADCval*LO ;                    // Multiplikation
  //out=IIRdo(lowPass1,mix) ;          // Tiefpass filtern
