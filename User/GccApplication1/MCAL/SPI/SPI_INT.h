/*
 * SPI_INT.h
 *
 * Created: 3/1/2024 9:34:11 PM
 *  Author: biso2
 */ 


#ifndef SPI_INT_H_
#define SPI_INT_H_
#define SPCR *(volatile u8*)0x2D
#define SPDR *(volatile u8*)0x2F
#define SPSR *(volatile u8*)0x2E
#define SPE 6
#define MSTR 4
#define SPIF 7




void SPI_Init();
u8 SPI_Read();
void SPI_Write(u8 data);



#endif /* SPI_INT_H_ */