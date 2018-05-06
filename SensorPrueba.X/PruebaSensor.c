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
#define _XTAL_FREQ 80000000



void main()
{
    configBoard();
    ADCON1bits.PCFG = 0b1111;//opcion de todos los pines en digitales


    
    TRISCbits.RC2=0;//motorderecho
    TRISBbits.RB4=0;//motor izuqierod

    
    
    //////////////////////////

  
     
    while(1)       {    
    
 
        PORTBbits.RB4=1;
        wait_in_ms(100);
        PORTBbits.RB4=0;
        wait_in_ms(50);
   

        
                }
    }  

