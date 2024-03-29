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
#include "UART_INT.h"
#include "MEM_INT.h"


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
DIO_setPinDir(DIO_PINA7,DIO_OUTPUT);
DIO_setPinDir(DIO_PINA6,DIO_OUTPUT);
DIO_setPinDir(DIO_PINA5,DIO_OUTPUT);


u8 msg[]="A user need to access. press k to allow the user: ";
UART_sendString(msg);
//u8 flag=0;
//flag=adminLogin();
u8 adminAnswer=UART_receiveData();

//if (flag)
//{

if(adminAnswer == 'k')
{
	DIO_setPinValue(DIO_PINA6, DIO_HIGH);
	DIO_setPinValue(DIO_PINA5, DIO_HIGH);
	_delay_ms(100);
	DIO_setPinValue(DIO_PINA6, DIO_LOW);
	DIO_setPinValue(DIO_PINA5, DIO_LOW);
}
else
{
	DIO_setPinValue(DIO_PINA7, DIO_HIGH);
	DIO_setPinValue(DIO_PINA5, DIO_HIGH);
	_delay_ms(100);
	DIO_setPinValue(DIO_PINA7, DIO_LOW);
	DIO_setPinValue(DIO_PINA5, DIO_LOW);
}
//}
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

