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
      unsigned char   dc ;
    OSCCON=0x72;  // use internal oscillator frequency USA EL CRISTAL, NO SE CAMBIA SIN IMPORTAR QUE CRITSAL SE USA
    
     configBoard();
    lcd_iniciar();      //Se inicializa el LCD
   
     //setup para generador con PWM
    TRISCbits.RC2=0;//ccp1 output para PWM
     //PR2 + 1 = ((1/cristal) x cristal) / 16
  //  PWM period = [(PR2) + 1] x 4 x Tosc x (TMR2 prescale value)
    //1/1k=(pr2+1)(1/8M)*16)
    PR2=0b01111100;
    CCPR1L=0b01001010;
    T2CON=0b00000111;
    CCP1CON=0b00111100;//pwm modo y no decimal
    TMR2=0;//timer2 limpio
    TMR2ON=1;//timer ON 
    
    
    while(1)       {    
       
             /*   for(dc = 0 ; dc < 128 ; dc++)
                        {
                        CCPR1L = dc ;
                        CCPR2L = 128 - dc ;
                        wait_in_ms(10) ;
                        }
                for(dc = 127 ; dc > 0 ; dc--)
                        {
                        CCPR1L = dc ;
                        CCPR2L = 128 - dc ;
                        wait_in_ms(10) ;
                        }*/
    }  
    
}