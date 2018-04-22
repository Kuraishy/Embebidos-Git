/*
 * File:   ECG.c
 * Author: Administrador
 *
 * Created on 25 de febrero de 2018, 04:28 PM
 */

//Motor derecho
//segun como se ponga va a delante o atras. adelante (avanzar =1 atras=0);
#define MotorIzquierdoAvanzar PORTAbits.RA0    //(IN4)
 #define MotorIzquierdoAtras PORTAbits.RA1//(IN3)

//Motor izquierdo
//Avanzar= (IN3=0,IN4=1)
#define MotorDerechoAvanzar PORTEbits.RE1 //(IN1)
#define MotorDerechoAtras PORTEbits.RE0//(IN2)

#include <pic18f4550.h>

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "config.h"
#include "definicionPines.h"
#include <time.h>
#include <string.h>
#define _XTAL_FREQ 80000000

void carroAvanzar();
void carroAtras();
void carroGirar(unsigned char direccion);//1 es a derecha  0 es izquierda
void carroMatar();

void main()
{
    
    ADCON1bits.PCFG = 0b1111;//opcion de todos los pines en digitales
    //OSCCON=0x72;  // use internal oscillator frequency USA EL CRISTAL, NO SE CAMBIA SIN IMPORTAR QUE CRITSAL SE USA
    //compuertas de los motores como salida
    TRISAbits.RA0=0;
    TRISAbits.RA1=0;
    TRISEbits.RE0=0;
    TRISEbits.RE1=0;
    //////////////////////////
     configBoard();
   
  



     
    while(1)       {    
    
       carroAvanzar();

        wait_in_ms(1000);
            
              carroAtras();
        wait_in_ms(1000);
        
              carroGirar(1);
              
        wait_in_ms(1000);
       
              carroGirar(2);

        wait_in_ms(1000);
        carroMatar();
         wait_in_ms(1000);


        
                }
    }  

void carroAvanzar(){
    MotorDerechoAvanzar=1;
    MotorDerechoAtras=0;
    MotorIzquierdoAvanzar=1;
    MotorIzquierdoAtras=0;
    
}

void carroAtras(){
    MotorDerechoAvanzar=0;
    MotorDerechoAtras=1;
    MotorIzquierdoAtras=1;
    MotorIzquierdoAvanzar=0;
    
}
    

void carroGirar(unsigned char direccion)//1 es a derecha  0 es izquierda
{
    if(direccion==1){
        MotorIzquierdoAvanzar=1;
        MotorIzquierdoAtras=0;
        MotorDerechoAvanzar =0;
        MotorDerechoAtras=0;
    }
    else if(direccion==2){
         MotorIzquierdoAvanzar=1;
        MotorIzquierdoAtras=0;
        MotorDerechoAvanzar =0;
        MotorDerechoAtras=1;
    }
}

void carroMatar(){
        MotorIzquierdoAvanzar=0;
        MotorIzquierdoAtras=0;
        MotorDerechoAvanzar =0;
        MotorDerechoAtras=0;
}