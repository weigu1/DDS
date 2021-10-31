/* dds_arduino_uno_256v_8b.ino
 * weigu.lu 
 * N = 32, P = 8, B = 8, res = 0.000008.466 Hz 
 * 1kHz Sinus DDS 
 * PWM output on pin 11 connected to low-pass
 * offset = fout*2^N/fCLK = 1000Hz*2^32/36363Hz = 118113668
 */

#include "sine_table_256_values_8_bit.h"

const uint8_t PIN_PWM_TIMER2A = 11; // PWM output on Uno
uint32_t phase_offset = 118113668;
uint32_t phase_accumulator = 0x00000000;
uint8_t  address_pointer = 0x00;

/* Timer1 interrupt calculates the pointer, gets the value
   for the PWM from the table and outputs it */
ISR(TIMER1_COMPA_vect){   
  phase_accumulator = phase_accumulator + phase_offset;
  address_pointer = phase_accumulator >> 24; // shift 3 byte
  OCR2A = SINE_256V_8B[address_pointer];  
}

void setup() {   
  pinMode(PIN_PWM_TIMER2A, OUTPUT);  
  cli();         // stop interrupts
  /* Set Timer2 register to FastPWM */
  TCCR2A = 0xA3;
  TCCR2B = 0x01; // no prescaling (f_PWM = 16MHz/256 = 62,5kHz)
  /* Set Timer1 for Timer interrupt */
  TCCR1A = 0;  
  TCCR1B = 0x0A; // turn on CTC mode prescaler = 2
  OCR1A = 54;   // f = 2MHz / (OCCR1A + 1) = 36363Hz
  TIMSK1 = 0x02; // enable timer compare interrupt
  sei();         //allow interrupts
}

void loop() { // everything in the ISR
}
