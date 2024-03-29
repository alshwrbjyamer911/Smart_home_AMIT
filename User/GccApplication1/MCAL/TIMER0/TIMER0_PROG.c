/*
 * TIMER0_PROG.c
 *
 * Created: 2/10/2024 7:49:54 PM
 *  Author: biso2
 */ 
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER0_INT.h"

void TIMER0_initNormalMode()
{
	//select Normal Mode
	CLEAR_BIT(TCCR0,WGM00);
	CLEAR_BIT(TCCR0,WGM01);

	//Enable Interrupt(overflow)
	SET_BIT(TIMSK,TOIE0);
	
}
void TIMER0_initCTCMode()
{
	    //force bit
		SET_BIT(TCCR0,FOC0);

		//select CTC
			CLEAR_BIT(TCCR0,WGM00);
			SET_BIT(TCCR0,WGM01);

		//Enable Interrupt(Compare match)
		SET_BIT(TIMSK,OCIE0);
		
		#if (ocPinMode==OCO_DICONNECTED)
		{
			CLEAR_BIT(TCCR0,COM00);
			CLEAR_BIT(TCCR0,COM01);


		}
		#elif (ocPinMode==OCO_TOGGLE)
		{
			SET_BIT(TCCR0,COM00);
			CLEAR_BIT(TCCR0,COM01);	
		}
		#elif (ocPinMode==OCO_SET)
		{
			SET_BIT(TCCR0,COM00);
			SET_BIT(TCCR0,COM01);
		}
		#elif (ocPinMode==OCO_CLEAR)
		{
			SET_BIT(TCCR0,COM00);
			CLEAR_BIT(TCCR0,COM01);
		}
		#endif
		
}
void TIMER0_initFastPwm()
{
		CLEAR_BIT(TCCR0,FOC0);

		//select Normal Mode
		SET_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);
		#if(PWM_MODE==PWM_NON_INVERTING)
		{
			CLEAR_BIT(TCCR0,COM00);
			SET_BIT(TCCR0,COM01);
		}
		#elif(PWM_MODE==PWM_INVERTING)
		{
			SET_BIT(TCCR0,COM00);
			SET_BIT(TCCR0,COM01);		
		}
		#endif
}
void TIMER0_setOCR(u8 num)
{
	OCR0=num;
}


void TIMER0_start(u8 prescaler)
{
	if(prescaler == TIMER0_CLK_DIV_1)
	{
		SET_BIT(TCCR0,CS00);
		CLEAR_BIT(TCCR0,CS01);
		CLEAR_BIT(TCCR0,CS02);
	}
	else if(prescaler == TIMER0_CLK_DIV_8)
	{
		CLEAR_BIT(TCCR0,CS00);
		SET_BIT(TCCR0,CS01);
		CLEAR_BIT(TCCR0,CS02);
	}
	else if(prescaler == TIMER0_CLK_DIV_64)
	{
				SET_BIT(TCCR0,CS00);
				SET_BIT(TCCR0,CS01);
				CLEAR_BIT(TCCR0,CS02);
	}
	else if(prescaler == TIMER0_CLK_DIV_256)
	{
		CLEAR_BIT(TCCR0,CS00);
		CLEAR_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS02);
	}
	else if(prescaler == TIMER0_CLK_DIV_1024)
	{
		SET_BIT(TCCR0,CS00);
		CLEAR_BIT(TCCR0,CS01);
		SET_BIT(TCCR0,CS02);
	}
	
	
}


void TIMER0_stop()
{
	CLEAR_BIT(TCCR0,CS00);
	CLEAR_BIT(TCCR0,CS01);
	CLEAR_BIT(TCCR0,CS02);
}

void TIMER0_setPreload(u8 ticks)
{
	TCNT0 = ticks;
}

u8 TIMER0_readTimer()
{
	return TCNT0;
}

void (*OV_ptr)();

void TIMER0_setCallback( void (*APP_func)() )
{
	OV_ptr = APP_func;
}

//ISR
void __vector_11(void) __attribute__((signal,used));
void __vector_11(void)
{
	//toggleLed();
	OV_ptr();
	
}


void (*CTC_ptr)();

void TIMER0_setCallbackCTC( void (*APP_func)() )
{
	CTC_ptr = APP_func;
}

//ISR
void __vector_10(void) __attribute__((signal,used));
void __vector_10(void)
{
	//toggleLed();
	CTC_ptr();
	
}

void TIMER0_setDuty(u8 duty)
{
			#if(PWM_MODE==PWM_NON_INVERTING)
			{
				OCR0=((duty*256)/100)-1;
			}
			#elif(PWM_MODE==PWM_INVERTING)
			{
				OCR0=((duty*256)/100)-1;
			}
			#endif
}

void TIMER0_setFrequency(u8 pwm_frequency)
{
	if (pwm_frequency==PWM_FREQUENCY_62500)
	{
		TIMER0_start(TIMER0_CLK_DIV_1);
	}
	else if (pwm_frequency==PWM_FREQUENCY_7812)
	{
		TIMER0_start(TIMER0_CLK_DIV_8);

	}
}