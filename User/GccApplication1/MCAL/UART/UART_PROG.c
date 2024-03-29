/*
 * UART_PROG.c
 *
 * Created: 2/24/2024 8:15:35 PM
 *  Author: biso2
 */ 
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "UART_PRIV.h"
#include "UART_CONFIG.h"
#include "UART_INT.h"
void UART_init()
{
	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,TXEN);
	
	u8 x=0b10000000;
	#if(UART_NUM_BIT_MODE==UART_8BIT_MODE)
	SET_BIT(UCSRB,UCSZ2);
	SET_BIT(x,UCSZ1);
	SET_BIT(x,UCSZ2);


	#elif(UART_NUM_BIT_MODE==UART_7BIT_MODE)

	#endif
	#if(UART_NUM_STOP_BIT==UART_STOP_1BIT)
	CLEAR_BIT(x,USBS);
	#elif(UART_NUM_STOP_BIT==UART_STOP_2BIT)
	SET_BIT(x,USBS);

	#endif
	#if(UART_PARITY_MODE==UART_PARITY_DISABLED)
	CLEAR_BIT(x,UPM0);
	CLEAR_BIT(x,UPM1);

	#elif(UART_PARITY_MODE==UART_PARITY_EVEN)
	CLEAR_BIT(x,UPM0);
	SET_BIT(x,UPM1);
	#endif
	UCSRC_UBRRH=x;
	UBRRL=UART_BAUD_9600;

}
void UART_sendData(u8 data)
{
	// data register e,pty
	while(GET_BIT(UCSRA,UDRE)==0);
	//send
	UDR= data;
}
void UART_sendString(u8* str)
{
		u8 i=0;
		while(str[i] != '\0')
		{
			UART_sendData(str[i]);
			i++;
		}
}

u8 UART_receiveData()
{
	//CHECK RECEIVE COMPLETE
	u32 timeout=0;

	while(GET_BIT(UCSRA,RXC)==0)
	{
		timeout++;
		if (timeout==100000)
		{
			return UART_NOT_RECEIVED;
		}
	}
	//READ DATA
	return UDR;
}