/*
 * SPI_PROG.c
 *
 * Created: 3/1/2024 9:33:38 PM
 *  Author: biso2
 */ 
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXT_INT.h"
#include "DIO_INT.h"
#include "SPI_INT.h"
void SPI_Init()
{
	SET_BIT(SPCR,MSTR);
	DIO_setPinDir(DIO_PINB5,DIO_OUTPUT);
	DIO_setPinDir(DIO_PINB7,DIO_OUTPUT);
	DIO_setPinDir(DIO_PINB6,DIO_INPUT);
	DIO_setPinDir(DIO_PINB4,DIO_OUTPUT);

	

	SET_BIT(SPCR,SPE);

	
}
u8 SPI_Read()
{
	while(GET_BIT(SPSR,SPIF)==0);
	return SPDR;
}
void SPI_Write(u8 data)
{
	DIO_setPinValue(DIO_PINB4,DIO_HIGH);
	DIO_setPinValue(DIO_PINB4,DIO_LOW);
	SPDR=data;
	while(GET_BIT(SPSR,SPIF)==0);
}