/*
 * File:   ECG.c
 * Author: Administrador
 *
 * Created on 25 de febrero de 2018, 04:28 PM
 */

#include <xc.h>            // use this for ANSI C and CCI conformance. See docus under CCI
#include <stdlib.h>        // always throw this one in, it is basic functions
#include <stdio.h>        // use this one for communications stuff, else try leaving it out if not needed
//#include "plib\usart.h"
#include<usart.h>

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
#include <string.h>



#define _XTAL_FREQ 80000000


           
void main()
{
    OSCCON=0x72;  /* use internal oscillator frequency
                               //  which is set to 8 MHz */
 //   OSCCON= 01110010;
   // OSCCON=01100000;
    TRISC=0;
     configBoard();
    lcd_iniciar();      //Se inicializa el LCD
    USART_Init(9600);  /* initialize USART operation with 9600 baud rate */ 
    MSdelay(50);
    while(1)   {
                lcd_origen();
                
              //  char temp[6];//para 4 caracteres
                char temp[6];
           /*    for(int i=0;i<5;i++){
                    temp[i]=NULL;
                }*/
USART_ReceiveString(&temp, sizeof temp );
           
             USART_SendString(temp);
             lcd_limpiar();
            lcd_texto(temp);
            if(!strcmp("on",temp)){
                PORTCbits.RC2=1;
            }
            else{
                PORTCbits.RC2=0;
            }
              memset(temp, 0, sizeof temp);
    }
    
}