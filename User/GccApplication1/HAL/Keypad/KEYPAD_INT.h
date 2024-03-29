/*
 * KEYPAD_INT.h
 *
 * Created: 2/5/2024 2:45:26 PM
 *  Author: biso2
 */ 


#ifndef KEYPAD_INT_H_
#define KEYPAD_INT_H_

#include "STD_TYPES.h"

#include "DIO_INT.h"



//macros
#define KEYPAD_ROW0  DIO_PINC2
#define KEYPAD_ROW1  DIO_PINC3
#define KEYPAD_ROW2  DIO_PINC4
#define KEYPAD_ROW3  DIO_PINC5

#define KEYPAD_COL0  DIO_PINC6
#define KEYPAD_COL1  DIO_PINC7
#define KEYPAD_COL2  DIO_PIND5
#define KEYPAD_COL3  DIO_PINA3



#define KEYPAD_ROW0_COL0 '7'
#define KEYPAD_ROW0_COL1 '8'
#define KEYPAD_ROW0_COL2 '9'
#define KEYPAD_ROW0_COL3 '/'

#define KEYPAD_ROW1_COL0 '4'
#define KEYPAD_ROW1_COL1 '5'
#define KEYPAD_ROW1_COL2 '6'
#define KEYPAD_ROW1_COL3 '*'

#define KEYPAD_ROW2_COL0 '1'
#define KEYPAD_ROW2_COL1 '2'
#define KEYPAD_ROW2_COL2 '3'
#define KEYPAD_ROW2_COL3 '-'

#define KEYPAD_ROW3_COL0 'c'
#define KEYPAD_ROW3_COL1 '0'
#define KEYPAD_ROW3_COL2 '='
#define KEYPAD_ROW3_COL3 '+'


#define KEYPAD_UNPRESSED 'x'

//#define KEYPAD_ARRAY {{'1','2','3','+'},{'4','5','6','*'},{},{}}

void KEYPAD_init();

u8 KEYPAD_read();


#endif /* KEYPAD_INT_H_ */