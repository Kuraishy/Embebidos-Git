

#include "USART_Header_File.h"
#include "config.h"
#include <xc.h>
#include <string.h>
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
    //RCSTA=0x90;                     /*Receive Enable(RX) enable and serial port enable */
    RCSTA=0x94;
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


void USART_ReceiveString(char *Input, unsigned char length)
{
    //unsigned char bool=0;
   // int i=0;
       for(int i=0;i<=length-2;i++) {
     // if(RCREG!=0){
   // while(bool==0){
      Input[i]=0;         
      RCREG=0;
     
      char temp=USART_ReceiveChar();
          if(temp>=97 && temp <=122 || temp==32){
                  Input[i] =temp;
         }else{
          Input[i+1]=0;
          i=length-1;
         // bool=1;
         }
      temp=0;//}
  }  
  
   
}
///////////////////////
/*
void USART_ReceiveString(char *Input, unsigned char length)
{
   
  for(int i=0;i<=length-2;i++) {
      Input[i]=0;         
      RCREG=0;
      while(RCIF==0);             
//      Char.IsLetter(RCREG);
      char temp=RCREG;
          if(temp>=97 && temp <=122){
                  Input[i] =temp;
         }else
          Input[i+1]=0;
        }  
}
 * */



/*TOLERANCIA RECIBE 4 y puede RECIBIR 3 sin perderse
void USART_ReceiveString(char *Input, unsigned char length)
{
   
  for(int i=0;i<=length-2;i++) {
      Input[i]=0;
                
      RCREG=0;
      while(RCIF==0);             
//      Char.IsLetter(RCREG);
      if(RCREG>=97 && RCREG <=122){
              Input[i] =RCREG;
      }else
          Input[i]=0;
  }
  //Input[length-2]=0;
  
}
*/


/*ESTE SIRVEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE
void USART_ReceiveString(char *Input, unsigned char length)
{
   
  for(int i=0;i<=length-2;i++) {
      Input[i]=0;
                
      RCREG=0;
      while(RCIF==0);                 //wait for receive interrupt flag
      

              Input[i] =RCREG;

  }
  Input[length-2]=0;
  
}
*/
