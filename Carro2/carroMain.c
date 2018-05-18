
//Motor derecho
//segun como se ponga va a delante o atras. adelante (avanzar =1 atras=0);
#define MotorIzquierdoAvanzar LATAbits.LA4     //(IN4)
 #define MotorIzquierdoAtras LATAbits.LA1 //(IN3)

//Motor izquierdo
//Avanzar= (IN3=0,IN4=1)
#define MotorDerechoAvanzar LATEbits.LE1 //(IN1)
#define MotorDerechoAtras LATEbits.LE0 //(IN2)

#define StatusPWM T2CONbits.TMR2ON

#define SensorIzquierda PORTBbits.RB5
#define SensorCentral PORTBbits.RB4
#define SensorDerecha PORTBbits.RB3
#define SensorExtremoIzquierda  PORTBbits.RB2
#define SensorExtremoDerecha PORTBbits.RB1


#include <pic18f4550.h>

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "config.h"
#include "definicionPines.h"
#include <time.h>
#include <string.h>
#include "Pwm Header.h"
#define _XTAL_FREQ 48000000 //Se define la frecuencia con la que trebaja nuestro oscilador para que tenga un areferencia con el comando __delay_ms


void configADC();
unsigned int ADC_Read (unsigned int channel);


void interrupt ADCint(void){
    

    if(PIR1bits.ADIF == 1) //Interrupcion por finalizacion de conversion ADC
    {
        PIR1bits.ADIF = 0;  //A/D Converter Interrupt Flag
       
    }


}

void main()
{
    
    configBoard();
    configADC();
    //salidas para los pines del motor
    TRISAbits.RA4=0;
    TRISAbits.RA1=0;
    TRISEbits.RE0=0;
    TRISEbits.RE1=0;
    
    TRISDbits.RD2=0;
   /*********PInes para sensores****************/
    TRISBbits.RB5=1;
    TRISBbits.RB4=1;
    TRISBbits.RB3=1;
    TRISBbits.RB2=1;
    TRISBbits.RB1=1;
    
 
     
    while(1)       {    

       ADCON0bits.ADON = 1;
    wait_in_ms(2);     //Espera tiempo de adquisicion    
    ADCON0bits.GO_nDONE = 1;   //Inicia la conversi€n de la se“al anal€gica almacenada en el condensador
    while(ADCON0bits.GO_nDONE); //Espera que la conversi€n termine cuando ADCON0bits.GO=0
    
     if(ADC_Read(0)>350){
            LATDbits.LD2=1;
        }else{
            LATDbits.LD2=0;
        }
    
    }}
    
 

void configADC(){
    
      
    
    TRISAbits.RA0=1;//Puerta A0 (2)
    INTCONbits.GIE = 0;     //Enable1/Disable0 global
    INTCONbits.PEIE = 0;    //Peripheral Interrupt Enable1/Disable0
    //INTCONbits.INT0IE = 0;  //INT0 External Interrupt Enable1/Disable0
    //INTCONbits.TMR0IE = 1;  //Overflow Interrupt Enable1/Disable0
     ADCON0bits.CHS = 0000;  //Analog Channel Select AN0
    ADCON1bits.VCFG = 0b00;     //Voltage Reference Configuration (VREF- VREF+ source) (VDD VSS source)  
    ADCON1bits.PCFG=0b1110;//A0 es analogico (1))
    ADCON2bits.ADFM = 1;     //A/D Result Format Select Justified (1 right, 0 left)
    ADCON2bits.ADCS = 0b110;   //A/D Conversion Clock Select TADmin 0.7 us(48MHz/64= 1.33us = TAD)
    ADCON2bits.ACQT = 0b010;   // A/D Acquisition Time Select (12TAD)
    PIE1bits.ADIE = 1;  //A/D Converter Interrupt Enable1/Disable0    
    PIR1bits.ADIF = 0;  //A/D Converter Interrupt Flag
  
    ADCON0bits.ADON = 0;    //ADC is shut-off; consumes no operating power
  ADCON0bits.GO=0;//Prende el ciclo?

     
}


unsigned int ADC_Read (unsigned int channel){
    
    if (channel == 0){
       ADCON0bits.CHS = 0b0000;
    
    ADCON0bits.GO_nDONE = 1;   //Inicia la conversi€n de la se“al anal€gica almacenada en el condensador
    while(ADCON0bits.GO_nDONE); //Espera que la conversi€n termine cuando ADCON0bits.GO=0
    return ((ADRESH<<8)+ADRESL); //Se concatenan los bits m∑s y menos significativos
    }
}
