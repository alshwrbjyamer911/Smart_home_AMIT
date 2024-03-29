/*
 * WDT_PROG.c
 *
 * Created: 2/23/2024 9:39:42 PM
 *  Author: biso2
 */ 
#include "DIO_INT.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "WDT_INIT.h"
void WDT_start(u8 time)
{
	SET_BIT(WDTCR,WDE);
	if (time==WDT_Time0)
	{
	CLEAR_BIT(WDTCR,WDP2);
	CLEAR_BIT(WDTCR,WDP1);
	CLEAR_BIT(WDTCR,WDP0);

	}
	else if (time==WDT_Time1)
	{
		CLEAR_BIT(WDTCR,WDP2);
		CLEAR_BIT(WDTCR,WDP1);
		SET_BIT(WDTCR,WDP0);
	}
	else if (time==WDT_Time2)
	{
		CLEAR_BIT(WDTCR,WDP2);
		SET_BIT(WDTCR,WDP1);
		CLEAR_BIT(WDTCR,WDP0);
	}
	else if (time==WDT_Time3)
	{
		CLEAR_BIT(WDTCR,WDP2);
		SET_BIT(WDTCR,WDP1);
		SET_BIT(WDTCR,WDP0);
	}
	else if (time==WDT_Time4)
	{
		SET_BIT(WDTCR,WDP2);
		CLEAR_BIT(WDTCR,WDP1);
		CLEAR_BIT(WDTCR,WDP0);
	}
	else if (time==WDT_Time5)
	{
		SET_BIT(WDTCR,WDP2);
		CLEAR_BIT(WDTCR,WDP1);
		SET_BIT(WDTCR,WDP0);
	}
	else if (time==WDT_Time6)
	{
		SET_BIT(WDTCR,WDP2);
		SET_BIT(WDTCR,WDP1);
		CLEAR_BIT(WDTCR,WDP0);
	}
	else if (time==WDT_Time7)
	{
		SET_BIT(WDTCR,WDP2);
		SET_BIT(WDTCR,WDP1);
		SET_BIT(WDTCR,WDP0);
	}
}
void WDT_stop()
{
	WDTCR = (1<<WDTOE) | (1<<WDE);
	WDTCR = 0x00;
}