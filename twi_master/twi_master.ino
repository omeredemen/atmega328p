/*
 * I2C ADDRESS AD0 = 0
  AD0 = 1 ->  1101001x
1101000x
MPU9250
*/
#include "twi_master.h"
#include <stdint.h>

void setup() {    
  master_init();
  Serial.begin(9600);  
}

void loop() {
  int x = TWI_start();
  Serial.println(x);
  int  y = write_address(0xD0);
  Serial.println(y);
  write_address(0x75);
  repeated_start_condition();
  read_address(0xD1);
  uint8_t z = read_Nack();
  Serial.println(z);
  twi_stop();
}

/*
void master_init(){                //It is working
  //TWCR = 0x04;                   //1<<TWEN
  TWSR = 0x00;                     //Prescale 1
  TWBR = 0x48;                     //For 100 KHz SCL Frequancy  
}           

void start_condition(){            //It is working
  TWCR = 0xA4;                     //TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);       
  while(!(TWCR & (1<<TWINT)));     // Wait until TWI finish it's job   
  int st = TWSR&0xF8;              //What is inside TWSR?
  while(st != 0x08) break;         // Cheking ACK  
}

void repeated_start_condition(){
  TWCR = 0xA4;                     //TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);       
  while(!(TWCR & (1<<TWINT)));     // Wait until TWI finish it's job   
  unsigned char st = TWSR&0xF8;              //What is inside TWSR?
  while(st != 0x10) break;         // Cheking ACK  
}

unsigned char write_address(unsigned char SLA_W){
  TWDR = SLA_W;                    //load the slave writing address to TWDR
  TWCR = 0X84;                     //TWCR = (1<<TWINT) | (1<<TWEN)
  while(!(TWCR & (1<<TWINT)));     // Wait until TWI finish it's job
  unsigned char st = TWSR&0xF8;        //What is inside TWSR?
  if(st == 0x18)                // Cheking ACK 
    return 1;
  //while(st == 0x20)return 1;     // Cheking NACK
}

unsigned char write_data(unsigned char data){
  TWDR = data;                     //load the data we want to sent to TWDR
  TWCR = 0X84;                     //TWCR = (1<<TWINT) | (1<<TWEN);
  while(!(TWCR & (1<<TWINT)));     // Wait until TWI finish it's job
  unsigned char st = TWSR&0xF8;              //What is inside TWDR?
  if(st == 0x28)                // Cheking ACK 
    return 1;
  //while(st == 0x30)return 1;  
}

unsigned char read_address(unsigned char SLA_R){
  TWDR = SLA_R;                    //load the slave reading address to TWDR
  TWCR = 0X84;                     //TWCR = (1<<TWINT) | (1<<TWEN)
  while(!(TWCR & (1<<TWINT)));     // Wait until TWI finish it's job
  unsigned char st = TWSR&0xF8;    //What is inside TWSR?
  if(st == 0x40)         // Cheking ACK 
    return 1; 
  //while(st == 0x48)return 1;  
}

unsigned char read_Ack(){
    TWCR=0xC4;                     // (1<<TWEN)|(1<<TWINT)|(1<<TWEA); 
    while(!(TWCR&(1<<TWINT)));     // Wait until TWI finish its job
    return TWDR;                   // Return received data 
}

unsigned char read_Nack(){               
    TWCR= 0xA4;                    //(1<<TWEN)|(1<<TWINT); 
    while(!(TWCR&(1<<TWINT)));     // Wait until TWI finish its job
    return TWDR;                   // Return received data 
}

void twi_stop(){
  TWCR = 0x94;                     //TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO) 
  while(!(TWCR & (1<<TWSTO)));  
}*/
