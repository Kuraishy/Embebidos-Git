/*
 * File:   ECG.c
 * Author: Administrador
 *
 * Created on 25 de febrero de 2018, 04:28 PM
 */
//RC6-RB5 25-38
#define TeclaDo PORTDbits.RD2
#define TeclaDo2 PORTDbits.RD3

#define TeclaRe PORTDbits.RD4
#define TeclaRe2  PORTDbits.RD5

#define TeclaMi PORTDbits.RD6

#define TeclaFa PORTDbits.RD7
#define TeclaFa2 PORTBbits.RB0

#define TeclaSol PORTBbits.RB1
#define TeclaSol2 PORTBbits.RB2

#define TeclaLa PORTBbits.RB3
#define TeclaLa2 PORTBbits.RB4  //no suena reppara

#define TeclaSi PORTBbits.RB5




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

void tocarNota(unsigned char nota);
void AmazingGrace();
void main()
{

    OSCCON=0x72;  // use internal oscillator frequency USA EL CRISTAL, NO SE CAMBIA SIN IMPORTAR QUE CRITSAL SE USA
    
     configBoard();
   // lcd_iniciar();      //Se inicializa el LCD
   
       TRISC = 0 ;                     // set PORTC as output
        PORTC = 0 ;                     // clear PORTC
        TRISE=1;
        TRISD=1;
        TRISB=1;
        
        
        
          unsigned char   dc ;
    

    while(1)       {    
        
        
        
        
       
        while(TeclaDo){
            tocarNota('c');
        }
         
         while(TeclaDo2){
            tocarNota('C');
        }
        
         while(TeclaRe){
            tocarNota('d');
        }
          while(TeclaRe2){
            tocarNota('D');
        }
         while(TeclaMi){
            tocarNota('e');
        }
          while(TeclaFa){
            tocarNota('f');
        }
         while(TeclaFa2){
            tocarNota('F');
        }
        while(TeclaSol){
            tocarNota('g');
        }
        while(TeclaSol2){
            tocarNota('G');
        }        
        while(TeclaLa){
            tocarNota('a');
        }
        while(TeclaLa2){
            tocarNota('A');
        }      
        while(TeclaSi){
            tocarNota('b');
        }    
           CCP1CON = 0;


           while(PORTEbits.RE1==1)
           {
        tocarNota('d');
    wait_in_ms(300);
    tocarNota('g');
    wait_in_ms(600);
    tocarNota('b');
    wait_in_ms(50);
    tocarNota('a');
    wait_in_ms(50);
    tocarNota('g');
    wait_in_ms(50);
    tocarNota('b');
    wait_in_ms(600);
    tocarNota('a');
    wait_in_ms(300);
    tocarNota('g');
    wait_in_ms(600);
    tocarNota('e');
    wait_in_ms(300);
    tocarNota('d');
    wait_in_ms(600);
    tocarNota('d');
    wait_in_ms(300);
    }
            
           
           
    ///////////////
       while(PORTEbits.RE0==1)
           {
           tocarNota('e');
           wait_in_ms(100);
           tocarNota('e');
           wait_in_ms(100);
           tocarNota('f');
           wait_in_ms(100);
           tocarNota('g');
           wait_in_ms(100);
           tocarNota('g');
           wait_in_ms(100);
           tocarNota('f');
           wait_in_ms(100);
           tocarNota('e');
           wait_in_ms(100);
           tocarNota('d');
           wait_in_ms(100);
           tocarNota('c');
           wait_in_ms(100);
           tocarNota('c');
           wait_in_ms(100);
           tocarNota('d');
           wait_in_ms(100);
           tocarNota('e');
           wait_in_ms(100);
           tocarNota('e');
           wait_in_ms(100);
           tocarNota('d');
           wait_in_ms(100);
           tocarNota('d');
           wait_in_ms(100);
           
       }
       }      
           ////////////////////////
                }  

void tocarNota(unsigned char nota){
    
    switch (nota){
        case'c'://nota do 523.251
            PR2 = 0b11101110 ;
            T2CON = 0b00000111 ;
            CCPR1L = 0b01110111 ;
            CCP1CON = 0b00011100 ;
            break;
            
        case 'C'://nota do# 554.365
            PR2 = 0b11100000 ;
            T2CON = 0b00000111 ;
            CCPR1L = 0b01110000 ;
            CCP1CON = 0b00011100 ;
            break;
            
        case 'd'://Re 587.330
PR2 = 0b11010100 ; 
T2CON = 0b00000111 ;
CCPR1L = 0b01101010 ;
CCP1CON = 0b00011100 ;
            break;
        case'D'://Re# 622.256
PR2 = 0b11001000 ;
T2CON = 0b00000111 ;
CCPR1L = 0b01100100 ;
CCP1CON = 0b00011100 ;
            break;
        case'e'://mi 659.255
PR2 = 0b10111101 ;
T2CON = 0b00000111 ;
CCPR1L = 0b01011110 ;
CCP1CON = 0b00111100 ;
            break;
        case'f'://fa    698.456
PR2 = 0b10110010 ;
T2CON = 0b00000111 ;
CCPR1L = 0b01011001 ;
CCP1CON = 0b00011100 ;
            break;
        case'F'://fa# 739.989
PR2 = 0b10101000 ;
T2CON = 0b00000111 ;
CCPR1L = 0b01010100 ;
CCP1CON = 0b00011100 ;
            break;
        case 'g'://sol 783.991
PR2 = 0b10011110 ;
T2CON = 0b00000111 ;
CCPR1L = 0b01001111 ;
CCP1CON = 0b00011100 ;
            break;
        case 'G'://sol#  830.609
PR2 = 0b10010101 ;
T2CON = 0b00000111 ;
CCPR1L = 0b01001010 ;
CCP1CON = 0b00111100 ;
            break;
        case 'a'://la   880
PR2 = 0b10001101 ;
T2CON = 0b00000111 ;
CCPR1L = 0b01000110 ;
CCP1CON = 0b00111100 ;
            break;
        case 'A'://la#      932.328
PR2 = 0b10000101 ;
T2CON = 0b00000111 ;
CCPR1L = 0b01000010 ;
CCP1CON = 0b00111100 ;
            break;
        case 'b'://si   987
PR2 = 0b01111110 ;
T2CON = 0b00000111 ;
CCPR1L = 0b00111111 ;
CCP1CON = 0b00011100 ;
            break;
        default:
               PR2 = 0 ;
            T2CON = 0 ;
            CCPR1L = 0 ;
            CCP1CON = 0;                  
            break;
            
    }
}
    
void AmazingGrace(){
 /*   tocarNota('d');
    wait_in_ms(700);
    tocarNota('g');
    wait_in_ms(1400);
    tocarNota('b');
    wait_in_ms(350);
    tocarNota('a');
    wait_in_ms(350);
    tocarNota('g');
    wait_in_ms(350);
    tocarNota('b');
    wait_in_ms(1400);
    tocarNota('a');
    wait_in_ms(700);
    tocarNota('g');
    wait_in_ms(1400);
    tocarNota('e');
    wait_in_ms(700);
    tocarNota('d');
    wait_in_ms(1400);
    tocarNota('d');
    wait_in_ms(700);
    */
       
}