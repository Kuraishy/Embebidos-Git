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
#include "I2C_config.h"

#define _XTAL_FREQ 48000000 //Se define la frecuencia con la que trebaja nuestro oscilador para que tenga un areferencia con el comando __delay_ms




 
   
void main()
{
    
    configBoard();
      
    int x = 100;
    char m[8];
    
    //sprintf(m, "value: %x", x);
    
    
    
    char data[8];
    initI2C();
    


	
	while(1)
	{

        
            I2Cstart();
              __delay_ms(500);


	}
}

