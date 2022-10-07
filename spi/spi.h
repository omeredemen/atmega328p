#ifndef _SPI_H
#define _SPI_H

#ifndef Arduino
  #include "Arduino.h" 
  #include <avr/io.h>
#endif

#include <stdint.h>


class SPI{
    public:
        void    masterBegin(uint8_t dataMode, uint8_t frequency, uint8_t csPin, uint8_t bitOrder);
        void    masterBegin();
        void    configDataMode(uint8_t dataMode);
        void    configClock(uint8_t frequency);
        void    transmit(uint8_t data);
        uint8_t receive();
};


#endif
