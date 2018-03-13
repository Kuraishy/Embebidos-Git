/*
 * File:   newmain.c
 * Author: raqpayro
 *
 * 
 */

#define _XTAL_FREQ 4000000     //4MHz

// PIC18F4550 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#pragma config PLLDIV = 1      // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
// CONFIG1H
#pragma config FOSC = HSPLL_HS     // Oscillator Selection bits (EC oscillator, CLKO function on RA6 (EC))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config USBDIV = 2  
// CONFIG2L
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
// CONFIG2H
#pragma config WDT = OFF         // Watchdog Timer Enable bit (WDT enabled)
// CONFIG3H
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)
// CONFIG4L
#pragma config LVP = OFF         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled
// CONFIG5L
// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)
// CONFIG6L

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "config.h"
#include "lcd.h"


unsigned int int0flag = 0;
unsigned int int1flag = 0;
unsigned int int2flag = 0;
unsigned int pir1flag = 0;

unsigned int count = 0;





void interrupt ADCint(void){
    
 if(INTCONbits.INT0IF == 1)
    {
        INTCONbits.INT0IF = 0; 
        int0flag = 1;
    }
    
    if(INTCON3bits.INT1IF == 1)
    {
        INTCON3bits.INT1IF = 0;
        int1flag = 1;
    }
    
    if(INTCON3bits.INT2IF == 1)
    {
        INTCON3bits.INT2IF = 0;
        int2flag = 1;
    }
 
    if(PIR1bits.ADIF == 1) //Interrupcion por finalizacion de conversion ADC
    {
        PIR1bits.ADIF = 0;  //A/D Converter Interrupt Flag
        pir1flag = 1;
    }


}
void main(void) {
    
    unsigned int an0;
    unsigned int an1;
    
    configBoard();
    
    lcd_iniciar();      //Se inicializa el LCD


    while(1){
        
    ADCON0bits.ADON = 1;
    wait_in_ms(2);     //Espera tiempo de adquisicion    
    
       TRISAbits.RA0=1;
   PORTAbits.RA0=0;
    ADCON0bits.GO_nDONE = 1;   //Inicia la conversi€n de la se“al anal€gica almacenada en el condensador
    while(ADCON0bits.GO_nDONE); //Espera que la conversi€n termine cuando ADCON0bits.GO=0
    
float  voltaje_an0 = 0; 
float  voltaje_an1 = 0; 

    an0 = ADC_Read(0);  // Se lee y almacena el valor ADC
    wait_in_ms(2);
    an1 = ADC_Read(1);  // Se lee y almacena el valor ADC
    
    voltaje_an0 = (an0 * 4.47)/1023; // Se convierte el valor ADC a voltaje
    voltaje_an1 = (an1 * 4.47)/1023; // Se convierte el valor ADC a voltaje

    
    lcd_limpiar();
    
    char str[2];
  //  char test2=
    sprintf(str,"v1= %0.2f ",voltaje_an0);
    lcd_texto(str);
  //  lcd_origen();
    
     lcd_ubicarXY(2,1);
      lcd_texto(str);
     
        wait_in_ms(200);
    } 

}

