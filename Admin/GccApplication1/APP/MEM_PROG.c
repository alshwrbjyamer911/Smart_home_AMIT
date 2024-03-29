/*
 * MEM_PROG.c
 *
 * Created: 3/20/2024 9:17:12 PM
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
#include "STD_TYPES.h"
#include "SPI_INT.h"
#include "UART_INT.h"
#include "I2C_INT.h"
#include "EEPROM_INT.h"
#include "MEM_INT.h"
#include "TIMER0_INT.h"
u8 charCounter=0;
u8 adminLogin()
{
	UART_sendString("Admin= ");
	u8 user[5];
	adminInput(user);
	UART_sendString("Admin Pass= ");
	u8 pass[4];
	adminInput(pass);
	if((user[0]==EEPROM_readData(0))
	 &&(user[1]==EEPROM_readData(1))
	 &&(user[2]==EEPROM_readData(2))
	 &&(user[3]==EEPROM_readData(3))
	 &&(user[4]==EEPROM_readData(4))
	 &&(pass[0]==EEPROM_readData(5))
	 &&(pass[1]==EEPROM_readData(6))
	 &&(pass[2]==EEPROM_readData(7))
	 &&(pass[3]==EEPROM_readData(8))
	 )
	 {
		 return 1;
	 }
	 else
	 {
		 return 0;
	 }

	
}

void adminInput (u8 *input)
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
u8 addOnlineUser()
{
	    u8 user[10];
		u8 pass[10];
		u8 i=0,location=0;
		u8 correct=0;
        UART_sendString("online user= ");

		adminInput(user);
		for ( i=101;i<200;i+=20)
		{
			if(EEPROM_readData(i)==255)
			{
				location=i;
				for(int l=0,j=i; l<charCounter; j++,l++)
				{
					EEPROM_writeData(user[l],j);
					_delay_ms(20);
				}
				correct++;
				break;
				
			}
		}
		UART_sendString("online user pass= ");
		adminInput(pass);
		location+=10;
		for(int l=0,j=location; l<charCounter; j++,l++)
		{
			EEPROM_writeData(pass[l],j);
			_delay_ms(20);
		}
		return correct;
		
	


}
u8 addOfflineUser()
{
	u8 user[10];
	u8 pass[10];
	u8 i=0,location=0;
	u8 correct=0;
	UART_sendString("offline user= ");

	adminInput(user);
	for ( i=11;i<100;i+=20)
	{
		if(EEPROM_readData(i)==255)
		{
			location=i;
			for(int l=0,j=i; l<charCounter; j++,l++)
			{
				EEPROM_writeData(user[l],j);
				_delay_ms(20);
			}
			correct++;
			break;
		}
	}
	UART_sendString("offline user pass= ");
	adminInput(pass);
	location+=10;
	for(int l=0,j=location; l<charCounter; j++,l++)
	{
		EEPROM_writeData(pass[l],j);
		_delay_ms(20);
	}
	return correct;
	
	


}
u8 deleteOnlineUser()
{
	u8 user[10];
	//adminInput(user);
	u8 location=0;
	u8 correct=0;
	u8 flag=0;
	UART_sendString("user You wish to delete= ");
	adminInput(user);
	for (u8 i=101;i<200;i+=20)
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
		for(u8 l=0,j=location; l<10; j++,l++)
		{
			EEPROM_writeData(255,j);
			_delay_ms(20);
			EEPROM_writeData(255,j+10);
			_delay_ms(20);
		}
		return 1;
	}
	return 0;

}
u8 deleteOfflineUser()
{
	u8 user[10];
	//adminInput(user);
	u8 location=0;
	u8 correct=0;
	u8 flag=0;
	UART_sendString("user You wish to delete= ");
	adminInput(user);
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
		for(u8 l=0,j=location; l<10; j++,l++)
		{
			EEPROM_writeData(255,j);
			_delay_ms(20);
			EEPROM_writeData(255,j+10);
			_delay_ms(20);
		}
		return 1;
	}
	return 0;

}
		    
u8 Door (u8 val)
{

		TIMER1_initFastPwmMod14();

		GI_enable();
		DIO_setPinDir(DIO_PIND5, DIO_OUTPUT);
		TIMER1_setFrequency(50);
			UART_sendString("\r");
			if(val==1)
			{
				LCD_clearDis();
				LCD_writeStr("OPEN  DOOR\r");
				
				TIMER1_setDuty(10);
				return 1;
			}
			else if(val==0)
			{
				LCD_clearDis();
				LCD_writeStr("Close  DOOR\r");
				TIMER1_setDuty(5);
				return 1;
			}
		
	return 0;


}		    
void LED_DIMMER(u8 x)
{
	
	DIO_setPinDir(DIO_PINB3,DIO_OUTPUT);
	u8 y;
	if (x==0)
	{
	TIMER0_stop();
	 }
 	else if (x>0 &&x<=5)
 	{
	TIMER0_initFastPwm();
	
	TIMER0_setFrequency(PWM_FREQUENCY_7812);
	 y=x*20;
	 TIMER0_setDuty(y);
	}
}



