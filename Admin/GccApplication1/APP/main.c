/*
 * GccApplication2.c
 *
 * Created: 3/1/2024 10:27:52 PM
 * Author : biso2
 */ 

#include "BIT_MATH.h"
# define F_CPU 16000000
#include <util/delay.h>
#include <string.h>
#include "DIO_INT.h"
#include "STD_TYPES.h"
#include "SPI_INT.h"
#include "UART_INT.h"
#include "I2C_INT.h"
#include "EEPROM_INT.h"
#include "MEM_INT.h"
#include "EXT_INT.h"
#include "GI_INT.h"
#include "LCD_INT.h"

int main(void)
{
	
	//DIO_setPinDir(DIO_PIND2,DIO_INPUT);
	DIO_setPinDir(DIO_PINB0,DIO_OUTPUT);
	DIO_setPinDir(DIO_PINA0,DIO_OUTPUT);
	DIO_setPinDir(DIO_PINA1,DIO_OUTPUT);
	DIO_setPinDir(DIO_PINA2,DIO_OUTPUT);
	DIO_setPinDir(DIO_PINA3,DIO_OUTPUT);
	DIO_setPinDir(DIO_PINA4,DIO_OUTPUT);


	SPI_Init();
	UART_init();
	I2C_init(MASTER);
	GI_enable();
	EXT0_init(EXT_RISING);
	
	
	u8 adminuser[5]="admin";
	u8 adminpassword[4]="1234";
	DIO_setPinDir(DIO_PIND3,DIO_OUTPUT);
	//saving admin username
	for(int b=0; b<5; b++)
	{
		EEPROM_writeData(adminuser[b],b);
		_delay_ms(20);

	}
	for(int b=0,j=5; b<4; b++,j++)
	{
		EEPROM_writeData(adminpassword[b],j);
		_delay_ms(20);

	}
    u8 wrongPass=0;

// for (int i=11;i<201;i++)
// {
// 	UART_sendData(EEPROM_readData(i));
// 	//EEPROM_writeData(255,i);
// 	//_delay_ms(30);
// 
// }
u8 userchoice[10];
u8 flag1;
u8 back=0;
while (1)
{
	if (wrongPass!=3)
	{	
		if(adminLogin())
		{
			wrongPass=0;
			UART_sendString("Welcome Home.\r ");
			flag1=1;
		while (flag1)
		{
				UART_sendString(" press a to add an online user\r press b to add an offline user\r press c to delete online user\r press d to delete offline user\r press e to Control devices\r press s to sign out\r");
				adminInput(userchoice);
				if ((!(strcmp(userchoice,"a"))))
					{
						if (addOnlineUser())
						{
							UART_sendString("User added successfully \r");
						}
						else
						{
							UART_sendString("Error\r ");
						}	
					}
				else if ((!(strcmp(userchoice,"b"))))
					{	
						if (addOfflineUser())
						{
							UART_sendString("User added successfully\r ");
						}
						else
						{
							UART_sendString("Error\r ");
						}
					}
				else if ((!(strcmp(userchoice,"c"))))
					{
						if (deleteOnlineUser())
						{
							UART_sendString("User deleted successfully \r");
						}
						else
						{
							UART_sendString("Error \r");
							
						}
					}
				else if ((!(strcmp(userchoice,"d"))))
				{
					if (deleteOfflineUser())
					{
						UART_sendString("User deleted successfully \r");
					}
					else
					{
						UART_sendString("Error \r");
						
					}
				}

				else if((!(strcmp(userchoice,"e"))))
					{
						LCD_init();
						back=1;
						while (back==1)
						{
							UART_sendString("Write the number of the led then on or off to control it\rPress a number between 1 and 5 to control the dimming\rWrite off to turn dimmer off\r Write open or close to control the door\r Press b to go back\r");
							adminInput(userchoice);
							if ((!(strcmp(userchoice,"off"))))
							{
								LED_DIMMER(0);
								LCD_goto(10,2);
								LCD_writeStr("      ");
								
							}
							else if ((!(strcmp(userchoice,"1"))))
							{
								LED_DIMMER(1);
								LCD_goto(10,2);
								LCD_writeStr("Dim L1");
								
							}
							else if ((!(strcmp(userchoice,"2"))))
							{
								LED_DIMMER(2);
								LCD_goto(10,2);
								LCD_writeStr("Dim L2");
							}
							else if ((!(strcmp(userchoice,"3"))))
							{
								LED_DIMMER(3);
								LCD_goto(10,2);
								LCD_writeStr("Dim L3");
							}
							else if ((!(strcmp(userchoice,"4"))))
							{
								LED_DIMMER(4);
								LCD_goto(10,2);
								LCD_writeStr("Dim L4");
							}
							else if ((!(strcmp(userchoice,"5"))))
							{
								LED_DIMMER(5);
								LCD_goto(10,2);
								LCD_writeStr("Dim L5");
							}
							else if ((!(strcmp(userchoice,"1 on"))))
							{
								DIO_setPinValue(DIO_PINA0,DIO_HIGH);
								LCD_goto(0,2);
								LCD_writeStr("L1");
							}
							else if ((!(strcmp(userchoice,"2 on"))))
							{
								DIO_setPinValue(DIO_PINA1,DIO_HIGH);
								LCD_goto(2,2);
								LCD_writeStr("L2");
							}
							else if ((!(strcmp(userchoice,"3 on"))))
							{
								DIO_setPinValue(DIO_PINA2,DIO_HIGH);
								LCD_goto(4,2);
								LCD_writeStr("L3");
							}
							else if ((!(strcmp(userchoice,"4 on"))))
							{
								DIO_setPinValue(DIO_PINA3,DIO_HIGH);
								LCD_goto(6,2);
								LCD_writeStr("L4");
							}
							else if ((!(strcmp(userchoice,"5 on"))))
							{
								DIO_setPinValue(DIO_PINA4,DIO_HIGH);
								LCD_goto(8,2);
								LCD_writeStr("L5");
							}
							else if ((!(strcmp(userchoice,"1 off"))))
							{
								DIO_setPinValue(DIO_PINA0,DIO_LOW);
								LCD_goto(0,2);
								LCD_writeStr("  ");
							}
							else if ((!(strcmp(userchoice,"2 off"))))
							{
								DIO_setPinValue(DIO_PINA1,DIO_LOW);
								LCD_goto(2,2);
								LCD_writeStr("  ");
							}
							else if ((!(strcmp(userchoice,"3 off"))))
							{
								DIO_setPinValue(DIO_PINA2,DIO_LOW);
								LCD_goto(4,2);
								LCD_writeStr("  ");
							}
							else if ((!(strcmp(userchoice,"4 off"))))
							{
								DIO_setPinValue(DIO_PINA3,DIO_LOW);
								LCD_goto(6,2);
								LCD_writeStr("  ");
							}
							else if ((!(strcmp(userchoice,"5 off"))))
							{
								DIO_setPinValue(DIO_PINA4,DIO_LOW);
								LCD_goto(8,2);
								LCD_writeStr("  ");
							}
							else if ((!(strcmp(userchoice,"open"))))
							{
								Door(0);
							}
							else if ((!(strcmp(userchoice,"close"))))
							{
								Door(1);
							}
							else if ((!(strcmp(userchoice,"b"))))
							{
								back=0;
							}
						}
					}
				else if ((!(strcmp(userchoice,"s"))))
					{
						flag1=0;
					//UART_sendString("wrong input\r ");
					}
				else
					{
						UART_sendString("wrong input\r ");
					}
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
