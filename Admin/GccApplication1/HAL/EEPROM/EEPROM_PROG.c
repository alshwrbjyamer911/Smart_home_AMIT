/*
 * EEPROM_PROG.c
 *
 * Created: 3/8/2024 7:08:44 PM
 *  Author: biso2
 */ 
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "I2C_INT.h"
#include "EEPROM_INT.h"
void EEPROM_writeData(u8 data, u16 location)
{
	//send start
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while( GET_BIT(TWCR,TWINT) ==0 );
	
	//address(1010)_3bitLocation_w
	u16 x = location & (0b11100000000);
	u8 y = x>>7;
	u8 result  = y | 0b10100000;
	TWDR = result;
	
	TWCR = (1<<TWINT) | (1<<TWEN);
	while( GET_BIT(TWCR,TWINT) ==0 );
	
	//8bitLocation
	TWDR = (u8)location;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while( GET_BIT(TWCR,TWINT) ==0 );
	
	//send data
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while( GET_BIT(TWCR,TWINT) ==0 );
	
	//send stop
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}
u8 EEPROM_readData(u16 location)
{
	/////dummy write/////
	//send start
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while( GET_BIT(TWCR,TWINT) ==0 );
	
	//address(1010)_3bitLocation_w
	u16 x = location & (0b11100000000);
	u8 y = x>>7;
	u8 result  = y | 0b10100000;
	TWDR = result;
	
	TWCR = (1<<TWINT) | (1<<TWEN);
	while( GET_BIT(TWCR,TWINT) ==0 );
	
	//8bitLocation
	TWDR = (u8)location;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while( GET_BIT(TWCR,TWINT) ==0 );
	
	//send start
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while( GET_BIT(TWCR,TWINT) ==0 );
	
	//address(1010_3bitLocation_r
	x = location & (0b11100000000);
	y = x>>7;
	result  = y | 0b10100001;
	TWDR = result;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while( GET_BIT(TWCR,TWINT) ==0 );
	
	//read data -> NACK
	TWCR = (1<<TWINT) | (1<<TWEN);
	while( GET_BIT(TWCR,TWINT) ==0 );
	u8 data = TWDR;
	
	//send stop
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	
	return data;

}