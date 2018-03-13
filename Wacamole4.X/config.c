/*
 * File:   config.c

 */


#include "config.h"
#include <xc.h>
#define _XTAL_FREQ 8000000

void configBoard() {

    //Interrupts setting
    
    INTCONbits.GIE = 1;    //Enable1/Disable0 global
    INTCONbits.PEIE = 1;    //Peripheral Interrupt Enable1/Disable0
  /*  INTCONbits.INT0IE = 0;  //INT0 External Interrupt Enable1/Disable0
    INTCONbits.TMR0IE = 0;  //Overflow Interrupt Enable1/Disable0*/
    
 
    
 
    //wait_in_ms settings
    //**** NO MOVER ***
    T0CONbits.TMR0ON = 1;   //Timer0 On/Off Control
    T08BIT = 1;             //Timer0 8-Bit/16-Bit Control (1 8-bit, 0 16-bit)
    T0CONbits.T0CS = 0;     //Timer0 Clock Source Select (1 T0CKI, 0 Internal)
    //T0CONbits.T0SE = 0;   //Timer0 Source Edge Select (0 rising, 1 falling)
    T0CONbits.PSA = 0;      //Timer0 Prescaler Assignment
    T0CONbits.T0PS = 100;   //Timer0 Prescaler Select
    INTCONbits.TMR0IF = 0;  //TMR0 Overflow Interrupt Flag (1 overflowed, 0 CLEARED)

    ADCON1bits.PCFG = 0b1111;//opcion de todos los pines en digitales
            

    TRISA=0b00000000; //set all pins of PORT A as output*/
    TRISB=0b00000000; //set all pins of PORT A as output*/

  
//  TRISB=1;
  
  TRISBbits.RB0=1;//entrada INT0
  TRISBbits.RB1=1;//entrada INT1
  TRISBbits.RB2=1;//entrada INT2
  TRISBbits.RB4=1;//INT RBIF
  
  //habilitar interrupciones
  INTCONbits.RBIE=0;//habilita la interrupcion
  INTCONbits.RBIF=0;//flag 0

  INTCONbits.INT0E=1;
  INTCON3bits.INT1E=1;
  INTCON3bits.INT2E=1;
  
  INTCONbits.INT0F=0;
  INTCON3bits.INT1F=0;
  INTCON3bits.INT2F=0;
  
  
   INTCON2bits.INTEDG0 =1;    //External Interrupt 0 Edge Select (1 rising, 0 falling)
 INTCON2bits.INTEDG1 = 1;   //External Interrupt 1 Edge Select (1 rising, 0 falling)
 INTCON2bits.INTEDG2 = 1;    //External Interrupt 2 Edge Select (1 rising, 0 falling)     
 INTCON2bits.RBIP=1;
          
 
 ADCON0 = 0b00000111;
 
              TRISD=0;
              PORTA=0;
  
}

void wait_in_ms(int time_in_ms){
    unsigned int count = 0;
    unsigned int count_ms = 0;
    unsigned int flag = 0;
    
    TMR0L = 131; 
    
     //Para 1ms : count_ms=3
    count_ms = ((8000000)*0.001)/((256-TMR0L)*32);   //Prescaler = 32
    
    TMR0ON = 1;
    
    while (count < count_ms){  
        if(TMR0IF == 1){
            TMR0IF = 0;
            TMR0L = 131;
            count ++;
            if (count == count_ms){
               flag++;
               if (flag != time_in_ms){
                   count = 0;
               }
               else{
                   count = count_ms;
                   }
            }
        }
    }
}
void wait_in_us(unsigned int microseconds){
    unsigned int micro;
    micro = 0;
    
    while (micro < microseconds) {
        __delay_us(1);
        micro++;
    }
}



