/*MPU9250
AD0 = 0
AD0 = 1
1101000
1101001*/

#include "SPI_master.h"

void setup() {
  SPI_masterInit(); 
}

void loop() {
  PORTB &= ~(1<<PORTB2);
  SPI_masterTransmit(0xF5);
  SPI_masterTransmit(0);
  SPI_masterReceiver();
  PORTB |= (1<<PORTB2);
}
