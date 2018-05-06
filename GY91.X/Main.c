/*
 * File:   ECG.c
 * Author: Administrador
 *
 * Created on 25 de febrero de 2018, 04:28 PM
 */




#include <pic18f4550.h>

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "config.h"
#include "definicionPines.h"
#include <time.h>
#include <string.h>
#include "i2c.h"
#include"lcd.h"
#define _XTAL_FREQ 48000000 //Se define la frecuencia con la que trebaja nuestro oscilador para que tenga un areferencia con el comando __delay_ms




 
   
void main()
{
    
    configBoard();
    lcd_inicializar();
        Acelerometro_Init();		
  char buffer[20];
    char buffer2[20];
      char buffer3[20];
	int Ax,Ay,Az,T,Gx,Gy,Gz;
	float Xa,Ya,Za,t,Xg,Yg,Zg;
    OSCCON = 0x72;
//    I2C_Inicializar();
   										/* Initialize I2C */	
								/* Initialize Gyro */
										/* Initialize USART with 9600 baud rate */
	
	while(1)
	{
    //    lcd_origen();
		Acelerometro_Start();								/* Read Gyro values continuously and send to terminal over USART */
		Ax = (((int)I2C_Read(0)<<8) | (int)I2C_Read(0));
		Ay = (((int)I2C_Read(0)<<8) | (int)I2C_Read(0));
		Az = (((int)I2C_Read(0)<<8) | (int)I2C_Read(0));
		T = (((int)I2C_Read(0)<<8) | (int)I2C_Read(0));
		Gx = (((int)I2C_Read(0)<<8) | (int)I2C_Read(0));
		Gy = (((int)I2C_Read(0)<<8) | (int)I2C_Read(0));
		Gz = (((int)I2C_Read(0)<<8) | (int)I2C_Read(1));
		I2C_Stop();
		Xa = (float)Ax/16384.0;							/* Divide raw value by sensitivity scale factor to get real values */
		Ya = (float)Ay/16384.0;
		Za = (float)Az/16384.0;
		Xg = (float)Gx/131.0;
		Yg = (float)Gy/131.0;
		Zg = (float)Gz/131.0;
		t = ((float)T/340.00)+36.53;					/* Convert temperature in °/c using formula */
		sprintf(buffer," Ax = %.2f g\t",Xa);			/* Take values in buffer to send all parameters over USART */
            
                 //   lcd_texto(buffer);
		
		sprintf(buffer2," Ay = %.2f g\t",Ya);
                 //  lcd_texto(buffer2);
        
		
		sprintf(buffer3," Az = %.2f g \n",Za);
	
               // lcd_texto(buffer3);
	}
}

