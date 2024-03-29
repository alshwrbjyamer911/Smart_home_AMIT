/*
 * LCD_INT.h
 *
 * Created: 1/30/2024 6:11:20 PM
 *  Author: biso2
 */ 


#ifndef LCD_INT_H_
#define LCD_INT_H_

#define LCD_MODE 4
#define LCD_D0 DIO_PINA0
#define LCD_D1 DIO_PINA1
#define LCD_D2 DIO_PINA2
#define LCD_D3 DIO_PINA3
#define LCD_D4 DIO_PINC2
#define LCD_D5 DIO_PINC3
#define LCD_D6 DIO_PINC4
#define LCD_D7 DIO_PINC5

#define LCD_RS DIO_PINC6
#define LCD_RW DIO_PINC7
#define LCD_E DIO_PIND6

#define LCD_CLEAR_CMD	0b00000001
#define LCD_ENTRY_MODE_CMD 0b00000110

void LCD_init();
void LCD_clearDis();
void LCD_writeChar(u8 data);
void LCD_writeStr(u8* str);
void LCD_createNewChar(u8* arr, u8 CharLocation);
void LCD_writeNewChar(u8 location);
void LCD_writeCmd(u8 data);

void LCD_ShiftDis(u8* str);
void LCD_goto(u8 x,u8 y);
void LCD_writeNum(s32 data);
void LCD_writeNumFloat(f32 num);









#endif /* LCD_INT_H_ */