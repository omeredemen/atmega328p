#ifdef Arduino
  #include "Arduino.h" 
  #include <avr/io.h>
#endif

#include "spi.h"

void SPI::masterBegin(uint8_t dataMode, uint8_t frequency, uint8_t csPin, uint8_t bitOrder){
    DDRB =0x28;
    pinMode(csPin,OUTPUT);
    digitalWrite(csPin,HIGH);   //it will change
    if(bitOrder){
        SPCR = 0x70;            //SPCR |= (1<<SPE)|(1<<MSTR)
    }
    else{
        SPCR = 0x50;            //SPCR |= (1<<SPE)|(1<<MSTR)|(1<<DORD)
    }
    SPCR = 0x50;
    
    configDataMode(dataMode);
    configClock(frequency);
}

void SPI::masterBegin(){
    return masterBegin(0,0,10,0);
}

/*              SPI Modes

                   CPOL        CPHA
spi mode 0          0           0
spi mode 1          0           1
spi mode 2          1           0
spi mode 3          1           1                               
*/

void SPI::configDataMode(uint8_t dataMode){
    switch (dataMode)
    {
    case 0:
        SPCR |= (0<<CPOL) | (0<<CPHA);
        break;
    case 1:
        SPCR |= (0<<CPOL) | (1<<CPHA);
        break;
    case 2:
        SPCR |= (1<<CPOL) | (0<<CPHA);
        break;
    case 3:
        SPCR |= (1<<CPOL) | (1<<CPHA);
        break;
    default:
        break;
    }
}

/*                              SCK Frequency

                     SPI2X            SPR1            SPR0           SCK Frequency
frequency 0            0               0               0               fosc/4
frequency 1            0               0               1               fosc/16
frequency 2            0               1               0               fosc/64
frequency 3            0               1               1               fosc/128
frequency 4            1               0               0               fosc/2
frequency 5            1               0               1               fosc/8
frequency 6            1               1               0               fosc/32
frequency 7            1               1               1               fosc/64
*/

void SPI::configClock(uint8_t frequency){
    switch (frequency)
    {
    case 0:
        SPSR |= (0<<SPI2X);
        SPCR |= (0<<SPR1) | (0<<SPR0);
        break;
    case 1:
        SPSR |= (0<<SPI2X);
        SPCR |= (0<<SPR1) | (1<<SPR0);
        break;
    case 2:
        SPSR |= (0<<SPI2X);
        SPCR |= (1<<SPR1) | (0<<SPR0);
        break;    
    case 3:
        SPSR |= (0<<SPI2X);
        SPCR |= (1<<SPR1) | (1<<SPR0);
        break;
    case 4:
        SPSR |= (1<<SPI2X);
        SPCR |= (0<<SPR1) | (0<<SPR0);
        break;   
    case 5:
        SPSR |= (1<<SPI2X);
        SPCR |= (0<<SPR1) | (1<<SPR0);
        break;
    case 6:
        SPSR |= (1<<SPI2X);
        SPCR |= (1<<SPR1) | (0<<SPR0);
        break;
    case 7:
        SPSR |= (1<<SPI2X);
        SPCR |= (1<<SPR1) | (1<<SPR0);
        break; 
    default:
        break;
    }
}

void SPI::transmit(uint8_t data){
    SPDR = data;
    while(!(SPSR & (1<<SPIF)));
}

uint8_t SPI::receive(){
    return SPDR;
}
