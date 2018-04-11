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
#include "lcd.h"
#include "definicionPines.h"
#include <time.h>
#include <string.h>
#define _XTAL_FREQ 80000000
#define tiempo 2000000 //temp del timer FOSC/4

unsigned char turno=0;
   unsigned long dato1;
   unsigned long dato2;
   unsigned long dt;
void main()
{
    OSCCON=0x72;  // use internal oscillator frequency USA EL CRISTAL, NO SE CAMBIA SIN IMPORTAR QUE CRITSAL SE USA

     configBoard();
    lcd_iniciar();      //Se inicializa el LCD
   
   unsigned long periodo;

    unsigned long frecuencia[30];
    unsigned long UwU[20];
   
    float freq;
    TRISC2=1; //CCP1 como Input

    memset(frecuencia,0,30);//
       memset(UwU,0,20);//

 
    PIE1bits.CCP1IE=1;
    PIR1bits.CCP1IF=0;     
    CCP1CON=0x05;       //modo de caputa Risign edge 0000 0101
    CCPR1=0x00;         //CCPR1 se limpia el registro de captura
    TMR1IF=0;           
    T1CON=0x80;         //  16-bit TMR1 Registro
    TMR1ON=1; //prende el timer1	     
    while(1)       {    
        lcd_origen();
    //    lcd_texto("gola");
        while(!(PIR1bits.CCP1IF)); //espera por la interrupcion
        PIR1bits.CCP1IF=0;
        dato1 = CCPR1;              //copiar el dato d ccpr1        
        
      CCP1CON=0x04;///Falling edge 0000 0100
        while(!(PIR1bits.CCP1IF)); //duty cycle
        PIR1bits.CCP1IF=0;
        dt = CCPR1;              //copiar el dato d ccpr1    
        
            
      CCP1CON=0x05;       //modo de caputa Risign edge
        while(!(PIR1bits.CCP1IF));  
        PIR1bits.CCP1IF=0;
        dato2 = CCPR1;              

        if(dato1 < dato2)
           {

           //calculo de frecuencia
            periodo = dato2 - dato1;
            freq = ((float)tiempo / (float)periodo);
            sprintf(frecuencia,"%.1f Hz ",freq); 
            
            lcd_texto(frecuencia);
            
            float temp=dt-dato1;//periodo activo
            float temp2=(temp/periodo)*100;
            sprintf(UwU, "%.2f  duty",temp2);
      //      lcd_ubicarXY(2,0);
        //    lcd_texto(UwU);
            //lcd_limpiar();
                lcd_ubicarXY(2,1);
                 lcd_texto(UwU);
               //   lcd_origen();
              //  lcd_texto(frecuencia);
            
            
            } 
        TMR1=0;
        memset(frecuencia,0,30);
            memset(UwU,0,20);//
    }  
    
}
/*
void interrupt test(){
    if(CCP1IF){
        CCP1IF=0;
         if(turno==0){
               data1 = CCPR1;            
               turno=1;
         }else if(turno==1){
             data2=CCPR1;
             turno=0;
         }
            
    }
     
}
*/
    
/*
void interrupt test(){
    
    if(RCIF){
            INTCONbits.GIE = 0;    //Enable1/Disable0 global
            char *test=&Input;
          setInput(RCREG);//recibimos un char
          
         TXREG=Input;              
         
                 //    if(!strcmp("on",Input)){//si lo que recibimos es = on
         if(Input=='d'){
                PORTCbits.RC2=1;//se prende el led
            }
        INTCONbits.GIE = 1;    //Enable1/Disable0 global
      
      }
        
    }

void setInput(char *temp){
    Input=temp;
}

*/
