#include "SPI_master.h"
#include  <avr/io.h>

void SPI_masterInit(){
  //Set SCK, MOSI and SS output
  DDRB = 0X2C;        //PORTB|=(1<<PORTB5)|(1<<PORTB3)|(1<<PORTB2)
  //Make HIGH PB2(Slave Select(SS)) 
  PORTB = 0x04;       //PORTB|=(1<<PORTB2)
  //Enable SPI, master and set SCK frequency = fclk/128
  SPCR = 0X5F;        //SPCR|=(1<<SPE)|(1<<MSTR)|(1<<CPHA)|(1<<CPOL)|(1<<SPR1)|1<<SPR0)
  
}

void SPI_masterTransmit(unsigned char data){
  SPDR = data;         
  while(!(SPSR & (1<<SPIF)));   //wait until SPIF set
}

unsigned char SPI_masterReceiver(){
  SPI_masterTransmit(0xFF);    
  return SPDR;
}
