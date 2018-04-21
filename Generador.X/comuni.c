/*
 * File:   ECG.c
 * Author: Administrador
 *
 * Created on 25 de febrero de 2018, 04:28 PM
 */


#include <pic18f4550.h>

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "config.h"
#include "lcd.h"
#include "definicionPines.h"
#include <time.h>
#include <string.h>
#define _XTAL_FREQ 80000000
#define tiempo 2000000 //temp del timer FOSC/4


void main()
{

    OSCCON=0x72;  // use internal oscillator frequency USA EL CRISTAL, NO SE CAMBIA SIN IMPORTAR QUE CRITSAL SE USA
    
     configBoard();
    lcd_iniciar();      //Se inicializa el LCD
   
     //setup para generador con PWM
    TRISCbits.RC2=0;//ccp1 output para PWM
     //PR2 + 1 = ((1/cristal) x cristal) / 16
  //  PWM period = [(PR2) + 1] x 4 x Tosc x (TMR2 prescale value)
    //1/1k=(pr2+1)(1/8M)*16)
   // PR2=0b01111100;
  /*  CCPR1L=0b01001010;
  //  T2CON=0b00000111;
    CCP1CON=0b00111100;//pwm modo y no decimal
    TMR2=0;//timer2 limpio
    TMR2ON=1;//timer ON 
    */
          unsigned char   dc ;
    
 
PR2 = 0b11111001 ;
T2CON = 0b00000101 ;
CCPR1L = 0b01111100 ;
CCP1CON = 0b00111100 ;
     
     
    while(1)       {    
    
        for(dc = 0 ; dc < 255 ; dc+=12)   {
                        CCPR1L = dc ;
                        CCPR2L = 128 - dc ;
                        wait_in_ms(300) ;
                        }
        
                for(dc = 254 ; dc > 0 ; dc-=12)
                        {
                        CCPR1L = dc ;
                        CCPR2L = dc-128 ;
                        wait_in_ms(300) ;
                        }
        
        
                }
    }  
    
