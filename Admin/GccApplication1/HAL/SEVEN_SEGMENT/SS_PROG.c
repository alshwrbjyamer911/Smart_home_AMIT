/*
 * SS_PROG.c
 *
 * Created: 1/27/2024 7:24:03 PM
 *  Author: biso2
 */ 

#include "DIO_INT.h"
#include "SS_INT.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
# define F_CPU 1000000
#include <util/delay.h>

void SS_init()
{
	DIO_setPinDir(SS_E1,DIO_OUTPUT);
	DIO_setPinDir(SS_E2,DIO_OUTPUT);
	DIO_setPinDir(SS_S0,DIO_OUTPUT);
	DIO_setPinDir(SS_S1,DIO_OUTPUT);
	DIO_setPinDir(SS_S2,DIO_OUTPUT);
	DIO_setPinDir(SS_S3,DIO_OUTPUT);

}

void SS_setEnable1()
{
	
	DIO_setPinValue(SS_E1,DIO_HIGH);
}
void SS_setEnable2()
{
	DIO_setPinValue(SS_E2,DIO_HIGH);
}

void SS_setdisable1()
{
	DIO_setPinValue(SS_E1,DIO_LOW);
}
void SS_setdisable2()
{
	DIO_setPinValue(SS_E2,DIO_LOW);
}

void SS_writeNumber(u8 num)
{
	SS_setEnable1();
	SS_setdisable2();
	u8 s=num/10;
	DIO_setPinValue(SS_S0,GET_BIT(s,0));
	DIO_setPinValue(SS_S1,GET_BIT(s,1));
	DIO_setPinValue(SS_S2,GET_BIT(s,2));
	DIO_setPinValue(SS_S3,GET_BIT(s,3));
    _delay_ms(20);
	SS_setdisable1();
	SS_setEnable2();
	s=num%10;
	DIO_setPinValue(SS_S0,GET_BIT(s,0));
	DIO_setPinValue(SS_S1,GET_BIT(s,1));
	DIO_setPinValue(SS_S2,GET_BIT(s,2));
	DIO_setPinValue(SS_S3,GET_BIT(s,3));
    _delay_ms(20);
}

