

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

/********************************Recibir Strigns***********************************/
void USART_ReceiveString(char *Input, unsigned char length)//usa un poitner de un array y su longitud
{
 
       for(int i=0;i<=length-2;i++) {//un ciclo, el total de espacios usados va a ser de la longitud del array - 2, debido al error y al terminador
      Input[i]=0;         //limpiamos el registro
      RCREG=0;          //limpiamos el registro
     
      char temp=USART_ReceiveChar();//recibimos un char
          if(temp>=97 && temp <=122 || temp==32){//vemos si ese char es una letra o un espacio (ASCII)
                  Input[i] =temp;//si es una letra o espacio se guarda en el array
         }else{//si es otra cosa (basura)
          Input[i+1]=0;//crea un terminador pues ya terminamos de recibir info, recibimos basura
          i=length-1;//salte del ciclo for
         // bool=1;
         }
      temp=0;//se limpia el registro
  }    
}

