#define LED 13   //PB5
#define BUTON 12 //PB4

void setup() {
  DDRB  = 0B00100000;
  PORTB = 0B00000000;
  }

void loop() {
  bool a = PINB & (1<<4);
  if(a == 0){
    PORTB = PORTB | (1<<5);  //PB5 1 olur
  }
    else{
    PORTB = ~(1<<5) & PORTB;  // PB5 0 olur
  }
}
