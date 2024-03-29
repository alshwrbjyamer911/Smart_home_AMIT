/*
 * MOTOR_PROG.c
 *
 * Created: 2/23/2024 7:44:36 PM
 *  Author: biso2
 */ 
#include "DIO_INT.h"
#include "STD_TYPES.h"
#include "MOTOR_INIT.h"
#include "TIMER1_INT.h"
#define MOTOR_RIGHT 0
#define MOTOR_LEFT 1
static void MOTOR_setDir(u8 dir)
{
	DIO_setPinDir(DIO_PINC5, DIO_OUTPUT);
	DIO_setPinDir(DIO_PINC6, DIO_OUTPUT);
	if(dir==MOTOR_LEFT)
	{
		DIO_setPinValue(DIO_PINC5, DIO_LOW);
		DIO_setPinValue(DIO_PINC6, DIO_HIGH);
	}
	else if(dir==MOTOR_RIGHT)
	{
		DIO_setPinValue(DIO_PINC5, DIO_HIGH);
		DIO_setPinValue(DIO_PINC6, DIO_LOW);
	}
}
static void MOTOR_setSpeed(u8 duty)
{
	TIMER1_setDuty(duty);
}
void MOTOR_start(u8 duty,u8 dir)
{
	TIMER1_initFastPwmMod14();
	TIMER1_setFrequency(1000);
	MOTOR_setSpeed(duty);
	MOTOR_setDir(dir);

}