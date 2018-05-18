/*
 * File:   configstandard.c
 * Author: Fernando
 *
 * Created on 28 de marzo de 2018, 11:27 PM
 */

#include "config.h"
/*********************************Funcion que configura pines como DIGITALES o ANALOGICAS y Configuramos las interrupciones generales*********************************/
void configstandard() 
{
    /*********************************Registro ADCON0*********************************/
    
    // Datasheet: pagina 259, PDF: 261
    
    ADCON0bits.CHS3 = 0; //Seleccion del canal 0000 = AN0
    ADCON0bits.CHS2 = 0;
    ADCON0bits.CHS1 = 0;
    ADCON0bits.CHS0 = 0;
    ADCON0bits.ADON = 1; // El ADC se activa
    
    /*********************************Registro ADCON1*********************************/
    
    ADCON1 = 0b00001110;
    
    /*********************************Registro ADCON2*********************************/
    
    ADCON2bits.ADFM = 1; //JUstificacion hacia la derecha
    ADCON2bits.ACQT2 = 1;//Configuracion Tad
    ADCON2bits.ACQT1 = 0;
    ADCON2bits.ACQT0 = 1;
    ADCON2bits.ADCS2 = 1; //Frecuencia de convercion FOSC/2
    ADCON2bits.ADCS1 = 0;
    ADCON2bits.ADCS0 = 0;
    
    ADRESH = 0;
    ADRESL = 0;
    
    /*********************************Existen otras formas de asignar valores*********************************/
    //Se toma solo el nombre del registro 
    //ADCON1 |= 0b00001111; - Forma Binaria
    //ADCON1 |= 15; - Forma decimal
    //ADCON1 |= 0x0F; - Hexadecimal
   
    /*********************************Registro INTCON*********************************/
    
    
   /*********************************Registro TIMER1*********************************/
    
   
    
    /*********************************Registro CCP1CON*********************************/
    
    CCP1CONbits.CCP1M = 0b1011; // 
    CCPR1 = 2400; // 2400 ticks = 0.6ms
    
    
    /**********adc  exp*******/
    ADCON2bits.ADCS=110;
    ADCON2bits.ACQT=010;
    /**********************/
    
    
  

    
}