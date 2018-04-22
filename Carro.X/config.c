/*
 * File:   config.c

 */


#include "config.h"
#include <xc.h>
#define _XTAL_FREQ 8000000

void configBoard() {

    //Interrupts setting
    
    INTCONbits.GIE = 0;    //Enable1/Disable0 global
    INTCONbits.PEIE = 0;    //Peripheral Interrupt Enable1/Disable0
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
            
/*
    TRISA=0b00000000; //set all pins of PORT A as output
    TRISB=0b00000000; //set all pins of PORT A as output

  */
//  TRISB=1;
  

 
  ADCON0 = 0b00000111;
          /*ADC******************************************************/

    ADCON0bits.ADON = 0;    //ADC is shut-off; consumes no operating power
  //  ADCON0bits.CHS = 0000;  //Analog Channel Select AN0
   // ADCON1bits.VCFG = 0b00;     //Voltage Reference Configuration (VREF- VREF+ source) (VDD VSS source)  
    //ADCON1bits.PCFG = 0b0111;  //A/D Port Configuration Control (Digital o Analog)
    ADCON2bits.ADFM = 1;     //A/D Result Format Select Justified (1 right, 0 left)
    ADCON2bits.ADCS = 0b110;   //A/D Conversion Clock Select TADmin 0.7 us(48MHz/64= 1.33us = TAD)
    ADCON2bits.ACQT = 0b101;   // A/D Acquisition Time Select (12TAD)
  // ADCON1bits.PCFG=0b1101;//A0 y A1es analogico (1))
  TRISAbits.RA1=1;//Puerta A0 (2)
  ADCON2bits.ADCS=0b110;//reloj conversion adc(3a))
  ADCON1bits.VCFG1=0;// VSS (3b)
  ADCON1bits.VCFG0=0;//Vdd (3b)
  //ADCON0bits.CHS=0b000;// seleccionar canal de entrada (3c)
  ADCON2bits.ADFM=1;//seleccionar justificacion (3d)7  
  //ADCON1bits.PCFG=0b1011;//A0, A1, A2 y A3 es analogico (1))
  //TRISAbits.RA0=1;//Puerta A0 (2)
  //TRISAbits.RA1=1;//puerta A1
  ADCON0bits.ADON=0;//encender el a/d module(3e)
  
   PIE1bits.ADIE=0;//activa interrupcion del adc(4))
  PIR1bits.ADIF=0;//bandera de la interrupcion(4))

  ADCON2bits.ACQT=0b111;//tiempo adquisicion (5)
  ADCON0bits.GO=1;//Prende el ciclo?
 
  RCIF=0;

 
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




