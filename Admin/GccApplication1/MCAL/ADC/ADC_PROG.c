/*
 * ADC_PROG.c
 *
 * Created: 2/9/2024 7:23:38 PM
 *  Author: biso2
 */ 
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXT_INT.h"
#include "DIO_INT.h"
#include "ADC_INT.h"
void ADC_init()
{
	//Select ref voltage(AVCC)
	SET_BIT(ADMUX,REFS0);
	CLEAR_BIT(ADMUX,REFS1);

	//select prescaler
	SET_BIT(ADCSRA,ADPS0);
	SET_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS2);

	//enable
	SET_BIT(ADCSRA,ADEN);

}

u16 ADC_read(u8 channel)//return digital
{
	//select ch
	if (channel==ADC0)
	{
	
	CLEAR_BIT(ADMUX,MUX0);
	CLEAR_BIT(ADMUX,MUX1);
	CLEAR_BIT(ADMUX,MUX2);
	CLEAR_BIT(ADMUX,MUX3);
	CLEAR_BIT(ADMUX,MUX4);
	}
	else if (channel==ADC1)
	{
		
		SET_BIT(ADMUX,MUX0);
		CLEAR_BIT(ADMUX,MUX1);
		CLEAR_BIT(ADMUX,MUX2);
		CLEAR_BIT(ADMUX,MUX3);
		CLEAR_BIT(ADMUX,MUX4);
	}
	else if (channel==ADC2)
	{
		
		CLEAR_BIT(ADMUX,MUX0);
		SET_BIT(ADMUX,MUX1);
		CLEAR_BIT(ADMUX,MUX2);
		CLEAR_BIT(ADMUX,MUX3);
		CLEAR_BIT(ADMUX,MUX4);
	}

	//start conv
	SET_BIT(ADCSRA,ADSC);
	//check if finish
	while (	GET_BIT(ADCSRA,ADSC));

	//read result
	return ADCLH;
}

f32 ADC_convertAnalog(u16 digitalValue)//return analog
{
	return (5.0/1024.0)*digitalValue;
	
}

