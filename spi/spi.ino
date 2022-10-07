#include "spi.h"

SPI spi;
void setup(){
  spi.masterBegin(3,3,10,0);
}

void loop(){
  PORTB &= ~(1<<PORTB2);
  spi.transmit(0xF5);
  spi.transmit(255);
  spi.receive();
  PORTB |= (1<<PORTB2);
}
