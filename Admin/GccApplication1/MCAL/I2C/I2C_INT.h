/*
 * I2C_INT.h
 *
 * Created: 3/6/2024 3:35:43 PM
 *  Author: biso2
 */ 


#ifndef I2C_INT_H_
#define I2C_INT_H_
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#define I2C_SLAVE_ADDRESS	0x50



/*I2c Registers*/
#define TWBR            *((volatile u8*)(0x20))

#define TWCR            *((volatile u8*)(0x56))
#define TWINT     7
#define TWEA      6
#define TWSTA     5
#define TWSTO     4
#define TWWC      3
#define TWEN      2
#define TWIE      0

#define TWSR            *((volatile u8*)(0x21))
#define TWPS0  0
#define TWPS1  1
#define TWS3   3
#define TWS4   4
#define TWS5   5
#define TWS6   6
#define TWS7   7

#define TWDR            *((volatile u8*)(0x23))
#define TWD0   0

#define TWAR             *((volatile u8*)(0x22))
#define TWGCE

enum I2C_mode
{
	SLAVE = 0,
	MASTER = 1
};

void I2C_init(enum I2C_mode mode);

void I2C_sendByte(u8 byte, u8 address);

void I2C_receiveByteACK(u8* byte, u8 address);

void I2C_receiveByteNACK(u8* byte, u8 address);



#endif /* I2C_INT_H_ */