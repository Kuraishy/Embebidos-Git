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
  

 
  ADCON0 = 0b00000111;
          /*ADC******************************************************/
 
  //Analog to Digital port converter setting
    ADCON0bits.ADON = 0;    // ENABLES ADC
    ADCON0bits.GODONE = 0;  //Starts the conversion
    
    ADCON0bits.CHS0 = 0;    //ANALOG CHANNEL SELECTION
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS2 = 0;
    ADCON0bits.CHS3 = 0;
    
    ADCON1bits.VCFG0 = 0;   //VALUE OF Vref+ (0 = 5V)
    ADCON1bits.VCFG1 = 0;   //VALUE OF Vref- (0 = GND)
    
    ADCON1bits.PCFG0 = 1;   //ANALOG OR DIGITAL PINS
    ADCON1bits.PCFG1 = 1;
    ADCON1bits.PCFG2 = 0;
    ADCON1bits.PCFG3 = 1;
    
    ADCON2bits.ADFM = 1;    //RESULT RIGHT JUSTIFIED
   
    ADCON2bits.ACQT0 = 0;   //ACQUISITION TIME
    ADCON2bits.ACQT1 = 0;
    ADCON2bits.ACQT2 = 1;
    
    ADCON2bits.ADCS0 = 0;   //CONVERSION CLOCK
    ADCON2bits.ADCS1 = 1;
    ADCON2bits.ADCS2 = 1  ;
  

  TRISAbits.RA1=1;//Puerta A0 (2)
  ADCON0bits.ADON=1;//encender el a/d module(3e)
   PIE1bits.ADIE=1;//activa interrupcion del adc(4))
  PIR1bits.ADIF=0;//bandera de la interrupcion(4))

  //ADCON2bits.ACQT=0b111;//tiempo adquisicion (5)
  ADCON0bits.GO=1;//Prende el ciclo?
 

 
              TRISD=0;
              PORTA=0;
              TRISCbits.RC1=0;
  
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



