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

    unsigned int print = 0;
    unsigned int valor=0;
        unsigned int up = 0;
    unsigned int down = 1;
    unsigned int ADCval = 0;
    float ADCDecimal = 0;
    float Voltage = 0;
    char str[24];

    

    unsigned int ADC_Read (unsigned int channel){
    
    /*
    if(channel > 12){              //Los canales son del 0 al 12
    return 0;
    }
    */
     
    if (channel == 0){
       ADCON0bits.CHS = 0b0000;
    }
    if (channel == 1){
       ADCON0bits.CHS = 0b0001;
    }
    if (channel == 2){
       ADCON0bits.CHS = 0010;
    }
    if (channel == 3){
       ADCON0bits.CHS = 0011;
    }
    if (channel == 4){
       ADCON0bits.CHS = 0100;
    }
    if (channel == 5){
       ADCON0bits.CHS = 0101;
    }
    if (channel == 6){
       ADCON0bits.CHS = 0110;
    }
    if (channel == 7){
       ADCON0bits.CHS = 0111;
    }
    if (channel == 8){
       ADCON0bits.CHS = 1000;
    }
    if (channel == 9){
       ADCON0bits.CHS = 1001;
    }
    if (channel == 10){
       ADCON0bits.CHS = 1010;
    }
    if (channel == 11){
       ADCON0bits.CHS = 1011;
    }
    if (channel == 12){
       ADCON0bits.CHS = 1100;
    }
    /*
    ADCON0 &= 0xC5;               //Despeja canal
    ADCON0 |= channel<<3;         //Asignando canal
    wait_in_ms(2);
    */
    
    wait_in_ms(2);
    ADCON0bits.GO_nDONE = 1;   //Inicia la conversiÛn de la seÒal analÛgica almacenada en el condensador
    while(ADCON0bits.GO_nDONE); //Espera que la conversiÛn termine cuando ADCON0bits.GO=0
    return ((ADRESH<<8)+ADRESL); //Se concatenan los bits m·s y menos significativos
}
void main()
{
  TRISCbits.RC1=1;
       TRISCbits.RC2=1;
       
      unsigned char   dc ;
    OSCCON=0x72;  // use internal oscillator frequency USA EL CRISTAL, NO SE CAMBIA SIN IMPORTAR QUE CRITSAL SE USA
    
     configBoard();
    lcd_iniciar();      //Se inicializa el LCD
   
   CCP2CONbits.CCP2M0 = 1; //CAPTURE MODE EVERY RISING EDGE
    CCP2CONbits.CCP2M1 = 1;
    CCP2CONbits.CCP2M2 = 0;
    CCP2CONbits.CCP2M3 = 1;
    
    T3CONbits.T3CCP1 = 0; //CCP1 WORKS WITH TIMER1
    T3CONbits.T3CCP2 = 0;
    
    PIE2bits.CCP2IE = 0;
    PIR2bits.CCP2IF = 0;
    TRISAbits.RA0=1;

            ADCON0bits.ADON = 1;    //TUNRN ON ADC
        T1CONbits.TMR1ON = 1; //Empieza a contar el TIMER1;

    while(1)       {    
 
        


        

        
        CCPR2 = 3000;
        
        if (TMR1IF == 1) {
            TMR1IF = 0;
            TMR1H = valor >> 8;
            TMR1L = valor;
         }
        
      
        
        if(CCP2IF == 1) {
            CCP2IF = 0;
            print = 1;
        }

            lcd_origen();
            wait_in_ms(10);
          //  move_cursor(7);
//            CCP2CONbits.CCP2M = 0;
//            CCP2IF = _OFF;
            
            
            sprintf(str, "%2.2fV ", Voltage);
            lcd_texto(str);
            print = 0;
            wait_in_ms(500);
        }
        

  
     
        
    }  
    


