/*
 * SS_INT.h
 *
 * Created: 1/27/2024 7:23:47 PM
 *  Author: biso2
 */ 


#ifndef SS_INT_H_
#define SS_INT_H_

#define SS_E1 DIO_PINB2
#define SS_E2 DIO_PINB1

#define SS_S0 DIO_PINA4
#define SS_S1 DIO_PINA5
#define SS_S2 DIO_PINA6
#define SS_S3 DIO_PINA7
#define SS_PORT PORTA
void SS_init();

void SS_setEnable1();
void SS_setEnable2();

void SS_setdisable1();
void SS_setdisable2();

void SS_writeNumber(u8 num);



#endif /* SS_INT_H_ */