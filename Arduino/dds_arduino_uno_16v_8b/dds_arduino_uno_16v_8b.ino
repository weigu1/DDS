/* dds_arduino_uno_16v_8b.ino
 * weigu.lu  
 * N = 12, P = 4, B = 8, res = 8.8777Hz
 * PWM output on pin 11 connected to low-pass
 * fout = fCLK/offset*2^N, fout = 8,877Hz/offset
 */

const uint8_t SINE_16V_8B[16] {
  0x80,0xb0,0xda,0xf5,0xff,0xf5,0xda,0xb0,
  0x80,0x4f,0x25,0xa,0x00,0x0a,0x25,0x4f  
};

const uint8_t PIN_PWM_TIMER2A = 11; // PWM output on Uno
uint16_t phase_offset = 560;
uint16_t phase_accumulator = 0x0000;
uint8_t  address_pointer = 0x00;

/* Timer1 interrupt calculates the pointer, gets the value
   for the PWM from the table and outputs it */
ISR(TIMER1_COMPA_vect){   
  phase_accumulator = (phase_accumulator + phase_offset) % 4096;
  address_pointer = phase_accumulator >> 8; // shift 3 byte
  OCR2A = SINE_16V_8B[address_pointer];    
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
