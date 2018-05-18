/*
 * File:   main_000_Practice_On Led.c
 * Author: Fernando
 *
 * Asunto: Asunto: Realiza una conversi´on de analogico a digital de manera periodica usando el disparo especial del modulo de comparacion.
 * 
 * Nota: Se configuro el Fosc sea igual a 16MHz
 * 
 * Created on 28 de marzo de 2018, 11:26 PM
 */


#include <xc.h> //libreria clasica
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "Library_LCD_2.h"
#include<math.h>
#define _XTAL_FREQ 48000000 //Se define la frecuencia con la que trebaja nuestro oscilador para que tenga un areferencia con el comando __delay_ms


/*********************************Empezamos con los Configuration bits**********************************/

#pragma config PLLDIV = 2       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /4][96 MHz PLL Src: /6])

// CONFIG1H
#pragma config FOSC = HSPLL_HS    // Oscillator Selection bits (EC oscillator, CLKO function on RA6 (EC))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF         // Watchdog Timer Enable bit (WDT enabled)
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = ON      // PORTB A/D Enable bit (PORTB<4:0> pins are configured as analog input channels on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

float voltaje;
unsigned int  adc1;
#define analogIn PORTAbits.RA0;
#define mVperAmp 185

      unsigned char buffer1[20]; //Variable String(Arreglos de char) que permitira imprimir datos
        unsigned char buffer2[20];
     
 /********************************* Funcion Interrupcion*********************************/
 
void interrupt comparar()
{
    INTCONbits.GIE = 0; //Se desactivan las interrupciones globales para no generar errores
    if(CCP1IF == 1)
    {
        T1CONbits.TMR1ON = 0;
        PIR1bits.CCP1IF = 0;
   
        adc1 = ADRESH;
        adc1 = adc1<<8;
        adc1 = adc1 + ADRESL;
        
        voltaje = adc1 * 4.72 /1024.0;
        
        
    
    }
   
    
}


/*********************************Funcion Principal*********************************/
void main(void)
{
    configstandard();//Funcion con las configuraciones basicas
    
//    TRISCbits.RC2 = 0; //Se configura como  salida para el CCP1
    TRISAbits.RA0 = 1;//Definimos como entrada para el ADC
  //  TRISAbits.RA1 = 0;
   
  //  T1CONbits.TMR1ON = 1;// Se enciende el timer1
    
    unsigned char buffer1[16]; //Variable String(Arreglos de char) que permitira imprimir datos
    
    /******************INICIALIZACION LCD ***************/
    Lcd_Init(); //Inicializamos
    Lcd_Cmd(LCD_CLEAR); //Limpiammos LCD
    Lcd_Cmd(LCD_CURSOR_OFF); //Apagamos el cursor
    __delay_ms(100);
    
     ADCON2bits.ADCS=110;
    ADCON2bits.ACQT=010;
    
    float sumIns=0;
    float Irms=0;
     unsigned int numCiclosMuestro=0;
     float PotenciaReal=0;
    while(1)//Bucle que evita que el programa termine
    {
  
        while(numCiclosMuestro<200){
        ADCON0bits.GO_DONE = 1;
        adc1 = (ADRESH<<8)+ADRESL;
        float Voltage=0;
        float Amps=0;
        Voltage=(float)(adc1*5.0/1024.0);
        Amps=((Voltage-2.5)/0.185);
     //sprintf(buffer1,"Voltage %0.2f", Voltage);
        sprintf(buffer1,"Voltage %3d", numCiclosMuestro);
        sprintf(buffer2,"amps %0.2f", Amps);
        Lcd_Out2(1, 0, buffer1); //(Linea horizontal, posicion vertical, string)
        Lcd_Out2(2, 0, buffer2);       
       
         __delay_us(50);
        // if(Amps>0.110||Amps<-0.110){//ruido de 110 mili amp
                 sumIns+=Amps*Amps;
                 numCiclosMuestro+=1; 
        //      }
        }
        
        Irms=sqrt(sumIns/201)/2;
        sprintf(buffer2,"IRMS %0.2f", Irms);
        Lcd_Out2(2, 0, buffer2);       
        
       
        sprintf(buffer1,"PReal %0.2f", Irms*128);
        Lcd_Out2(1, 0, buffer1);       
       
    }
    return;
}
 