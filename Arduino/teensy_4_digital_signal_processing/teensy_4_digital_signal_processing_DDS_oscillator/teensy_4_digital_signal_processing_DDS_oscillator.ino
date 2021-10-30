/*
 * weigu.lu
 * based on an article of Martin Ossmann Funkamateur 4/21
 */


#include "sine_table_4096_12_bit.h"

uint32_t phase,local_oscillator;

void setup() {
  Serial.begin(115200);
  phase = 0xABCD;
  local_oscillator=SINE_4096[(phase>>20) & 0xFFF]; // get value from table
  Serial.print(local_oscillator,HEX);

}

void loop() {
}

  //Phase += frequency ;               // DDS phase erhoehen
  //LO=DDStable[(phase>>20) & 0xFFF] ; // get value from table
  //mix=ADCval*LO ;                    // Multiplikation
  //out=IIRdo(lowPass1,mix) ;          // Tiefpass filtern
