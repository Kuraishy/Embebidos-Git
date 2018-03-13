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
#include "VariableGlobal.h"
#define buzzer PORTCbits.RC1

#define VALORMUERTOBAJO  -10
#define VALORMUERTOALTO 50
#define VALORPICO 3.8



#define _XTAL_FREQ 80000000



void pacienteMuerto(float testv);
 //   extern int pulsoCorazonX=0;



  
void main(void) {
    
        configBoard();
    
    lcd_iniciar();      //Se inicializa el LCD
        OSCCON=0x72;              /* use internal oscillator frequency
                                 which is set to * MHz */
        char data_in;
   // TRISD = 0;                /* set PORT as output port */
         USART_Init(9600);         /* initialize USART operation with 9600 baud rate */ 
        MSdelay(50);
         unsigned int an1;

       int pulsoCorazonX=0;
      
    
       ADCON0bits.CHS = 0b0001;
         float  voltaje_an1 = 0; 
         char str[3]; 
          int pulsos_test=0;
          int pulsoCorazonY=0;
           

    while(1){

   //   data_in=USART_ReceiveChar();
   
                 
                 
              wait_in_ms(2);
            an1 = ADC_Read(1);  // Se lee y almacena el valor ADC
            voltaje_an1 = (an1 * 4.47)/1023; // Se convierte el valor ADC a voltaj

        sprintf(str,"%1.2f\n",voltaje_an1);
         USART_SendString(str); //send LED ON status to terminal

         pacienteMuerto(an1);
         if(voltaje_an1>VALORPICO){
             
             TRISBbits.RB0=0;
             PORTBbits.RB0=1;
             wait_in_ms(50);
             PORTBbits.RB0=0;
         
         }

                wait_in_ms(2);     //Espera tiempo de adquisicion    }
/*
      char str3[4];
      sprintf(str3," %d",pulsoCorazonX);
          
      lcd_texto(str3);*/


     MSdelay(150);
          lcd_origen();
            /*   if(pulsos_test==30){
                   pulsos_test=0;
               }
*/
     


        }


  
     
      return;

     
    }
      
      
      
       
  //  }
    
    


    

void pacienteMuerto(float testv){
     
    if(testv<VALORMUERTOALTO && testv>VALORMUERTOBAJO){
        buzzer=1;
          
    }
 
    else
    {

        buzzer=0;
    }

          /*    if(pulsos_test%33==0){
      
    //     pulsos_test=0;
           char str2[4];
             lcd_origen();
            lcd_limpiar();
         //   int temp=*pulsosCorazonX;
        // sprintf(str2," %d PPM",temp*10);

          
   //   lcd_texto(str2);
  
     // *pulsosCorazonX=0;
            */
     
  
}

    
 




