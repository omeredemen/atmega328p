#ifndef twimaster
#define twimaster
#include <stdint.h>

int TWI_start();
int master_init();
int start_condition();
void repeated_start_condition();
unsigned char write_address(unsigned char SLA_W);
unsigned char write_data(unsigned char data);
unsigned char read_address(unsigned char SLA_R);
uint8_t read_Ack();
unsigned char read_Nack();
void twi_stop();

#endif
