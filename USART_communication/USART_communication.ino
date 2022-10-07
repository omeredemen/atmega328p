#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void setup() {
  usart_init(MYUBRR);                     // firstly, we must set initalizaiton
}

void loop() { 
  char a ;
  a = usart_Receive(); 
  usart_Transmit(a); 
}

//initalization part
void usart_init( unsigned int ubrr){
  
  //enable receiver and transmitter
  //8 data bit, 2 stop bit
  UCSR0C = 0X0E; //00001110
  UCSR0B = 0X18; //00011000
  
  //set baudrate
  UBRR0L = ubrr;      
  UBRR0H = (ubrr >> 8);
}

//receive part
unsigned char usart_Receive(){
  while (!(UCSR0A & (1 << RXC0)));     //wait for data be received 
  return(UDR0);                        //get and return received data from buffer
}

//transmission part
void usart_Transmit(char data){
  while (!(UCSR0A & (1<<UDRE0)));      //wait for empty transmit buffer
  UDR0 = data ;                       
}

void send_string(char* str){
  int j=0;
  while (*(str+j)!=0){
    usart_Transmit(*(str+j));  
    j++;
  }
}

void sendInteger(int number){
  char buffer[8];
  int i = 0;
  itoa(number, buffer, 10);
  while(*(buffer+i) != 0){
    usart_Transmit(*(buffer+i));
    i++;
  }
}

void sendfloat(float flo){
  String string = "";     // empty string
  int i = 0;
  string.concat(flo);
  while(string[i] != 0){
    usart_Transmit(string[i]);
    i++;
  }
}
