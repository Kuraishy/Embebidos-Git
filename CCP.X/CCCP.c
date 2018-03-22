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

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "config.h"
#include "lcd.h"
#include "definicionPines.h"
#include <time.h>
#include <string.h>
#define _XTAL_FREQ 80000000
#define f_timer 2000000 //temp del timer FOSC/4

unsigned char turno=0;

void main()
{
    OSCCON=0x72;  // use internal oscillator frequency USA EL CRISTAL, NO SE CAMBIA SIN IMPORTAR QUE CRITSAL SE USA

     configBoard();
    lcd_iniciar();      //Se inicializa el LCD
   
   unsigned long signal_period,data1,data2;
    unsigned long frequency_Hz[20];
    float Frequency;
    TRISC2=1; //CCP1 como Input
    OSCCON=0x72;        /* set internal clock to 8MHz */
 
    memset(frequency_Hz,0,20);//

 
    PIE1bits.CCP1IE=1;
    PIR1bits.CCP1IF=0;     
    CCP1CON=0x05;       /* Capture mode is selected for detecting Rising edge */
    CCPR1=0x00;         /*CCPR1 is capture count Register which is cleared initially*/
    TMR1IF=0;           
    T1CON=0x80;         /* Enable 16-bit TMR1 Register,No pre-scale,use internal clock,Timer OFF */
    TMR1=0; 
    TMR1ON=1; /* Turn-On Timer1 */	     
    while(1)       {    
        while(!(PIR1bits.CCP1IF));  /*Wait for Interrupt flag which is generated when edge is detected*/
        PIR1bits.CCP1IF=0;
        data1 = CCPR1;              /*Copy count of 1st edge detected*/        
            
        while(!(PIR1bits.CCP1IF));  /*Wait for Interrupt flag which is generated when edge is detected*/
        PIR1bits.CCP1IF=0;
        data2 = CCPR1;              /*Copy count of 2nd edge detected*/

        if(data1 < data2)
           {

            /*Calculation for Frequency Measurement*/
            signal_period = data2 - data1;
            Frequency = ((float)f_timer / (float)signal_period); /*Count for 1 cycle*0.5us gives period */
            sprintf(frequency_Hz,"%.3f  ",Frequency); 

           
            
            } 
        TMR1=0;
        memset(frequency_Hz,0,20);
    }  
    
}

void interrupt test(){
    if(CCP1IF){
        CCP1IF=0;
         if(turno==0){
               data1 = CCPR1;              //Copy count of 1st edge detected   
               turno=1;
         }else if(turno==1){
             data2=CCPR1;
             turno=0;
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
