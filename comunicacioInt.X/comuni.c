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


       static char dataIn[22];//array donde se guarda el dato entrante, longitud maxima + 2
       static char temp;
       
       void USART_test(char *Input, unsigned char length);//usa un poitner de un array y su longitud
void main()
{
    OSCCON=0x72;  // use internal oscillator frequency USA EL CRISTAL, NO SE CAMBIA SIN IMPORTAR QUE CRITSAL SE USA
    TRISC=0;
     configBoard();
   // lcd_iniciar();      //Se inicializa el LCD
    USART_Init(9600);  /* initialize USART operation with 9600 baud rate */ 
    MSdelay(50);
    while(1)   {
               // lcd_origen();
             
              // USART_ReceiveString(&dataIn, sizeof dataIn );//enviamos la direccion en la memoria del array y su longitud
               
             USART_SendString(dataIn);//enviamos lo que recibimos para verificar que este correcto
          //   lcd_limpiar();//se limpia la lcd
        //    lcd_texto(dataIn);//se imprime lo que recibimos
            if(!strcmp("on",dataIn)){//si lo que recibimos es = on
                PORTCbits.RC2=1;//se prende el led
            }
            else{//sino
                PORTCbits.RC2=0;//se apaga
            }
              memset(dataIn, 0, sizeof dataIn);//vacia la memoria del array que recibe mensajes, para usarlo con diferentes tamaños
    }
    
}

void interrupt interrupcion(){
    if(RCIF){
     USART_test(&dataIn,sizeof dataIn);
     
     PORTCbits.RC2=1;

        
        
    }
}


void USART_test(char *Input, unsigned char length)//usa un poitner de un array y su longitud
{
 
       for(int i=0;i<=length-2;i++) {//un ciclo, el total de espacios usados va a ser de la longitud del array - 2, debido al error y al terminador
      Input[i]=0;         //limpiamos el registro
      
       char temp=  RCREG;                  

          if(temp>=97 && temp <=122 || temp==32){//vemos si ese char es una letra o un espacio (ASCII)
                  Input[i] =temp;//si es una letra o espacio se guarda en el array
                 RCREG=0;          //limpiamos el registro
         }else{//si es otra cosa (basura)
          Input[i+1]=0;//crea un terminador pues ya terminamos de recibir info, recibimos basura
          i=length-1;//salte del ciclo for
         // bool=1;
         }
      temp=0;//se limpia el registro
  }
       
       for(int i=0;i<length-1;i++){
           Input[i]=Input[i+1];
  
       }
       
}
