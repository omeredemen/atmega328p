// FAST PWM MODE WİTH TC0 NO PRESCALER
// OC0A => PD6


void setup() {
  DDRD = 0XFF;
  OCR0A = 192; // SET DUTY CYCLE
  TCCR0A |= (1 << COM0A1) | (1 << COM0A0); //COMPARE OUTPUT MODE TO INVERTİNG
  TCCR0A |= (1 << WGM01) | (1 << WGM00);   // SELECT FAST PWM MODE
  //TCCR0B |= (1 << CS00);                   // SELECET PRESCALER
   TCCR0B = 0x03;
   //TCCR0B &= CS02;
}

void loop() {
  
}
