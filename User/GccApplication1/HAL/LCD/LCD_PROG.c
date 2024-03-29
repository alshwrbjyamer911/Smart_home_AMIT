/*
 * LCD_PROG.c
 *
 * Created: 1/30/2024 6:11:55 PM
 *  Author: biso2
 */ 
#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "DIO_INT.h"

#include "LCD_INT.h"

#define F_CPU 16000000
#include <util/delay.h>

void LCD_init()
{
	#if LCD_MODE  == 4
		DIO_setPinDir(LCD_D4, DIO_OUTPUT);
		DIO_setPinDir(LCD_D5, DIO_OUTPUT);
		DIO_setPinDir(LCD_D6, DIO_OUTPUT);
		DIO_setPinDir(LCD_D7, DIO_OUTPUT);
	
		DIO_setPinDir(LCD_RS, DIO_OUTPUT);
		DIO_setPinDir(LCD_RW, DIO_OUTPUT);
		DIO_setPinDir(LCD_E, DIO_OUTPUT);
	
		//for 4 bit
		LCD_writeCmd(0b00000010);
		_delay_ms(50);
		//function set
		LCD_writeCmd(0b00101000);
		_delay_ms(1);
		//Display on/off
		LCD_writeCmd(0b00001110);
		_delay_ms(1);
		//clear
		LCD_writeCmd(0b00000001);
		_delay_ms(5);
		//Entry mode set
		LCD_writeCmd(0b00000110);
	#elif LCD_MODE == 8
	
		DIO_setPinDir(LCD_D0, DIO_OUTPUT);
		DIO_setPinDir(LCD_D1, DIO_OUTPUT);
		DIO_setPinDir(LCD_D2, DIO_OUTPUT);
		DIO_setPinDir(LCD_D3, DIO_OUTPUT);
		DIO_setPinDir(LCD_D4, DIO_OUTPUT);
		DIO_setPinDir(LCD_D5, DIO_OUTPUT);
		DIO_setPinDir(LCD_D6, DIO_OUTPUT);
		DIO_setPinDir(LCD_D7, DIO_OUTPUT);
	
		DIO_setPinDir(LCD_RS, DIO_OUTPUT);
		DIO_setPinDir(LCD_RW, DIO_OUTPUT);
		DIO_setPinDir(LCD_E, DIO_OUTPUT);
	
		_delay_ms(50);
	
		//function set
		LCD_writeCmd(0b00111000);
		_delay_ms(1);
		//Display on/off
		LCD_writeCmd(0b00001110);
		_delay_ms(1);
		//clear
		LCD_writeCmd(0b00000001);
		_delay_ms(5);
		//Entry mode set
		LCD_writeCmd(0b00000110);
	#endif
}


static void LCD_sendData(u8 data)
{
	#if LCD_MODE  == 4
	DIO_setPinValue(LCD_D4, GET_BIT(data,4));
	DIO_setPinValue(LCD_D5, GET_BIT(data,5));
	DIO_setPinValue(LCD_D6, GET_BIT(data,6));
	DIO_setPinValue(LCD_D7, GET_BIT(data,7));
	DIO_setPinValue(LCD_E, DIO_HIGH);
	_delay_ms(1);
	DIO_setPinValue(LCD_E, DIO_LOW);
	
	DIO_setPinValue(LCD_D4, GET_BIT(data,0));
	DIO_setPinValue(LCD_D5, GET_BIT(data,1));
	DIO_setPinValue(LCD_D6, GET_BIT(data,2));
	DIO_setPinValue(LCD_D7, GET_BIT(data,3));
	DIO_setPinValue(LCD_E, DIO_HIGH);
	_delay_ms(1);
	DIO_setPinValue(LCD_E, DIO_LOW);
	
	#elif LCD_MODE == 8
	DIO_setPinValue(LCD_D0, GET_BIT(data,0));
	DIO_setPinValue(LCD_D1, GET_BIT(data,1));
	DIO_setPinValue(LCD_D2, GET_BIT(data,2));
	DIO_setPinValue(LCD_D3, GET_BIT(data,3));
	DIO_setPinValue(LCD_D4, GET_BIT(data,4));
	DIO_setPinValue(LCD_D5, GET_BIT(data,5));
	DIO_setPinValue(LCD_D6, GET_BIT(data,6));
	DIO_setPinValue(LCD_D7, GET_BIT(data,7));
	
	DIO_setPinValue(LCD_E, DIO_HIGH);
	_delay_ms(1);
	DIO_setPinValue(LCD_E, DIO_LOW);
	#endif
}

void LCD_writeChar(u8 data)
{
	DIO_setPinValue(LCD_RW, DIO_LOW);
	DIO_setPinValue(LCD_RS, DIO_HIGH);
	LCD_sendData(data);
}

void LCD_writeCmd(u8 data)
{
	DIO_setPinValue(LCD_RW, DIO_LOW);
	DIO_setPinValue(LCD_RS, DIO_LOW);
	LCD_sendData(data);
}

void LCD_writeStr( u8* str )
{
	u8 i=0;
	while(str[i] != '\0')
	{
		LCD_writeChar(str[i]);
		i++;
	}
}

void LCD_writeNum(s32 num)
{
	if(num < 0)
	{
		LCD_writeChar('-');
		num = num * -1;
	}
	
	u32 i =0;
	u8 arr[16];
	if(num==0)
	{
		LCD_writeChar('0');

	}
	while(num != 0)
	{
		arr[i] = (num%10) + 48;
		i++;
		num = num/10;
	}
	s32 k;
	for(k=i-1; k>=0; k--)
	{
		LCD_writeChar(arr[k]);
	}
}

void LCD_clearDis()
{
	LCD_writeCmd(0b00000001);
	_delay_ms(1);
}

void LCD_goto(u8 x, u8 y)
{
	if(y==1)
	{
	//line 1
	LCD_writeCmd(0b10000000+x);
	}
	else if(y==2)
	{
	//line 2
	LCD_writeCmd(0b10000000+0x40+x);
	}
}

void LCD_createNewChar(u8* Arr, u8 CharLocation)
{
	//<8 as you can not store more than 8 new char
	if(CharLocation<8)
	{
		//0x40 from the datasheet
		//*8 as each char take 8 bytes(from datasheet)
		LCD_writeCmd(0x40 + (CharLocation*8));

		for(u8 i=0; i<8; i++)
		{
			LCD_writeChar(Arr[i]);
		}
		LCD_goto(0,1);//must set location to any place after make a custom character
	}
	
}

void LCD_writeNewChar(u8 CharLocation)
{
	
		LCD_writeChar(CharLocation);

}

void LCD_shiftDis(u8* str)
{

}
void LCD_writeNumFloat(f32 num)
{
	s32 x=num*100.0;
	if(x < 0)
	{
		LCD_writeChar('-');
		x = x * -1;
	}
	
	u32 i =0;
	u8 arr[16];
	while(x != 0)
	{
		arr[i] = (x%10) + 48;
		i++;
		x = x/10;
	}
	s32 k;
	for(k=i-1; k>=0; k--)
	{
		if (k==1)
		{
			LCD_writeChar('.');
		}
		LCD_writeChar(arr[k]);
	}
}