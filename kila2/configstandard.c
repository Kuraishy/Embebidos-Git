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
    
    // Datasheet: pagina 99, PDF: 101
    INTCONbits.GIE = 0; //Se activan las interrupciones globales
    INTCONbits.PEIE = 0; // se activan las interrupciones por perifericos
    INTCONbits.INT0IE=0;
    INTCONbits.INT0IF=0;
    INTCON2bits.INTEDG0=0;
    INTCON2bits.INTEDG1=0;
    INTCON3bits.INT1E=0;
    INTCON3bits.INT1F=0;
    
    PIE1bits.CCP1IE = 0; //Habilitamos la interrupcion por CCP1
    PIR1bits.CCP1IF = 0; //Limpiamos la bandera de int por CCP1
    
   /*********************************Registro TIMER1*********************************/
    
    // Timer1 1 tick = 0.25us
    //Se configuro el Fosc = 16Mhz
    
    T1CONbits.TMR1CS = 0; //Fosc/4
    T1CONbits.RD16 = 1; //Timer en 16 bits
    T1CONbits.T1CKPS = 0b00; //Prescaler 1:1
    T1CONbits.TMR1ON = 0;//Se mantiene apagado el Timer1
    TMR1 = 0; // Se mantiene apagado el timer1 para que no comience a contar
    
    /*********************************Registro CCP1CON*********************************/
    
    CCP1CONbits.CCP1M = 0b1011; // 
    CCPR1 = 2400; // 2400 ticks = 0.6ms
    
    
    /**********adc  exp*******/
    ADCON2bits.ADCS=110;
    ADCON2bits.ACQT=010;
    /**********************/
    
    
    /************Registro T0CON - TIMER0 - Temporizador ************/
    //Si se usa el TIMER0 con interrupciones hay que configurarlo en el registro INTCON
     // Datasheet: pagina 125, PDF: 127
    T0CONbits.TMR0ON = 0; //Descativa el inicio del TIMER0 (1 = ON, 0 = OFF)
    T0CONbits.T08BIT = 1; //Se configuran de cuantos bits se uilizaran (1 = 8 bits, 0 = 16 bits)
    T0CONbits.T0CS = 0; // Uso del pin TOKL(RA4) (1 = si, 0 = no) 
    T0CONbits.T0SE = 1; // se configura en subida. Lectura de flanco de subida o de bajada (solo para modo contador es indiferente en modo temporizador )
    T0CONbits.PSA = 0; //Uso del prescalador(0 = ON, 1 = OFF)
    //Configuracion del preescalador con los bits 0,1 y 2 - valores en el datasheet
    /// Modo del prescales en 1:256
    T0CONbits.T0PS2 = 1;
    T0CONbits.T0PS1 = 1;
    T0CONbits.T0PS0 = 1;

    
}