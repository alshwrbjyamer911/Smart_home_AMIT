/*
 * EXT_INT.h
 *
 * Created: 2/7/2024 2:00:28 AM
 *  Author: biso2
 */ 


#ifndef EXT_INT_H_
#define EXT_INT_H_
//reg. Addr.
//INT0 ,INT1 level
#define MCUCR *(volatile u8*)0x55
#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3


//INT2 level
#define MCUCSR *(volatile u8*)0x54
#define ISC2 6

//INT0,1,2 Enable
#define  GICR *(volatile u8*)0x5B
#define INT0 6
#define INT1 7
#define INT2 5




#define EXT_LOW_LEVEL 0
#define EXT_ANY_LOGICAL 1
#define EXT_FALLING	2
#define EXT_RISING 3

void EXT0_init(u8 level);
void EXT1_init(u8 level);
void EXT2_init(u8 level);


void EXT_setCallbackInt0(void (*ptr)());
void EXT_setCallbackInt1(void (*ptr)());
void EXT_setCallbackInt2(void (*ptr)());





#endif /* EXT_INT_H_ */