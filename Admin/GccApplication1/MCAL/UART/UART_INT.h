/*
 * UART_INT.h
 *
 * Created: 2/24/2024 8:16:13 PM
 *  Author: biso2
 */ 


#ifndef UART_INT_H_
#define UART_INT_H_
#define UART_NOT_RECEIVED 'x'
void UART_init();
void UART_sendData(u8 data);
void UART_sendString(u8* str);

u8 UART_receiveData();

 

#endif /* UART_INT_H_ */