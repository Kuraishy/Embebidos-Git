

#include "funciones.h";
#include "lcd.h"
#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 80000000
#define LED1 PORTAbits.RA1
#define LED2 PORTAbits.RA2
#define LED3 PORTAbits.RA3
#define LED4 PORTAbits.RA4
#define TiempoLVL1 1000
#define TiempoLVL2 1000
#define TiempoLVL3 1000
#define TiempoLVL4 1000
#define TiempoLVL5 1000
#define TiempoLVL6 1000
#define TiempoLVL7 1000
#define TiempoLVL8 1000


unsigned char nivel=7;
unsigned char numTopos=0;
unsigned char presionoBoton=0;
signed int puntuacion =0;
unsigned char cantidadBotones=0;

void interrupt ADCint(void){
     
    if(PIR1bits.ADIF == 1) //Interrupcion por finalizacion de conversion ADC
    {
        PIR1bits.ADIF = 0;  //A/D Converter Interrupt Flag
    
    }
}


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
