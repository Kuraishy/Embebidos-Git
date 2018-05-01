/*
 * File:   ECG.c
 * Author: Administrador
 *
 * Created on 25 de febrero de 2018, 04:28 PM
 */

//Motor derecho
//segun como se ponga va a delante o atras. adelante (avanzar =1 atras=0);
#define MotorIzquierdoAvanzar LATAbits.LA0     //(IN4)
 #define MotorIzquierdoAtras LATAbits.LA1 //(IN3)

//Motor izquierdo
//Avanzar= (IN3=0,IN4=1)
#define MotorDerechoAvanzar LATEbits.LE1 //(IN1)
#define MotorDerechoAtras LATEbits.LE0 //(IN2)

#define StatusPWM T2CONbits.TMR2ON

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

void carroAvanzar();//funcion de avanzar
void carroAtras();//funcion de retroceder 
void carroGirar(unsigned char direccion);//1 es a derecha  0 es izquierda
void carroMatar();//para el carro


 
   
void main()
{
    configBoard();
    ADCON1bits.PCFG = 0b1111;//opcion de todos los pines en digitales
    //salidas para los pines del motor
    TRISAbits.RA0=0;
    TRISAbits.RA1=0;
    TRISEbits.RE0=0;
    TRISEbits.RE1=0;
    //////////////////////////
  /*********Configuracion de pines***********/
    TRISCbits.RC2 = 0; //Pin del CCP1 es declarada como salida 
    TRISCbits.RC1 = 0;
       /*********Funciones para configurar señal PWM ***********/
    config_timer2(0,16); //(Encendido/Apagado , Prescaler )
    coinfig_ccpcon(48000000,5000);//(Fosc(Hz), Frecuencia (HZ))
    config_ccp1(25);//(DutyCycle(%))
    config_ccp2(35);//(DutyCycle(%))
    
   StatusPWM = 1;
   
  



     
    while(1)       {    
    
   //    carroAvanzar();
       /* wait_in_ms(1000);    
        carroAvanzar();
        wait_in_ms(1000);    
        carroAtras();
        wait_in_ms(1000);    
        carroMatar();
        carroGirar(1);
        wait_in_ms(1000);    
        carroMatar();
        carroGirar(2);*/
    
        
        

   

        
                }
    }  

void carroAvanzar(){//avanza el carro
    MotorDerechoAvanzar=1;
    MotorDerechoAtras=0;
    MotorIzquierdoAvanzar=1;
    MotorIzquierdoAtras=0;
    
}

void carroAtras(){//retrocede el carro
    MotorDerechoAvanzar=0;
    MotorDerechoAtras=1;
    MotorIzquierdoAvanzar=0;
    MotorIzquierdoAtras=1;
    
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