/*
 * GI_INT.h
 *
 * Created: 2/7/2024 2:32:12 AM
 *  Author: biso2
 */ 


#ifndef GI_INT_H_
#define GI_INT_H_

#define SREG *(volatile u8*)0x5F
#define I 7

void GI_enable();
void GI_disable();



#endif /* GI_INT_H_ */