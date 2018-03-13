/*
 * File:   ECG.c
 * Author: Administrador
 *
 * Created on 25 de febrero de 2018, 04:28 PM
 */



#include <pic18f4550.h>
#include "Configuration_Header_File.h"
#include "USART_Header_File.h"
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "config.h"
#include "lcd.h"
#include "definicionPines.h"
#include "funciones.h"
#include <time.h>


#define _XTAL_FREQ 80000000


           
void main()
{
    OSCCON=0x72;  /* use internal oscillator frequency
                                 which is set to 8 MHz */
    char data_in;
//    TRISD = 0;  /* set PORT as output port */
           char test3;
           configBoard();
    lcd_iniciar();      //Se inicializa el LCD
    USART_Init(9600);  /* initialize USART operation with 9600 baud rate */ 
    MSdelay(50);
    while(1)   {
                lcd_origen();

       
          
       
        
        /*data_in=USART_ReceiveChar();
        if(data_in=='a')
        {   
            lcd_limpiar();
       //     LED = 0;  //turn ON LED 
                        TRISCbits.RC2=0;
                        if(PORTCbits.RC2==1){
                            PORTCbits.RC2=0;
                        }else PORTCbits.RC2=1;
            
          //  USART_SendString("a");  // send LED ON status to terminal 
            lcd_texto("a");
             
        }
        else if(data_in=='2')
                
        {
            lcd_limpiar();
//            LED = 1;  //turn OFF LED
            TRISCbits.RC2=0;
            PORTCbits.RC2=0;
            USART_SendString("OFF");  // send LED OFF status to terminal 
            lcd_texto("OFF");
        }
        else if(data_in=='3')
        {
            lcd_limpiar();
                        TRISCbits.RC2=0;
            PORTCbits.RC2=1;
            USART_SendString("ON");  //send msg to select proper option 
            //char test2=USART_ReceiveString();
     
          /*  uart_read( 5, test3);
            lcd_texto("ON");
        }
        */
   //     MSdelay(100);
     //   lcd_limpiar();
      /*     char reci[5]; 
           int i=0;
     
    char test=USART_ReceiveChar();
    lcd_texto(test);
    lcd_origen();
   // lcd_limpiar();
  /*  while(test!='\0'){
        test=USART_ReceiveChar();
    reci[i]=test;
   i++;
    }
        

    
  lcd_texto(reci[2]);
  lcd_texto(test);
    */
                
                char temp[5];
          /*      for(int i=0;i<16;i++){
                    temp[i]=NULL;
                }*/
//USART_ReceiveString(temp, 5);
             USART_SendString(temp);
             lcd_texto(temp);

    }
    
}