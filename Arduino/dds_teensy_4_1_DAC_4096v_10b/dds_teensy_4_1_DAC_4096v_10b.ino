/* dds_teensy_4_0_4096v_10b.ino
 * weigu.lu 
 * N = 32, P = 8, B = 10, res = 0.00023283Hz!
 * 1kHz Sinus DDS 
 * PWM output on pin 4 with 10 bit and 146.48kHz connected to low-pass
 * ISR with 100kHz
 * offset = fout*2^N/fCLK = 1000Hz*2^32/1000000Hz = 4294967
 */

#include "sine_table_4096_values_10_bit.h"

const byte DAC1 = A21;
const byte DAC_RESOLUTION = 12;
uint32_t phase_offset = 4294967;
uint32_t phase_accumulator = 0x00000000;
uint16_t  address_pointer = 0x0000;

IntervalTimer myISR; // Create an IntervalTimer object 

/* Timer interrupt calculates the pointer, gets the value
   for the PWM from the table and outputs it */
void isr_DDS() {
  phase_accumulator = phase_accumulator + phase_offset;
  address_pointer = phase_accumulator >> 22; // shift 22 bit
  analogWrite(DAC1, PIN_PWM,SINE_4096V_10B[address_pointer]);
}

void setup() {    
  analogWriteResolution(DAC_RESOLUTION); 
  myISR.begin(isr_DDS, 1);  // 1µs -> 1Mz
  //myISR.priority(0);        // highest priority
}

void loop() { // everything in the ISR 
}
