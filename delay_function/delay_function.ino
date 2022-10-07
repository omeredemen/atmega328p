void setup() {
  DDRB = 0x01; //PB0 pinini çıkış olarak tanımladık
}

void loop() {
  PORTB |= 1<<0;
  new_delay(1000);
  PORTB &= ~(1<<0);
  new_delay(1000);
}

void new_delay(int mili_sn){
  //Presclar 32
  TCCR0B |= (1 << CS00);
  TCCR0B |= (1 << CS01);
  TCCR0B &= ~(1 << CS02);
  //TCCR0B = 0x07;
  TCNT0 = 0; //TCNT0'ı 0'ladık.
  
  int count = 0;

  while(mili_sn){
    if(TCNT0 >= 249){
      TCNT0 = 0;
      mili_sn--;
    }         
  } 
}
