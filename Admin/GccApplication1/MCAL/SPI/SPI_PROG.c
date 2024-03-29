/*
 * SPI_PROG.c
 *
 * Created: 3/1/2024 9:33:38 PM
 *  Author: biso2
 */ 
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "UART_INT.h"
#include "EXT_INT.h"
#include "DIO_INT.h"
#include "SPI_INT.h"
#include "MEM_INT.h"
#define F_CPU 16000000
#include <util/delay.h>


void SPI_Init()
{
	CLEAR_BIT(SPCR,MSTR);
	DIO_setPinDir(DIO_PINB5,DIO_OUTPUT);
	DIO_setPinDir(DIO_PINB7,DIO_OUTPUT);
	DIO_setPinDir(DIO_PINB6,DIO_INPUT);
	DIO_setPinDir(DIO_PINB4,DIO_OUTPUT);
	SET_BIT(SPCR,SPIE); //Enable Interrupts for the SPI module

	
	//SET_BIT(SREG, 7);
	SET_BIT(SPCR,SPE);

	
}
u8 SPI_Read()
{
	while(GET_BIT(SPSR,SPIF)==0);
	return SPDR;
}
void SPI_Write(u8 data)
{
	DIO_setPinValue(DIO_PINB4,DIO_HIGH);
	DIO_setPinValue(DIO_PINB4,DIO_LOW);
	SPDR=data;
	while(GET_BIT(SPSR,SPIF)==0);
}
// SPI interrupt service routine using __vector keyword

void control(u8 Val)
{
	
	if(Val=='g')
		{
			DIO_setPinValue(DIO_PINA0,DIO_HIGH);
			LCD_goto(0,2);
			LCD_writeStr("L1");
		}
	else if(Val=='h')
		{
			DIO_setPinValue(DIO_PINA1,DIO_HIGH);
			LCD_goto(2,2);
			LCD_writeStr("L2");
		}
	else if(Val=='i')
		{
			DIO_setPinValue(DIO_PINA2,DIO_HIGH);
			LCD_goto(4,2);
			LCD_writeStr("L3");
		}
	else if(Val=='j')
		{
			DIO_setPinValue(DIO_PINA3,DIO_HIGH);
			LCD_goto(6,2);
			LCD_writeStr("L4");
		}
	else if(Val=='k')
		{
			DIO_setPinValue(DIO_PINA4,DIO_HIGH);
			LCD_goto(8,2);
			LCD_writeStr("L5");
		}
	else if(Val=='l')
		{
			DIO_setPinValue(DIO_PINA0,DIO_LOW);
			LCD_goto(0,2);
			LCD_writeStr("  ");
		}
	else if(Val=='m')
		{
			DIO_setPinValue(DIO_PINA1,DIO_LOW);
			LCD_goto(2,2);
			LCD_writeStr("  ");
		}
	else if(Val=='n')
		{
			DIO_setPinValue(DIO_PINA2,DIO_LOW);
			LCD_goto(4,2);
			LCD_writeStr("  ");
		}
	else if(Val=='o')
		{
			DIO_setPinValue(DIO_PINA3,DIO_LOW);
			LCD_goto(6,2);
			LCD_writeStr("  ");
		}
	else if(Val=='p')
		{
			DIO_setPinValue(DIO_PINA4,DIO_LOW);
			LCD_goto(8,2);
			LCD_writeStr("  ");
		}
	else if(Val == 'a')
		{ 
		LED_DIMMER(0);
		LCD_goto(10,2);
		LCD_writeStr("      ");
		} 
	else if(Val == 'b')
		{
			LED_DIMMER(1);
			LCD_goto(10,2);
			LCD_writeStr("Dim L1");
		}
	else if(Val == 'c')
		{
			LED_DIMMER(2);
			LCD_goto(10,2);
			LCD_writeStr("Dim L2");
		}
	else if(Val == 'd')
		{
			LED_DIMMER(3);
			LCD_goto(10,2);
			LCD_writeStr("Dim L3");
		}
	else if(Val == 'e')
		{
			LED_DIMMER(4);
			LCD_goto(10,2);
			LCD_writeStr("Dim L4");
		} 
	else if(Val == 'f')
		{
			LED_DIMMER(0);
			LCD_goto(10,2);
			LCD_writeStr("Dim L5");
		}	 	 	 
		

}
void __vector_12(void) __attribute__((signal,used));
void __vector_12(void) 
{
	u8 Val=SPI_Read();
		control(Val);
	// Add any processing code here
}
