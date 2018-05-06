
#include <pic18f4550.h>

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "config.h"
#include "definicionPines.h"
#include <time.h>
#include <string.h>
#include "i2c.h"
#include"GiroAceleroDefines.h"
#define I2C_SCL_PIN PORTBbits.RB1
#define I2C_SDA_PIN PORTBbits.RB0


void I2C_Inicializar(){
  

    TRISB0 = 1;                     /* Set up I2C lines by setting as input */
    TRISB1 = 1;
    SSPSTAT = 80;                   /* Slew rate disabled, other bits are cleared */
    SSPCON1 = 0x28;		/* Enable SSP port for I2C Master mode, clock = FOSC / (4 * (SSPADD+1))*/ 
    SSPCON2 = 0;
    SSPADD = BITRATE;          /* Set clock frequency */  
    SSPIE = 1;                      /* Enable SSPIF interrupt */
    SSPIF = 0;

}




char I2C_Start(char slave_write_address)
{   
    SSPCON2bits.SEN = 1;            /* Send START condition */
    while(SSPCON2bits.SEN);         /* Wait for completion of START */
    SSPIF=0;
    if(!SSPSTATbits.S)              /* Return 0 if START is failed */
    return 0;
    return (I2C_Write(slave_write_address)); /* Write slave device address with write to communicate */
}





void I2C_Ack(){
     ACKDT = 0;  					/* Acknowledge data 1:NACK,0:ACK */
    ACKEN = 1;        				/* Enable ACK to send */
    while(ACKEN);

}

void I2C_Nack()
{
    ACKDT = 1;          			/* Not Acknowledge data 1:NACK,0:ACK */
	ACKEN = 1;              		/* Enable ACK to send */	          
    while(ACKEN);
}


char I2C_Read(char flag)            /* Read data from slave devices with 0=Ack & 1=Nack */
{
    char buffer;
    RCEN = 1;                       /* Enable receive */
    while(!SSPSTATbits.BF);         /* Wait for buffer full flag which set after complete byte receive */
    buffer = SSPBUF;                /* Copy SSPBUF to buffer */
    if(flag==0)
        I2C_Ack();                  /* Send acknowledgment */
    else
        I2C_Nack();                 /* Send negative acknowledgment */
    I2C_Ready();
    return(buffer);
}

void I2C_Ready()
{
    while(!SSPIF);                  /* Wait for operation complete */
    SSPIF=0;                        /*clear SSPIF interrupt flag*/
}

char I2C_Write(unsigned char data)
{
      SSPBUF = data;                /* Write data to SSPBUF */
      I2C_Ready();
      if (ACKSTAT)                  /* Return 2 if acknowledgment received else 1 */
        return 1;
      else
        return 2;
}

char I2C_Repeated_Start(char slave_read_address)
{
    RSEN = 1;                       /* Send REPEATED START condition */
    while(SSPCON2bits.RSEN);        /* Wait for completion of REPEATED START condition */
    SSPIF = 0;
    if(!SSPSTATbits.S)              /* Return 0 if REPEATED START is failed */
    return 0;
    I2C_Write(slave_read_address);  /* Write slave device address with read to communicate */
    if (ACKSTAT)                    /* Return 2 if acknowledgment received else 1 */
     return 1;
    else
     return 2;
}


void I2C_Start_Wait(char slave_write_address)
{
  while(1)
  {   
    SSPCON2bits.SEN = 1;            /* Send START condition */
    while(SSPCON2bits.SEN);         /* Wait for completion of START */
    SSPIF = 0;
    if(!SSPSTATbits.S)              /* Continue if START is failed */
        continue;
    I2C_Write(slave_write_address); /* Write slave device address with write to communicate */
    if(ACKSTAT)                     /* Check whether Acknowledgment received or not */
    {
        I2C_Stop();                 /* If not then initiate STOP and continue */
        continue;
    }    
    break;                          /* If yes then break loop */
  }
}

void Aceletometro_Init()										/* Gyro initialization function */
{
	wait_in_ms(150);		/* Power up time >100ms */
	I2C_Start_Wait(0xD0);	/* Start with device write address */
	I2C_Write(SMPLRT_DIV);	/* Write to sample rate register */
	I2C_Write(0x07);	/* 1KHz sample rate */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(PWR_MGMT_1);	/* Write to power management register */
	I2C_Write(0x01);	/* X axis gyroscope reference frequency */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(CONFIG);	/* Write to Configuration register */
	I2C_Write(0x00);	/* Fs = 8KHz */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(GYRO_CONFIG);	/* Write to Gyro configuration register */
	I2C_Write(0x18);	/* Full scale range +/- 2000 degree/C */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(INT_ENABLE);	/* Write to interrupt enable register */
	I2C_Write(0x01);
	I2C_Stop();

}

void Acelerometro_Start()

{
	I2C_Start_Wait(0xD0);								/* I2C start with device write address */
	I2C_Write(ACCEL_XOUT_H);							/* Write start location address from where to read */ 
	I2C_Repeated_Start(0xD1);							/* I2C start with device read address */
}

char I2C_Stop()
{
    PEN = 1;                        /* Initiate STOP condition */
    while(PEN);                     /* Wait for end of STOP condition */
    SSPIF = 0;
    if(!SSPSTATbits.P);             /* Return 0 if STOP failed */
    return 0;
}
