
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

void carroAvanzar();//funcion de avanzar
void carroAtras();//funcion de retroceder 
void carroGirar(unsigned char direccion);//1 es a derecha  0 es izquierda
void carroMatar();//para el carro
void carroAvanzarEspecial();///para el caso donde no detecten nada, reduce la velocidad
void carroGirarEspecial(unsigned char direccion2, unsigned char PWM1, unsigned char PWM2);
void configADC();
unsigned int ADC_Read (unsigned int channel);
void EstacionaminetoM1();
unsigned char test=0;

void interrupt ADCint(void){
    

   
    if(INT0IF==1){
        INT0F=0;
        test=1;
        EstacionaminetoM1();
    }
}





void main()
{
    
    configBoard();
    
    //salidas para los pines del motor
    TRISAbits.RA4=0;
    TRISAbits.RA1=0;
    TRISEbits.RE0=0;
    TRISEbits.RE1=0;
    

       
   /*********PInes para sensores****************/
    TRISBbits.RB5=1;
    TRISBbits.RB4=1;
    TRISBbits.RB3=1;
    TRISBbits.RB2=1;
    TRISBbits.RB1=1;
    
    TRISAbits.RA0=1;//sensor
  /*********Configuracion de pines***********/
    TRISCbits.RC2 = 0; //Pin del CCP1 es declarada como salida 
    TRISCbits.RC1 = 0;
       /*********Funciones para configurar señal PWM ***********/
    config_timer2(0,16); //(Encendido/Apagado , Prescaler )
    coinfig_ccpcon(48000000,15000);//(Fosc(Hz), Frecuencia (HZ))
  //  config_ccp1(25);//(DutyCycle(%))//llanta derecha
    //config_ccp2(35);//(DutyCycle(%))//llanta izquierda
    
   StatusPWM = 1;
      ADCON1bits.PCFG = 0b1111;//opcion de todos los pines en digitales

     
    while(1)       {    
        wait_in_ms(3000);
 
        carroAvanzarEspecial();
        wait_in_ms(300);
        while(PORTAbits.RA0==0){
        carroAvanzarEspecial();
        wait_in_ms(1000);
        }
     
            EstacionaminetoM1();
            while(test==1);

  
        
                }
    }  


void carroAvanzar(){//avanza el carro
    MotorDerechoAvanzar=1;
    MotorDerechoAtras=0;
    MotorIzquierdoAvanzar=1;
    MotorIzquierdoAtras=0;
    config_ccp1(100);//(DutyCycle(%))
    config_ccp2(100);//(DutyCycle(%))
    
}
void carroAvanzarEspecial(){

     MotorDerechoAvanzar=1;
    MotorDerechoAtras=0;
    MotorIzquierdoAvanzar=1;
    MotorIzquierdoAtras=0;
    config_ccp1(80);//(DutyCycle(%))
    config_ccp2(80);//(DutyCycle(%))

}

void carroAtras(){//retrocede el carro
    MotorDerechoAvanzar=0;
    MotorDerechoAtras=1;
    MotorIzquierdoAvanzar=0;
    MotorIzquierdoAtras=1;
    config_ccp1(100);//(DutyCycle(%))
    config_ccp2(100);//(DutyCycle(%))
}
    
void carroGirarEspecial(unsigned char direccion2, unsigned char PWM1, unsigned char PWM2){
    if(direccion2==1){
        MotorIzquierdoAvanzar=1;
        MotorIzquierdoAtras=0;
        MotorDerechoAvanzar=1;
        MotorDerechoAtras=0;
        
    }
  
     config_ccp1(PWM1);//(DutyCycle(%))
    config_ccp2(PWM2);//(DutyCycle(%))
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
    else if(direccion==3){
         MotorIzquierdoAvanzar=0;
        MotorIzquierdoAtras=0;
        MotorDerechoAvanzar =1;
        MotorDerechoAtras=0;
    }
    else if(direccion==4){
        MotorIzquierdoAvanzar=0;
        MotorIzquierdoAtras=1;
        MotorDerechoAvanzar =1;
        MotorDerechoAtras=0;
    }
     config_ccp1(100);//(DutyCycle(%))
    config_ccp2(100);//(DutyCycle(%))
}

void carroMatar(){
        MotorIzquierdoAvanzar=0;
        MotorIzquierdoAtras=0;
        MotorDerechoAvanzar =0;
        MotorDerechoAtras=0;
        config_ccp1(0);//(DutyCycle(%))
       config_ccp2(0);//(DutyCycle(%))
}

void configADC(){
    
      
    

    INTCONbits.GIE = 0;     //Enable1/Disable0 global
    INTCONbits.PEIE = 0;    //Peripheral Interrupt Enable1/Disable0
   INTCONbits.INT0IE = 0;  //INT0 External Interrupt Enable1/Disable0
    INTCON2bits.INTEDG0 = 1;    //External Interrupt 0 Edge Select (1 rising, 0 falling)
    INTCONbits.INT0IF=0;


     
}



void EstacionaminetoM1(){//sensor esta atras
    
    
   carroMatar();
   wait_in_ms(500);
   carroAvanzarEspecial();
   wait_in_ms(1500);
     carroGirar(1);
     wait_in_ms(800);
     carroAvanzarEspecial();
      wait_in_ms(300);
     carroGirar(3);
     wait_in_ms(900);
          carroAvanzarEspecial();
      wait_in_ms(300);
     carroMatar();
     wait_in_ms(1000);
     test=1;
   //  carroMatar();
}
/*
void EstacionaminetoM2(){//sensor adelante
    carroAvanzar();
    __wait_in_ms(100);
    carroMatar();
     __wait_in_ms(150);
     carroGirarEspecial(1,80,40);
     __wait_in_ms(150);
     carroMatar();
     __wait_in_ms(100);
     carroGirarEspecial(1,40,80);
     __wait_in_ms(100);
     carroAvanzar();
     __wait_in_ms(300);
     carroMatar();
}*/