/*
 * EEPROM_INT.h
 *
 * Created: 3/8/2024 7:09:19 PM
 *  Author: biso2
 */ 


#ifndef EEPROM_INT_H_
#define EEPROM_INT_H_
void EEPROM_writeData(u8 data, u16 location);
u8 EEPROM_readData(u16 location);




#endif /* EEPROM_INT_H_ */