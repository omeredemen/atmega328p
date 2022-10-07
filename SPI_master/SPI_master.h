#ifndef SPI_master
#define SPI_master

void SPI_masterInit();
void SPI_masterTransmit(unsigned char data);
unsigned char SPI_masterReceiver();

#endif
