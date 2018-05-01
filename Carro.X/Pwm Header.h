/* 
 * File:   Pwm Header.h
 * Author: Administrador
 *
 * Created on 1 de mayo de 2018, 03:27 PM
 */

#ifndef PWM_HEADER_H
#define	PWM_HEADER_H
#define _XTAL_FREQ 48000000 //Se define la frecuencia con la que trebaja nuestro oscilador para que tenga un areferencia con el comando __delay_ms
#include <xc.h> //libreria clasica
#include "config.h"
#include <math.h>

void config_timer2(int onoff, int presc); //Prototipos del programa
void coinfig_ccpcon(float fosc, float freq);
void config_ccp1(int duty1);
void config_ccp2(int duty2);


/*********************************Variables Globales*********************************/
float prescg; //Prescaler GLOBAL
float pr2g; //PR2 GLOBAL








#endif	/* PWM_HEADER_H */

