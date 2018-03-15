/*
 * File:   ECG.c
 * Author: Administrador
 *
 * Created on 25 de febrero de 2018, 04:28 PM
 */

#include <xc.h>            // use this for ANSI C and CCI conformance. See docus under CCI
#include <stdlib.h>        // always throw this one in, it is basic functions
#include <stdio.h>        // use this one for communications stuff, else try leaving it out if not needed
#include <pic18f4550.h>
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
    OSCCON=0x72;  // use internal oscillator frequency USA EL CRISTAL, NO SE CAMBIA SIN IMPORTAR QUE CRITSAL SE USA
    TRISC=0;
     configBoard();
    lcd_iniciar();      //Se inicializa el LCD
    USART_Init(9600);  /* initialize USART operation with 9600 baud rate */ 
    MSdelay(50);
    while(1)   {
                lcd_origen();
               static char temp[12];//array donde se guarda el dato entrante, longitud maxima + 2
               USART_ReceiveString(&temp, sizeof temp );//enviamos la direccion en la memoria del array y su longitud
             USART_SendString(temp);//enviamos lo que recibimos para verificar que este correcto
             lcd_limpiar();//se limpia la lcd
            lcd_texto(temp);//se imprime lo que recibimos
            if(!strcmp("on",temp)){//si lo que recibimos es = on
                PORTCbits.RC2=1;//se prende el led
            }
            else{//sino
                PORTCbits.RC2=0;//se apaga
            }
              memset(temp, 0, sizeof temp);//vacia la memoria del array que recibe mensajes, para usarlo con diferentes tamaños
    }
    
}