/*
 * MEM_PROG.c
 *
 * Created: 3/21/2024 10:43:59 PM
 *  Author: biso2
 */ 
#include "GI_INT.h"
//#include "TIMER0_INT.h"
#include "TIMER1_INT.h"
#include "LCD_INT.h"
#include "BIT_MATH.h"
# define F_CPU 16000000
#include <util/delay.h>
#include "DIO_INT.h"
#include "KEYPAD_INT.h"
#include "STD_TYPES.h"
#include "SPI_INT.h"
#include "UART_INT.h"
#include "I2C_INT.h"
#include "EEPROM_INT.h"
#include "MEM_INT.h"
#include "ADC_INT.h"
u8 charCounter=0;
void userkeypadInput (u8 *input)
{
	u8 key=0,i=0;
	charCounter=0;
	while (key!='=')
	{
		key = KEYPAD_read();
		if(key != KEYPAD_UNPRESSED && key!='=')
		{
			while(KEYPAD_read() != KEYPAD_UNPRESSED);
			LCD_writeChar(key);
			input[i]=key;
			charCounter++;
			i++;
		}
	}
	input[charCounter]='\0';
}
void userInput (u8 *input)
{
	u8 c=0,i=0;
	charCounter=0;
	while (c!=0x3d)
	{
		c=UART_receiveData();
		if (c!=0x3d)
		{
			input[i]=c;
			charCounter++;
			i++;
		}
	}
	input[charCounter]='\0';
	UART_sendData(13);
	UART_sendData(10);
}
u8 userkeypadCheck()
{
	u8 user[10];
	u8 pass[10];
	u8 flag=0;
	LCD_writeStr("user=");
	userkeypadInput(user);
	u8 correct=0, location=0;
	for (u8 i=11;i<100;i+=20)
	{
		if(EEPROM_readData(i)!=255)
		{
			for(u8 l=0,j=i; l<charCounter; j++,l++)
			{
				if (user[l]==EEPROM_readData(j))
				{
					correct++;
					if (correct==charCounter)
					{
						location=i;
						_delay_ms(300);
						flag=1;
						break;
					}
				}
				else
				{
					
					correct=0;
				}
			}
		}
		if(flag==1){break;}
	}
	if (location!=0)
	{
		LCD_goto(0,2);
		LCD_writeStr("password=");
		userkeypadInput(pass);
		location+=10;
		correct=0;
		for(u8 l=0,j=location; l<charCounter; j++,l++)
		{
			if (pass[l]==EEPROM_readData(j))
			{
				correct++;
				if (correct==charCounter)
				{
					_delay_ms(300);
					return 1;
				}
			}
			else{correct=0;}
		}
	}
	return 0;
}
u8 userCheck()
{
		u8 user[10];
		u8 pass[10];
		UART_sendString("user=");
		userInput(user);
		u8 correct;
		correct=0;
		u8 location;
		location=0;
		    for (u8 i=101;i<200;i+=20)
		    {
			    if(EEPROM_readData(i)!=255)
			    {
				    for(u8 l=0,j=i; l<10; j++,l++)
				    {
					    if (user[l]==EEPROM_readData(j))
					    {
						    correct++;
						    if (correct==charCounter)
						    {
							    location=i;
							    break;
						    }
					    }
					    else
					    {
						    correct=0;
					    }
				    }
			    }
		    }
		if (location!=0)
		{
			UART_sendString("password=");
			userInput(pass);
			location+=10;
			correct=0;
			for(u8 l=0,j=location; l<10; j++,l++)
			{
				if (pass[l]==EEPROM_readData(j))
				{
					correct++;
					if (correct==charCounter)
					{
						return 1;
					}
				}
			}
		}
			return 0;
}

void ext_fun()
{
	DIO_setPinDir(DIO_PINA2,DIO_OUTPUT);
	u8 incorrect,flag=1,flag1=1;
	while (flag==1)
	{
		u8 userchoice[10];
		incorrect=0;
		if (incorrect!=3)
		{
			if (userkeypadCheck())
			{
				incorrect=0;
				LCD_clearDis();
				LCD_writeStr("Welcome");
				_delay_ms(500);
				LCD_clearDis();
				
				while(flag1==1)
				{
					//LCD_writeStr("p f 1to6 to led contro");
					userkeypadInput(userchoice);
					if((!(strcmp(userchoice,"1-1"))))
					{
						SPI_Write('g');
						LCD_clearDis();
						
					}
					else if((!(strcmp(userchoice,"2-1"))))
					{
						SPI_Write('h');
						LCD_clearDis();
					}
					else if((!(strcmp(userchoice,"3-1"))))
					{
						SPI_Write('i');
						LCD_clearDis();
					}
					else if((!(strcmp(userchoice,"4-1"))))
					{
						SPI_Write('j');
						LCD_clearDis();
					}
					else if((!(strcmp(userchoice,"5-1"))))
					{
						SPI_Write('k');
						LCD_clearDis();
					}
					else if((!(strcmp(userchoice,"1-0"))))
					{
						SPI_Write('l');
						LCD_clearDis();
					}
					else if((!(strcmp(userchoice,"2-0"))))
					{
						SPI_Write('m');
						LCD_clearDis();
					}
					else if((!(strcmp(userchoice,"3-0"))))
					{
						SPI_Write('n');
						LCD_clearDis();
					}
					else if((!(strcmp(userchoice,"4-0"))))
					{
						SPI_Write('o');
						LCD_clearDis();
					}
					else if((!(strcmp(userchoice,"5-0"))))
					{
						SPI_Write('p');
						LCD_clearDis();
					}
					
					else if((!(strcmp(userchoice,"6-0"))))
					{
						SPI_Write('a');
						LCD_clearDis();
					}
					else if((!(strcmp(userchoice,"6-1"))))
					{
						SPI_Write('b');
						LCD_clearDis();
					}
					else if((!(strcmp(userchoice,"6-3"))))
					{
						SPI_Write('d');
						LCD_clearDis();
					}
					else if((!(strcmp(userchoice,"6-4"))))
					{
						SPI_Write('e');
						LCD_clearDis();
					}
					else if((!(strcmp(userchoice,"6-5"))))
					{
						SPI_Write('f');
						LCD_clearDis();
					}
					else if((!(strcmp(userchoice,"6-2"))))
					{
						SPI_Write('c');
						LCD_clearDis();
					}
					else if((!(strcmp(userchoice,"0"))))
					{
						flag=0;
						flag1=0;
						LCD_clearDis();
					}
				}


			}
			else if(!userkeypadCheck())
			{
				LCD_clearDis();
				LCD_writeStr("error");
				incorrect++;
			}
		}
		else
		{
			DIO_setPinValue(DIO_PINA2,DIO_HIGH);
			_delay_ms(2000);
			DIO_setPinValue(DIO_PINA2,DIO_LOW);
			incorrect=0;
		}
	}
}