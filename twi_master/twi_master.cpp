#include "twi_master.h"
#include  <avr/io.h>
#include <stdint.h>

int master_init(){                 //It is working 
  
  TWBR = 0x48;                     //For 100 KHz SCL Frequancy
}           
int TWI_start(void){
  // Clear TWI interrupt flag, Put start condition on SDA, Enable TWI
  TWCR= 0xA4;  
  while(!(TWCR & (1<<TWINT))); // Wait till start condition is transmitted
    //return 0;
  int st = TWSR&0xF8;
  if(st != 0x08 && st != 0x10) // Check for the acknowledgement
    return st;
}
int start_condition(){             //It is working
  TWCR = 164;                     //TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
  while(!(TWCR & (1<<TWINT)))return 0;     //Wait until TWI finish it's job
  int st = TWSR&0xF8;              //What is inside TWSR?
  if(st == 0x08) return 1;        // Cheking ACK  
  else return st;
}

void repeated_start_condition(){
  TWCR = 0xA4;                     //TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);       
  while(!(TWCR & (1<<TWINT)));     // Wait until TWI finish it's job   
  unsigned char st = TWSR&0xF8;    //What is inside TWSR?
  while(st != 0x10) break;         // Cheking ACK  
}

unsigned char write_address(unsigned char SLA_W){
  TWDR = SLA_W;                    //load the slave writing address to TWDR
  TWCR = 0X84;                     //TWCR = (1<<TWINT) | (1<<TWEN)
  while(!(TWCR & (1<<TWINT)))return 0;     // Wait until TWI finish it's job
  unsigned char st = TWSR&0xF8;        //What is inside TWSR?
  if(st == 0x18)                   // Cheking ACK 
    return 1;
  else 
    return st;
}

unsigned char write_data(unsigned char data){
  TWDR = data;                     //load the data we want to sent to TWDR
  TWCR = 0X84;                     //TWCR = (1<<TWINT) | (1<<TWEN);
  while(!(TWCR & (1<<TWINT)));     // Wait until TWI finish it's job
  unsigned char st = TWSR&0xF8;              //What is inside TWDR?
  if(st == 0x28)                   // Cheking ACK 
    return 1;
  else return 0;  
}

unsigned char read_address(unsigned char SLA_R){
  TWDR = SLA_R;                    //load the slave reading address to TWDR
  TWCR = 0X84;                     //TWCR = (1<<TWINT) | (1<<TWEN)
  while(!(TWCR & (1<<TWINT)));     // Wait until TWI finish it's job
  unsigned char st = TWSR&0xF8;    //What is inside TWSR?
  if(st == 0x40)                   // Cheking ACK 
    return 1; 
  else 
    return st;
}

uint8_t read_Ack(){
    TWCR = 0xC4;                   // (1<<TWEN)|(1<<TWINT)|(1<<TWEA); 
    while(!(TWCR&(1<<TWINT)));     // Wait until TWI finish its job
    return TWDR;                   // Return received data 
}

unsigned char read_Nack(){               
    TWCR= 0x84;                    //(1<<TWEN)|(1<<TWINT); 
    while(!(TWCR&(1<<TWINT)));     // Wait until TWI finish its job
    return TWDR;                   // Return received data 
}

void twi_stop(){
  TWCR = 0x94;                     //TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO) 
  while(!(TWCR & (1<<TWSTO)));  
}
