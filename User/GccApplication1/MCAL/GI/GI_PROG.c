/*
 * GI_PROG.c
 *
 * Created: 2/7/2024 2:31:51 AM
 *  Author: biso2
 */ 


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GI_INT.h"

void GI_enable()
{
	SET_BIT(SREG, I);
}

void GI_disable()
{
	CLEAR_BIT(SREG , I);
}