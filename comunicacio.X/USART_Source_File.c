

#include "USART_Header_File.h"
#include "config.h"
#include <xc.h>
#define _XTAL_FREQ 8000000
 
/*****************************USART Initialization*******************************/
void USART_Init(long baud_rate)
{
    float temp;
    TRISC6=0;                       /*Make Tx pin as output*/
    TRISC7=1;                       /*Make Rx pin as input*/
    temp=Baud_value;     
    SPBRG=(int)temp;                /*baud rate=9600, SPBRG = (F_CPU /(64*9600))-1*/
    TXSTA=0x20;                     /*Transmit Enable(TX) enable*/ 
    RCSTA=0x90;                     /*Receive Enable(RX) enable and serial port enable */
}
/******************TRANSMIT FUNCTION*****************************************/ 
void USART_TransmitChar(char out)
{        
        while(TXIF==0);            /*wait for transmit interrupt flag*/
        TXREG=out;                 /*wait for transmit interrupt flag to set which indicates TXREG is ready
                                    for another transmission*/    
}
/*******************RECEIVE FUNCTION*****************************************/
char USART_ReceiveChar()
{

    while(RCIF==0);                 /*wait for receive interrupt flag*/
    return(RCREG);                  /*receive data is stored in RCREG register and return to main program */
}



// Read specified number of chars and put them into holder array

void USART_SendString(const char *out)
{
   while(*out!='\0')
   {            
        USART_TransmitChar(*out);
        out++;
   }
}
/*********************************Delay Function********************************/
void MSdelay(unsigned int val)
{
     unsigned int i,j;
        for(i=0;i<=val;i++)
            for(j=0;j<81;j++);      /*This count Provide delay of 1 ms for 8MHz Frequency */
 }
///////////////////////

/*
void USART_ReceiveString(char *Input, unsigned char length)
{
    char temp[5];
   for(int i=0;i<length;i++){
   temp[i]=0;
   RCREG=0;
   while(RCIF==0);//wait for receive interrupt flag
     temp[i]=RCREG;
            __delay_us(150);
          
         }
      
    for(int x=0;x<length-1;x++){
        Input[x]=temp[x];
    }
      //Input++;
  }
  */

char recieveUSART()
{
    while(RCIF == 0); /*wait for receive interrupt flag*/
    if(RCSTAbits.OERR)
    {           
        CREN = 0;
        NOP();
        CREN=1;
    }
    return(RCREG);  /*received in RCREG register and return to main program */
}

/*void USART_ReceiveString(char *Input, unsigned char length)
{
   
  for(int i=0;i<length;i++) {
      Input[i]=0;
      while(RCIF==0);                 /*wait for receive interrupt flag*/ 
      /*
        if(RCREG!='\0'){
              Input[i] =RCREG;
            __delay_us(50);
         }
      RCREG=0;
  }
  
}
*/

/*RECIVE BIEN PALABRAS AL INICIO Y LUEGO BASURA, TESTFKODKFOSDFK
 void USART_ReceiveString(char *Input, unsigned char length)
{
 
   for(int i=0;i<length;i++){
   Input[i]=0;
   RCREG=0;
   while(RCIF==0);/*wait for receive interrupt flag*/ 
    /* Input[i]=RCREG;
            __delay_us(150);
          
         }
      
      //Input++;
  }
  */