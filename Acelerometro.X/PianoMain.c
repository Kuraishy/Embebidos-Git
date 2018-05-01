


#include <pic18f4550.h>

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "config.h"
//#include "lcd.h"
#include "definicionPines.h"
#include <time.h>
#include <string.h>
#define _XTAL_FREQ 80000000
#define tiempo 2000000 //temp del timer FOSC/4


void main(){

   // OSCCON=0x72;  // use internal oscillator frequency USA EL CRISTAL, NO SE CAMBIA SIN IMPORTAR QUE CRITSAL SE USA
    OSCCON= 0b01110010;
    
     configBoard();
   // lcd_iniciar();      //Se inicializa el LCD
   
       TRISC = 0 ;                     // set PORTC as output
        PORTC = 0 ;                     // clear PORTC
        TRISE=1;
        TRISD=1;
        TRISB=1;
        
        
        
         
    

    while(1)  {    
        

    }
 }      
        
