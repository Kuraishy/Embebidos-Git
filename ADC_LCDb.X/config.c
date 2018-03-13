/*
 * File:   config.c
 * Author: renatosoriano
 *
 * Created on January 13, 2017, 4:01 PM
 */

#include "config.h"
#include <xc.h>

void configBoard() {
    ADCON0bits.ADON = 0;    //ADC is shut-off; consumes no operating power
  //  ADCON0bits.CHS = 0000;  //Analog Channel Select AN0

    ADCON1bits.VCFG = 0b11;     //Voltage Reference Configuration (VREF- VREF+ source) (VDD VSS source)  
    ADCON1bits.PCFG = 0b0111;  //A/D Port Configuration Control (Digital o Analog)
    
    ADCON2bits.ADFM = 1;     //A/D Result Format Select Justified (1 right, 0 left)
    ADCON2bits.ADCS = 0b110;   //A/D Conversion Clock Select TADmin 0.7 us(48MHz/64= 1.33us = TAD)
    ADCON2bits.ACQT = 0b101;   // A/D Acquisition Time Select (12TAD)
    
    //ADCON1 != 0b00001111;
    //ADCON1 != 0x0F;
    //ADCON1 != 15;
    
    TRISA = _INPUT;
    TRISB = _OUTPUT;  //Entradas por INT0, INT1, INT2
    TRISC = _OUTPUT;  //TRISC = 0x00 OR 0b00000000
    TRISD = _OUTPUT;
    TRISE = _OUTPUT;
    
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    
    LED_TRIS = _OUTPUT;
    LED2_TRIS = _OUTPUT;
    SW1_TRIS = _INPUT;
    
    //Interrupts setting
    IPEN = 0;
    INTCONbits.GIE = 0;     //Enable1/Disable0 global
    INTCONbits.PEIE = 1;    //Peripheral Interrupt Enable1/Disable0
    INTCONbits.INT0IE = 1;  //INT0 External Interrupt Enable1/Disable0
    INTCONbits.TMR0IE = 1;  //Overflow Interrupt Enable1/Disable0
    
    INTCON2bits.INTEDG0 = 1;    //External Interrupt 0 Edge Select (1 rising, 0 falling)
    INTCON2bits.INTEDG1 = 1;    //External Interrupt 1 Edge Select (1 rising, 0 falling)
    INTCON2bits.INTEDG2 = 1;    //External Interrupt 2 Edge Select (1 rising, 0 falling)
    
    INTCON3bits.INT1IP = 0; //INT1 External Interrupt Priority (1 high p, 0 low p)
    INTCON3bits.INT2IP = 0; //INT2 External Interrupt Priority (1 high p, 0 low p)
    INTCON3bits.INT1IE = 1; //INT1 External Interrupt Enable1/Disable0
    INTCON3bits.INT2IE = 1; //INT2 External Interrupt Enable1/Disable0

    PIE1bits.ADIE = 0;  //A/D Converter Interrupt Enable1/Disable0    
    PIR1bits.ADIF = 0;  //A/D Converter Interrupt Flag
    
     
    //wait_in_ms settings
    //**** NO MOVER ***
    T0CONbits.TMR0ON = 1;   //Timer0 On/Off Control
    T08BIT = 1;             //Timer0 8-Bit/16-Bit Control (1 8-bit, 0 16-bit)
    T0CONbits.T0CS = 0;     //Timer0 Clock Source Select (1 T0CKI, 0 Internal)
    //T0CONbits.T0SE = 0;   //Timer0 Source Edge Select (0 rising, 1 falling)
    T0CONbits.PSA = 0;      //Timer0 Prescaler Assignment
    T0CONbits.T0PS = 100;   //Timer0 Prescaler Select
    INTCONbits.TMR0IF = 0;  //TMR0 Overflow Interrupt Flag (1 overflowed, 0 CLEARED)

    
    
      ADCON1bits.PCFG=0b1110;//A0 es analogico (1))
  TRISAbits.RA0=1;//Puerta A0 (2)
  ADCON2bits.ADCS=0b110;//reloj conversion adc(3a))
  ADCON1bits.VCFG1=0;// VSS (3b)
  ADCON1bits.VCFG0=0;//Vdd (3b)
  //ADCON0bits.CHS=0b000;// seleccionar canal de entrada (3c)
  ADCON2bits.ADFM=1;//seleccionar justificacion (3d)7  
  ADCON1bits.PCFG=0b1011;//A0, A1, A2 y A3 es analogico (1))
  TRISAbits.RA0=1;//Puerta A0 (2)
  TRISAbits.RA1=1;//puerta A1
  ADCON0bits.ADON=1;//encender el a/d module(3e)
  
   PIE1bits.ADIE=1;//activa interrupcion del adc(4))
  PIR1bits.ADIF=0;//bandera de la interrupcion(4))

  ADCON2bits.ACQT=0b111;//tiempo adquisicion (5)
  ADCON0bits.GO=1;//Prende el ciclo?
}

void wait_in_ms(int time_in_ms){
    unsigned int count = 0;
    unsigned int count_ms = 0;
    unsigned int flag = 0;
    
    TMR0L = 131; 
    
     //Para 1ms : count_ms=3
    count_ms = ((12000000)*0.001)/((256-TMR0L)*32);   //Prescaler = 32
    
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

