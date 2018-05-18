/*
 * File:   ECG.c
 * Author: Administrador
 *
 * Created on 25 de febrero de 2018, 04:28 PM
 */

//Motor derecho
//segun como se ponga va a delante o atras. adelante (avanzar =1 atras=0);
/*
#define MotorIzquierdoAvanzar LATAbits.LA0     //(IN4)
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



 
   
void main()
{
    configBoard();
    ADCON1bits.PCFG = 0b1111;//opcion de todos los pines en digitales
    //salidas para los pines del motor
    TRISAbits.RA0=0;
    TRISAbits.RA1=0;
    TRISEbits.RE0=0;
    TRISEbits.RE1=0;
   ////////////////////////PInes para sensores////////////////////
    TRISBbits.RB5=1;
    TRISBbits.RB4=1;
    TRISBbits.RB3=1;
    TRISBbits.RB2=1;
    TRISBbits.RB1=1;
    
   
 ////////////////////Configuracion de pines/////////////////////
    TRISCbits.RC2 = 0; //Pin del CCP1 es declarada como salida 
    TRISCbits.RC1 = 0;
     ////////////////Funciones para configurar señal PWM //////////////////
    config_timer2(0,16); //(Encendido/Apagado , Prescaler )
    coinfig_ccpcon(48000000,15000);//(Fosc(Hz), Frecuencia (HZ))
  //  config_ccp1(25);//(DutyCycle(%))//llanta derecha
    //config_ccp2(35);//(DutyCycle(%))//llanta izquierda
    
   StatusPWM = 1;
   
  



     
    while(1)       {    
    
   //    carroAvanzar();
        wait_in_ms(1000);    
        carroAvanzar();
        wait_in_ms(1000);    
        carroAtras();
        wait_in_ms(1000);    
        carroMatar();
        carroGirar(1);
        wait_in_ms(1000);    
        carroMatar();
        carroGirar(2);
    
        if(SensorDerecha==0&&SensorCentral==0&&SensorIzquierda==0&&SensorExtremoDerecha==0&&SensorExtremoIzquierda==0){
            carroAvanzarEspecial();
        }
        else if(SensorDerecha==0&&SensorCentral==0&&SensorIzquierda==1){
            carroGirar(3);
        }
        else if(SensorDerecha==0&&SensorCentral==1&&SensorIzquierda==0){
            carroAvanzar();
        }
        else if(SensorDerecha==0&&SensorCentral==1&&SensorIzquierda==1){
            carroAvanzar();
        }
        else if(SensorDerecha==1&&SensorCentral==0&&SensorIzquierda==0){
            carroGirar(1);
        }
        else if(SensorDerecha==1&&SensorCentral==1&&SensorIzquierda==0){
            carroAvanzar();
        }
        else if(SensorDerecha==1&&SensorCentral==1&&SensorIzquierda==1){
            carroMatar();
        }

        else if(SensorExtremoDerecha==1&&SensorDerecha==0&&SensorCentral==0&&SensorIzquierda==0&&SensorExtremoIzquierda==0){
              MotorDerechoAvanzar=0;
              MotorDerechoAtras=0;
             MotorIzquierdoAvanzar=1;
             MotorIzquierdoAtras=0;
        }
        else if(SensorExtremoDerecha==0&&SensorDerecha==0&&SensorCentral==0&&SensorIzquierda==0&&SensorExtremoIzquierda==1){
              MotorDerechoAvanzar=1;
              MotorDerechoAtras=0;
             MotorIzquierdoAvanzar=0;
             MotorIzquierdoAtras=0;
        }
   

        
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
*/

/*
 * File:   ECG.c
 * Author: Administrador
 *
 * Created on 25 de febrero de 2018, 04:28 PM
 */

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
void carroGirarEspecial(unsigned char direccion2);
void carroEsquivar();

void main()
{
    configBoard();
    ADCON1bits.PCFG = 0b1111;//opcion de todos los pines en digitales
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
    
    TRISAbits.RA0=1;//sensor distancia
  /*********Configuracion de pines***********/
    TRISCbits.RC2 = 0; //Pin del CCP1 es declarada como salida 
    TRISCbits.RC1 = 0;
       /*********Funciones para configurar señal PWM ***********/
    config_timer2(0,16); //(Encendido/Apagado , Prescaler )
    coinfig_ccpcon(48000000,15000);//(Fosc(Hz), Frecuencia (HZ))
  //  config_ccp1(25);//(DutyCycle(%))//llanta derecha
    //config_ccp2(35);//(DutyCycle(%))//llanta izquierda
    
   StatusPWM = 1;
   
     
    while(1)       {    

        
  //      while(PORTAbits.RA0==1){
    
        if(SensorExtremoIzquierda==0&&SensorIzquierda==0&&SensorCentral==0&&SensorDerecha==0&&SensorExtremoDerecha==0){
            carroAvanzarEspecial();
        }
        else if (SensorExtremoIzquierda==0&&SensorIzquierda==0&&SensorCentral==0&&SensorDerecha==0&&SensorExtremoDerecha==1){
            carroGirar(1);
        }
        else if(SensorExtremoIzquierda==0&&SensorIzquierda==0&&SensorCentral==0&&SensorDerecha==1&&SensorExtremoDerecha==0){
            carroGirar(1);
        }
        else if(SensorExtremoIzquierda==0&&SensorIzquierda==0&&SensorCentral==0&&SensorDerecha==1&&SensorExtremoDerecha==1){
            carroGirar(1);
        }
        else if(SensorExtremoIzquierda==0&&SensorIzquierda==0&&SensorCentral==1&&SensorDerecha==0&&SensorExtremoDerecha==0){
            carroAvanzar();
        }
        else if(SensorExtremoIzquierda==0&&SensorIzquierda==0&&SensorCentral==1&&SensorDerecha==1&&SensorExtremoDerecha==0){
            carroGirar(1);
        }
        else if(SensorExtremoIzquierda==0&&SensorIzquierda==1&&SensorCentral==0&&SensorDerecha==0&&SensorExtremoDerecha==0){
            carroGirar(3);
        }
        else if(SensorExtremoIzquierda==0&&SensorIzquierda==1&&SensorCentral==1&&SensorDerecha==0&&SensorExtremoDerecha==0){
            carroGirar(3);
        }
        else if(SensorExtremoIzquierda==0&&SensorIzquierda==1&&SensorCentral==1&&SensorDerecha==1&&SensorExtremoDerecha==0){
            carroAvanzarEspecial();
        }
        else if(SensorExtremoIzquierda==1&&SensorIzquierda==0&&SensorCentral==0&&SensorDerecha==0&&SensorExtremoDerecha==0){
            carroGirar(3);
        }
        else if(SensorExtremoIzquierda==1&&SensorIzquierda==1&&SensorCentral==0&&SensorDerecha==0&&SensorExtremoDerecha==0){
            carroGirar(3);
        }
        else if (SensorExtremoIzquierda==1&&SensorIzquierda==1&&SensorCentral==1&&SensorDerecha==1&&SensorExtremoDerecha==1){
            carroAvanzarEspecial();
        }
        else if(SensorExtremoIzquierda==0&&SensorIzquierda==0&&SensorCentral==1&&SensorDerecha==1&&SensorExtremoDerecha==1){
            carroGirarEspecial(1);
        }
        else if(SensorExtremoIzquierda==1&&SensorIzquierda==1&&SensorCentral==1&&SensorDerecha==0&&SensorExtremoDerecha==0){
            carroGirarEspecial(2);
        }
      //  }
       
     
       //     carroEsquivar();
        

        
                }
    }  

void carroAvanzar(){//avanza el carro
    MotorDerechoAvanzar=1;
    MotorDerechoAtras=0;
    MotorIzquierdoAvanzar=1;
    MotorIzquierdoAtras=0;
    config_ccp1(85);//(DutyCycle(%))
    config_ccp2(85);//(DutyCycle(%))
    
}
void carroAvanzarEspecial(){

     MotorDerechoAvanzar=1;
    MotorDerechoAtras=0;
    MotorIzquierdoAvanzar=1;
    MotorIzquierdoAtras=0;
    config_ccp1(70);//(DutyCycle(%))
    config_ccp2(70);//(DutyCycle(%))

}

void carroAtras(){//retrocede el carro
    MotorDerechoAvanzar=0;
    MotorDerechoAtras=1;
    MotorIzquierdoAvanzar=0;
    MotorIzquierdoAtras=1;
    config_ccp1(100);//(DutyCycle(%))
    config_ccp2(100);//(DutyCycle(%))
}
    
void carroGirarEspecial(unsigned char direccion2){
    if(direccion2==1){
        MotorIzquierdoAvanzar=1;
        MotorIzquierdoAtras=0;
        MotorDerechoAvanzar=0;
        MotorDerechoAtras=0;
        
    }
    else if(direccion2==2){
         MotorIzquierdoAvanzar=0;
        MotorIzquierdoAtras=0;
        MotorDerechoAvanzar=1;
        MotorDerechoAtras=0;
    }
     config_ccp1(40);//(DutyCycle(%))
    config_ccp2(40);//(DutyCycle(%))
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
     config_ccp1(85);//(DutyCycle(%))
    config_ccp2(85);//(DutyCycle(%))
}

void carroMatar(){
        MotorIzquierdoAvanzar=0;
        MotorIzquierdoAtras=0;
        MotorDerechoAvanzar =0;
        MotorDerechoAtras=0;
        config_ccp1(0);//(DutyCycle(%))
       config_ccp2(0);//(DutyCycle(%))
}

void carroEsquivar(){
    
    
    
    carroMatar();
    wait_in_ms(100);
    carroAtras();
    wait_in_ms(700);
    carroGirar(1);
    wait_in_ms(400);
    carroAvanzarEspecial();
     wait_in_ms(1000);
     carroGirar(3);
     wait_in_ms(400);
      carroAvanzarEspecial();
     wait_in_ms(1500);
     carroMatar();
    wait_in_ms(100);
    carroAvanzarEspecial();
    
}