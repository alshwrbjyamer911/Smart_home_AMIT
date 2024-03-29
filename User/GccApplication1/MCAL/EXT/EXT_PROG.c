/*
 * EXT_PROG.c
 *
 * Created: 2/7/2024 2:01:06 AM
 *  Author: biso2
 */ 
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#define F_CPU 16000000
#include <util/delay.h>
#include "EXT_INT.h"
#include "DIO_INT.h"
#include "KEYPAD_INT.h"
#include "LCD_INT.h"
#include "MEM_INT.h"
#include "SPI_INT.h"


void EXT0_init(u8 level)
{
	if(level == EXT_LOW_LEVEL)
	{
		CLEAR_BIT(MCUCR,ISC00);
		CLEAR_BIT(MCUCR,ISC01);
	}
	else if(level == EXT_ANY_LOGICAL)
	{
		SET_BIT(MCUCR,ISC00);
		CLEAR_BIT(MCUCR,ISC01);
	}
	else if(level == EXT_FALLING)
	{
		CLEAR_BIT(MCUCR,ISC00);
		SET_BIT(MCUCR,ISC01);
	}
	else if( level == EXT_RISING)
	{
		SET_BIT(MCUCR,ISC00);
		SET_BIT(MCUCR,ISC01);
		
	}
	//enable INT0
	SET_BIT(GICR, INT0);
	
}




void EXT1_init(u8 level)
{
	if(level == EXT_LOW_LEVEL)
	{
		CLEAR_BIT(MCUCR,ISC10);
		CLEAR_BIT(MCUCR,ISC11);
	}
	else if(level == EXT_ANY_LOGICAL)
	{
		SET_BIT(MCUCR,ISC10);
		CLEAR_BIT(MCUCR,ISC11);
	}
	else if(level == EXT_FALLING)
	{
		CLEAR_BIT(MCUCR,ISC10);
		SET_BIT(MCUCR,ISC11);
	}
	else if( level == EXT_RISING)
	{
		SET_BIT(MCUCR,ISC10);
		SET_BIT(MCUCR,ISC11);
		
	}
	//enable INT0
	SET_BIT(GICR, INT1);
		
	
}
void EXT2_init(u8 level)
{
    if(level == EXT_FALLING)
	{
		CLEAR_BIT(MCUCSR,ISC2);
	}
	else if( level == EXT_RISING)
	{
		SET_BIT(MCUCSR,ISC2);
		
	}
	//enable INT0
	SET_BIT(GICR, INT2);
	
		
	
}

//pointer to function
void (*INT0_ptr)();

void EXT_setCallbackInt0(void (*ptr)())
{
	//INT0_ptr = APP_func;
	INT0_ptr = ptr;
}
void __vector_1(void) __attribute__((signal,used));
void __vector_1(void)
{
	//call func(pointer to function)
	//APP_func();
	INT0_ptr();
	
	
}

void (*INT1_ptr)();

void EXT_setCallbackInt1(void (*ptr)())
{
	//INT0_ptr = APP_func;
	INT1_ptr = ptr;
}

void __vector_2(void) __attribute__((signal,used));
void __vector_2(void)
{
	//call func(pointer to function)
	//APP_func();
	INT1_ptr();
	//DIO_setPinValue(DIO_PINA0,DIO_HIGH);
}
void (*INT2_ptr)();

void EXT_setCallbackInt2(void (*ptr)())
{
	//INT0_ptr = APP_func;
	INT2_ptr = ptr;
}

void __vector_3(void) __attribute__((signal,used));
void __vector_3(void)
{
	//call func(pointer to function)
	//APP_func();
	INT2_ptr();
	//DIO_setPinValue(DIO_PINA0,DIO_HIGH);
}

