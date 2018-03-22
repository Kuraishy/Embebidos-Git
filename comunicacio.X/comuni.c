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

 static char Input[22];//array donde se guarda el dato entrante, longitud maxima + 2

 static char Input2;
  int i=0;
  int memoriaAnterior;
  unsigned char banderaSerial=0;
  void setInput(char *temp);

void main()
{
    OSCCON=0x72;  // use internal oscillator frequency USA EL CRISTAL, NO SE CAMBIA SIN IMPORTAR QUE CRITSAL SE USA
    TRISC=0;
     configBoard();
    lcd_iniciar();      //Se inicializa el LCD
    USART_Init(9600);  /* initialize USART operation with 9600 baud rate */ 
    MSdelay(50);
        PIE1bits.RCIE=1;
        
    while(1)   {
                lcd_origen();
             
                
          //   USART_SendString(Input);//enviamos lo que recibimos para verificar que este correcto
            // lcd_limpiar();//se limpia la lcd
                char text;
                lcd_limpiar();
            lcd_texto(Input);//se imprime lo que recibimos
                
                  USART_SendString(Input);
            if(!strcmp("on",Input)){
                PORTCbits.RC2=1;
            }
            else if(!strcmp("off",Input)){
                PORTCbits.RC2=0;
            }
 memset(Input, 0, sizeof Input);
            wait_in_ms(500);
         
    }
    
}

void interrupt test(){
            
    if(RCIF){
            char temp=RCREG;
                 //      lcd_texto(temp);
           if(temp>=97 && temp <=122 || temp==32){//vemos si ese char es una letra o un espacio (ASCII)                Input[i]=RCREG;
                  Input[i]=temp;   
                    i++;               
            }
           else{
       
                     i=0;     
            }       
      }
}
        

    
/*
void interrupt test(){
    
    if(RCIF){
            INTCONbits.GIE = 0;    //Enable1/Disable0 global
            char *test=&Input;
          setInput(RCREG);//recibimos un char
          
         TXREG=Input;              
         
                 //    if(!strcmp("on",Input)){//si lo que recibimos es = on
         if(Input=='d'){
                PORTCbits.RC2=1;//se prende el led
            }
        INTCONbits.GIE = 1;    //Enable1/Disable0 global
      
      }
        
    }

void setInput(char *temp){
    Input=temp;
}

*/
