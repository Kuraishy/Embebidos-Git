/*
 * File:   ECG.c
 * Author: Administrador
 *
 * Created on 25 de febrero de 2018, 04:28 PM
 */

#define MotorDerecho LATCbits.LC2
#define MotorIzquierdo LATBbits.LB4
#define SensorDerecho PORTDbits.RD2
#define SensorCentral PORTDbits.RD3
#define SensorIzquierdo PORTCbits.RC7 

#include <pic18f4550.h>



#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "config.h"
#include "definicionPines.h"
#include <time.h>
#include <string.h>
#include "lcd.h"
#define _XTAL_FREQ 16000000



void main()
{
    configBoard();
        lcd_iniciar(); 
    ADCON1bits.PCFG = 0b1111;//opcion de todos los pines en digitales


    
    TRISCbits.RC2=0;//motorderecho
    TRISBbits.RB4=0;//motor izuqierod
    TRISDbits.RD3=1;//sensor central
    TRISDbits.RD2=1;//Sensor Derecho
    TRISCbits.RC7=1;//Sensor Izuqierod
    
    
    //////////////////////////

  
     
    while(1)       {    
    
   
        lcd_origen();
        lcd_texto("hola");
  

        
                }
    }  

