/*
 * TIMER1_PROG.c
 *
 * Created: 2/17/2024 8:37:11 PM
 *  Author: biso2
 */ 
#include "TIMER1_INT.h"
#include "STD_TYPES.h"
#include "BIT_MATH.h"

void TIMER1_initFastPwmMod14()
{
	//force bit
	SET_BIT(TCCR1A,FOC1A);
	
	//select fast PWM mode 14
	CLEAR_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
	
	#if(TIMER1_PWM_MODE == TIMER1_PWM_NON_INVERTING)
	{
		CLEAR_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
	}
	#elif(TIMER1_PWM_MODE == TIMER1_PWM_INVERTING)
	{
		SET_BIT(TCCR1A,COM1A0);
		SET_BIT(TCCR1A,COM1A1);
	}
	#endif
}

void TIMER1_setDuty(f32 duty)
{
	#if(TIMER1_PWM_MODE == TIMER1_PWM_NON_INVERTING)
	{
		OCR1A = ((duty*ICR1/100.0) -1);
	}
	#elif(TIMER1_PWM_MODE == TIMER1_PWM_INVERTING)
	{
		
	}
	#endif
}

void TIMER1_setFrequency(u16 pwm_frequency)
{
	//ICR1 = 4999;//-> 50 Hz
	ICR1 = (16000000/(64.0*pwm_frequency))-1;
	
	// select prescaler 64
	SET_BIT(TCCR1B,CS10);
	SET_BIT(TCCR1B,CS11);
	CLEAR_BIT(TCCR1B,CS12);
}