// PWM MODE WİTH TC0, NO PRESCALER
// OC0A => PD6


void setup() {
  DDRD = 0XFF;
  TCNT0 = 0;
  OCR0A = 10;              // SET PWM
  TCCR0A |= (1 << COM0A1) | (1 << COM0A0); //COMPRE OUTPUT MODE
  TCCR0A |= (1 << WGM00);  //SELECT PWM,PHASE CORRECT MODE
  TCCR0B |= (1 << CS00);   //SELECT 1 PRESCALER
   
}

void loop() {
  
}
