/* 
 * File:   Pwm Header.h
 * Author: Administrador
 *
 * Created on 1 de mayo de 2018, 03:27 PM
 */

#ifndef I2C_H
#define	I2C_H
#define _XTAL_FREQ 48000000 //Se define la frecuencia con la que trebaja nuestro oscilador para que tenga un areferencia con el comando __delay_ms
#include <xc.h> //libreria clasica
#include "config.h"
#include <math.h>

#include <xc.h>                         /* Include processor files - each processor file is guarded. */
#define F_OSC 8000000                   /* Define F_OSC, here it's 8 MHz */
#define I2C_CLOCK 100000                /* I2C clock frequency is 100 kHz*/
#define BITRATE ((F_OSC/(4*I2C_CLOCK))-1) /* find bit rate to assign this value to SSPADD register*/





void I2C_Ready();                       /* Check weather I2C is ready/idle or not */
void I2C_Init();                        /* Initialize I2C configuration*/
char I2C_Start(char);                   /* Send START pulse with slave device write address */
void I2C_Start_Wait(char);              /* Send START pulse with slave device write address until acknowledgement */
char I2C_Repeated_Start(char);          /* Send REPEATED START pulse with slave device read address*/
char I2C_Stop();                        /* Send STOP pulse*/
char I2C_Write(unsigned char);          /* Write data/address to slave device */
void I2C_Ack();                         /* Send acknowledge to slave for continue read */
void I2C_Nack();                        /* Send negative acknowledge to slave for stop current communication */
char I2C_Read(char);                    /* Read data from slave devices with 0=Ack & 1=Nack */
void Acelerometro_Start();
void Acelerometro_Init();





#endif	/* PWM_HEADER_H */

