/*I2C ADDRESS MPU9250
AD0 = 0
AD0 = 1
1101000
1101001*/


void setup() {
  Serial.begin(9600);
}

void loop() {
  SPI_masterInit();
  PORTB &= ~(1<<PORTB2);
  SPI_masterTransmit(0xE8);
  SPI_masterTransmit(0);
  unsigned char x = SPI_masterReceiver();
  Serial.println(x);
}


void SPI_masterInit(){
  //Set SCK, MOSI and SS output
  DDRB = 0X2C;        //PORTB|=(1<<PORTB5)|(1<<PORTB3)|(1<<PORTB2)
  //Make HIGH PB2(Slave Select(SS)) 
  PORTB = 0x04;       //PORTB|=(1<<PORTB2)
  //Enable SPI, master and set SCK frequency = fclk/128
  SPCR = 0X4F;        //SPCR|=(1<<SPE)|(1<<MSTR)|(1<<(CPOL))|(1<<SPR1)|1<<SPR0)
}

void SPI_masterTransmit(unsigned char data){
  SPDR = data;         
  while(!(SPSR & (1<<SPIF)));   //wait until SPIF set
}

unsigned char SPI_masterReceiver(){
  SPDR = 0xFF;
  while(!(SPSR & (1<<SPIF)));    //wait until SPIF set
  return SPDR;
}
