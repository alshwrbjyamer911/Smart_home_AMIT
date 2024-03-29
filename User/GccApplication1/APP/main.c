/*
 * GccApplication2.c
 *
 * Created: 3/1/2024 10:27:52 PM
 * Author : biso2
 */ 

#include "BIT_MATH.h"
# define F_CPU 16000000
#include <util/delay.h>
#include "DIO_INT.h"
#include "STD_TYPES.h"
#include "SPI_INT.h"
#include "UART_INT.h"
#include "I2C_INT.h"
#include "EEPROM_INT.h"
#include "MEM_INT.h"
#include "EXT_INT.h"
#include "GI_INT.h"
#include "KEYPAD_INT.h"
#include "LCD_INT.h"
#include "TIMER0_INT.h"
#include <string.h>
#include "ADC_INT.h"

void AC()
{
	
	
	static u16 counter=0;
	counter++;
	if(counter==1220)
	{
		u16 x = ADC_read(ADC0);
		f32 y = x * (500.0/1023.0);
		if(y>=30)
		{
			DIO_setPinValue(DIO_PINA1,DIO_HIGH);
		}
		else if(y<22)
		{
			DIO_setPinValue(DIO_PINA1,DIO_LOW);
		}
		counter=0;
	}
}
int main(void)
{ 
	
	DIO_setPinDir(DIO_PIND3,DIO_INPUT);
	DIO_setPinDir(DIO_PIND7,DIO_INPUT);
	DIO_setPinDir(DIO_PIND6,DIO_INPUT);
	DIO_setPinDir(DIO_PINA2,DIO_OUTPUT);
	DIO_setPinDir(DIO_PINA1,DIO_OUTPUT);
	DIO_setPinDir(DIO_PINA0,DIO_INPUT);
	DIO_setPinDir(DIO_PINA1,DIO_OUTPUT);
	ADC_init();

	SPI_Init();
	UART_init();
	I2C_init(MASTER);
	GI_enable();
	EXT0_init(EXT_RISING);
	TIMER0_initNormalMode();
	TIMER0_setCallback(AC);
	TIMER0_start(TIMER0_CLK_DIV_256);
	KEYPAD_init();
    LCD_init();
	EXT_setCallbackInt0(ext_fun);
	u8 wrongPass=0;
	u8 signout=1;
	
while (1)
{
	
			
if (wrongPass!=3)
{
	if(userCheck()==1)
	{
		wrongPass=0;
		UART_sendString("waiting admin approval...\r");
		DIO_setPinDir(DIO_PINB0,DIO_OUTPUT);
		DIO_setPinValue(DIO_PINB0,DIO_HIGH);	
		_delay_ms(50);	
		DIO_setPinValue(DIO_PINB0,DIO_LOW);
		
		while ((!DIO_readPinValue(DIO_PIND3)));
		if (DIO_readPinValue(DIO_PIND6))
		{
			UART_sendString("welcome\r");
			
			/////////////////////////////////////////////////
			///////////////////////////////////////////////
			u8 userchoice[10];
			 
			   
			     
				 while (signout==1)
				 {
					 UART_sendString("Write the number of the led then on or off to control it\rPress a number between 1 and 5 to control the dimming\rWrite off to turn dimmer off\rPress s to signout\r");
					 userInput(userchoice);
					 AC();
					 if ((!(strcmp(userchoice,"off"))))
					 {
						 //dimmeroff
						 SPI_Write('a');
					 }
					 else if ((!(strcmp(userchoice,"1"))))
					 {
						// LED_DIMMER(1);
						SPI_Write('b');
					 }
					 else if ((!(strcmp(userchoice,"2"))))
					 {
						// LED_DIMMER(2);
						SPI_Write('c');
					 }
					 else if ((!(strcmp(userchoice,"3"))))
					 {
						 //LED_DIMMER(3);
						 SPI_Write('d');
					 }
					 else if ((!(strcmp(userchoice,"4"))))
					 {
						 //LED_DIMMER(4);
						 SPI_Write('e');
					 }
					 else if ((!(strcmp(userchoice,"5"))))
					 {
						 //LED_DIMMER(5);
						 SPI_Write('f');
					 }
					 else if ((!(strcmp(userchoice,"1 on"))))
					 {
						// DIO_setPinValue(DIO_PINA0,DIO_HIGH);
						SPI_Write('g');
										 }
					 else if ((!(strcmp(userchoice,"2 on"))))
					 {
						 //DIO_setPinValue(DIO_PINA1,DIO_HIGH);
						 SPI_Write('h');
					 }
					 else if ((!(strcmp(userchoice,"3 on"))))
					 {
						// DIO_setPinValue(DIO_PINA2,DIO_HIGH);
						 SPI_Write('i');
					 }
					 else if ((!(strcmp(userchoice,"4 on"))))
					 {
						// DIO_setPinValue(DIO_PINA3,DIO_HIGH);
						 SPI_Write('j');
					 }
					 else if ((!(strcmp(userchoice,"5 on"))))
					 {
						 //DIO_setPinValue(DIO_PINA4,DIO_HIGH);
						 SPI_Write('k');
					 }
					 else if ((!(strcmp(userchoice,"1 off"))))
					 {
						// DIO_setPinValue(DIO_PINA0,DIO_LOW);
						 SPI_Write('l');
					 }
					 else if ((!(strcmp(userchoice,"2 off"))))
					 {
						// DIO_setPinValue(DIO_PINA1,DIO_LOW);
						 SPI_Write('m');
					 }
					 else if ((!(strcmp(userchoice,"3 off"))))
					 {
						// DIO_setPinValue(DIO_PINA2,DIO_LOW);
						 SPI_Write('n');
					 }
					 else if ((!(strcmp(userchoice,"4 off"))))
					 {
						// DIO_setPinValue(DIO_PINA3,DIO_LOW);
						 SPI_Write('o');
					 }
					 else if ((!(strcmp(userchoice,"5 off"))))
					 {
						 //DIO_setPinValue(DIO_PINA4,DIO_LOW);
						 SPI_Write('p');
					 }
					 else if ((!(strcmp(userchoice,"s"))))
					 {
						 signout=0;
					 }
				 }
			 
			/////////////////////////////////////
			/////////////////////////////////////////
			
			
			
			//menu+door
		}
		else if (DIO_readPinValue(DIO_PIND7))
			{
				UART_sendString("Access Denied");
				UART_sendData(13);
				UART_sendData(10);
			}
	}
	else 
	{
   		UART_sendString("Wrong Username or Password");
		wrongPass++;

	}
}
else
{
	DIO_setPinValue(DIO_PINA2,DIO_HIGH);
	_delay_ms(2000);
	DIO_setPinValue(DIO_PINA2,DIO_LOW);
	wrongPass=0;
}

	

 }

}

