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


void Trigger_Pulse_10us();

#define _XTAL_FREQ 8000000	/* Define freq */
#define Trigger_Pulse LATD0	/* Define Trig pin of HC-SR04 */

void main()
{
    float Distance;
    int Time;
    float Total_distance[10];
    OSCCON=0x72;		/* Use internal oscillator frequency */
    TRISB = 0xff;		/* Make PORTB as Input port*/
    TRISD = 0;			/* Make PORTD as Output port*/
    INTCON2bits.RBPU=0;		/* Enable PORTB Pull-ups */

    Trigger_Pulse = 0;
/* Enable 16-bit TMR1 Register,No prescale, internal clock, Timer OFF */    
    T1CON = 0x80;
    TMR1IF = 0;			/* Make Timer1 Overflow Flag to '0' */
    TMR1=0;			/* Load Timer1 with 0 */

while(1)
{    
    
    Trigger_Pulse_10us();	/* Transmit 10us pulse to HC-SR04 */
    while(PORTBbits.RB0==0);	/* Wait for rising edge at Echo pin */
    TMR1=0;			/* Load Timer1 register with 0 */
    TMR1ON=1;			/* Turn ON Timer1*/
    while(PORTBbits.RB0==1 && !TMR1IF);/* Wait for falling edge */
    Time = TMR1;		/* Copy Time when echo is received */
    TMR1ON=0;			/* Turn OFF Timer1 */
    Distance = ((float)Time/117.00);/* Distance =(velocity x Time)/2 */
    if(Distance>5&&Distance<15){
        PORTDbits.RD2=1;
    }else{
        PORTDbits.RD2=0;
    }
  
}   
}
void Trigger_Pulse_10us()
{
    Trigger_Pulse = 1;
    __delay_us(10);
    Trigger_Pulse = 0;
}