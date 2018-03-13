/* 
 * File:   definicionPines.h
 * Author: Administrador
 *
 * Created on 16 de febrero de 2018, 06:36 PM
 */

#ifndef DEFINICIONPINES_H
#define	DEFINICIONPINES_H

#include <xc.h>

// CONFIG1L
#pragma config PLLDIV = 2       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])

// CONFIG1H
#pragma config FOSC = HSPLL_HS      // Oscillator Selection bits (EC oscillator, CLKO function on RA6 (EC)) tipo de cristal, alta velocidad 
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)

// CONFIG2L
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)

// CONFIG2H
#pragma config WDT = OFF         // Watchdog Timer Enable bit (WDT enabled) hay que apagarlo

// CONFIG3H
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config LVP = OFF         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)






#endif	/* DEFINICIONPINES_H */

