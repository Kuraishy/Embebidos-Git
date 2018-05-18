
#include "Pwm Header.h"
#include "config.h"
#include <xc.h>
#include <string.h>
#define _XTAL_FREQ 48000000 //Se define la frecuencia con la que trebaja nuestro oscilador para que tenga un areferencia con el comando __delay_ms
 
/*********************************Funcion Principal*********************************/



/*********************************Funcion TIMER2*********************************/

void config_timer2(int onoff, int presc)
{
    T2CONbits.TOUTPS = 0b0000; //El postsacale no se implementan
    
    prescg = presc; //Se asigna a la variable global ya que este valor se utilizara para formulas proximas
    
    switch(presc)
    {
        case 1: T2CONbits.T2CKPS = 0b00; break; //Prescaler de 1 
        case 4: T2CONbits.T2CKPS = 0b01; break; //Prescaler de 4
        case 16: T2CONbits.T2CKPS = 0b11; break; //Prescaler de 16 El ultimo bit es indiferente))
    }
    /*********************************Registro T2CON*********************************/
    T2CONbits.TOUTPS = 0b0000; //El postsacale no se implementan
    
    T2CONbits.TMR2ON = onoff; //Se mantiene apagado el timer2
    
}
 
/*********************************Funcion CCP1CON*********************************/
void coinfig_ccpcon(float fosc, float freq)
{
    PR2 = ((fosc/(4*freq*prescg))-1);
    pr2g = PR2;
    CCP1CONbits.P1M = 0b00; //P1A
    CCP2CONbits.CCP2M = 1100; //Modo PWM
    CCP1CONbits.CCP1M = 1100; //MOdo PWM
}

void config_ccp1(int duty1)
{
    int valreg;
    
    valreg = (duty1*(pr2g + 1)*4)/100;
    
    //Convercion del valor valreg a binario
    int n,x,i,j,z;
    unsigned int w,y;
	int a[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    
	n = valreg;
	i = 0;
    z = 0;
	y = 0;
    w = 0;
	
	while(n > 0)
	{
		a[i] = n % 2;
		n = n / 2;
		i++;
	}
	
	for(j = 0 ; j <=  1; j++)
	{
		x = a[j] * (pow (2,j)); //Elevar un numero a la potencia y^x
		y = x + y;
	}
    for(j = 2 ; j <=  9; j++)
	{
		x = a[j] * (pow (2,z)); //Elevar un numero a la potencia y^x
		w = x + w;
		z++;
	}
    
    CCP1CONbits.DC1B = y; //Valores obtenidos Del CCPxCON en la formula
    CCPR1L = w; // Valor obtenido en la formula 
    
}


void config_ccp2(int duty2)
{
    int valreg;
    
    valreg = (duty2*(pr2g + 1)*4)/100;
    
    //Convercion del valor valreg a binario
    int n,x,i,j,z;
    unsigned int w,y;
	int a[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    
	n = valreg;
	i = 0;
    z = 0;
	y = 0;
    w = 0;
	
	while(n > 0)
	{
		a[i] = n % 2;
		n = n / 2;
		i++;
	}
	
	for(j = 0 ; j <=  1; j++)
	{
		x = a[j] * (pow (2,j)); //Elevar un numero a la potencia y^x
		y = x + y;
	}
    for(j = 2 ; j <=  9; j++)
	{
		x = a[j] * (pow (2,z)); //Elevar un numero a la potencia y^x
		w = x + w;
		z++;
	}
    
   CCP2CONbits.DC2B = y; //Valores obtenidos Del CCPxCON en la formula
   CCPR2L = w;// Valor obtenido en la formula 
    
}
