/*
 * KEYPAD_PROG.c
 *
 * Created: 2/5/2024 2:46:51 PM
 *  Author: biso2
 */ 
#include "KEYPAD_INT.h"
#include "DIO_INT.h"

void KEYPAD_init()
{
	DIO_setPinDir(KEYPAD_ROW0, DIO_INPUT);
	DIO_setPinDir(KEYPAD_ROW1, DIO_INPUT);
	DIO_setPinDir(KEYPAD_ROW2, DIO_INPUT);
	DIO_setPinDir(KEYPAD_ROW3, DIO_INPUT);
	
	DIO_setPinPullup(KEYPAD_ROW0);
	DIO_setPinPullup(KEYPAD_ROW1);
	DIO_setPinPullup(KEYPAD_ROW2);
	DIO_setPinPullup(KEYPAD_ROW3);
	
	DIO_setPinDir(KEYPAD_COL0, DIO_OUTPUT);
	DIO_setPinDir(KEYPAD_COL1, DIO_OUTPUT);
	DIO_setPinDir(KEYPAD_COL2, DIO_OUTPUT);
	DIO_setPinDir(KEYPAD_COL3, DIO_OUTPUT);
	
}

u8 KEYPAD_read()
{
	
	DIO_setPinValue(KEYPAD_COL0, DIO_LOW);
	DIO_setPinValue(KEYPAD_COL1, DIO_HIGH);
	DIO_setPinValue(KEYPAD_COL2, DIO_HIGH);
	DIO_setPinValue(KEYPAD_COL3, DIO_HIGH);
	
	if(DIO_readPinValue(KEYPAD_ROW0) == DIO_LOW)
	{
		return KEYPAD_ROW0_COL0;
	}
	else if(DIO_readPinValue(KEYPAD_ROW1) == DIO_LOW)
	{
		return KEYPAD_ROW1_COL0;
	}
	else if(DIO_readPinValue(KEYPAD_ROW2) == DIO_LOW)
	{
		return KEYPAD_ROW2_COL0;
	}
	else if(DIO_readPinValue(KEYPAD_ROW3) == DIO_LOW)
	{
		return KEYPAD_ROW3_COL0;
	}
	
	
	
	
	
	DIO_setPinValue(KEYPAD_COL0, DIO_HIGH);
	DIO_setPinValue(KEYPAD_COL1, DIO_LOW);
	DIO_setPinValue(KEYPAD_COL2, DIO_HIGH);
	DIO_setPinValue(KEYPAD_COL3, DIO_HIGH);
	
	if(DIO_readPinValue(KEYPAD_ROW0) == DIO_LOW)
	{
		return KEYPAD_ROW0_COL1;
	}
	else if(DIO_readPinValue(KEYPAD_ROW1) == DIO_LOW)
	{
		return KEYPAD_ROW1_COL1;
	}
	else if(DIO_readPinValue(KEYPAD_ROW2) == DIO_LOW)
	{
		return KEYPAD_ROW2_COL1;
	}
	else if(DIO_readPinValue(KEYPAD_ROW3) == DIO_LOW)
	{
		return KEYPAD_ROW3_COL1;
	}
	
	
	
	DIO_setPinValue(KEYPAD_COL0, DIO_HIGH);
	DIO_setPinValue(KEYPAD_COL1, DIO_HIGH);
	DIO_setPinValue(KEYPAD_COL2, DIO_LOW);
	DIO_setPinValue(KEYPAD_COL3, DIO_HIGH);
	
	if(DIO_readPinValue(KEYPAD_ROW0) == DIO_LOW)
	{
		return KEYPAD_ROW0_COL2;
	}
	else if(DIO_readPinValue(KEYPAD_ROW1) == DIO_LOW)
	{
		return KEYPAD_ROW1_COL2;
	}
	else if(DIO_readPinValue(KEYPAD_ROW2) == DIO_LOW)
	{
		return KEYPAD_ROW2_COL2;
	}
	else if(DIO_readPinValue(KEYPAD_ROW3) == DIO_LOW)
	{
		return KEYPAD_ROW3_COL2;
	}
	
	
	DIO_setPinValue(KEYPAD_COL0, DIO_HIGH);
	DIO_setPinValue(KEYPAD_COL1, DIO_HIGH);
	DIO_setPinValue(KEYPAD_COL2, DIO_HIGH);
	DIO_setPinValue(KEYPAD_COL3, DIO_LOW);
	
	if(DIO_readPinValue(KEYPAD_ROW0) == DIO_LOW)
	{
		return KEYPAD_ROW0_COL3;
	}
	else if(DIO_readPinValue(KEYPAD_ROW1) == DIO_LOW)
	{
		return KEYPAD_ROW1_COL3;
	}
	else if(DIO_readPinValue(KEYPAD_ROW2) == DIO_LOW)
	{
		return KEYPAD_ROW2_COL3;
	}
	else if(DIO_readPinValue(KEYPAD_ROW3) == DIO_LOW)
	{
		return KEYPAD_ROW3_COL3;
	}
	
	return KEYPAD_UNPRESSED;
	
}