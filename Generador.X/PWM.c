#include <pic18f4550.h>

#include "config.h"

void PWMfrecuenciau(unsigned int freq, unsigned int cristal){
   //se mete la frecuencia y el critsal y te da el pr2
    PR2=(cristal/64*freq)-1;
}

void PWMint(unsigned char status){
   //inicializa el PWM con todo y prescalador a 16
    T2CON=0b00000011;
    TMR2ON=status;
  
   
}

void PWMduty( float duty,unsigned int freq, unsigned int cristal){

     int test=((duty/freq)*(cristal))/16;
    
    
}