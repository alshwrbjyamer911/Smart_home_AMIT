/*
 * WDT_INIT.h
 *
 * Created: 2/23/2024 9:39:21 PM
 *  Author: biso2
 */ 


#ifndef WDT_INIT_H_
#define WDT_INIT_H_
#define WDTOE 4
#define WDE 3
#define WDP2 2
#define WDP1 1
#define WDP0 0

#define WDT_Time0 0
#define WDT_Time1 1
#define WDT_Time2 2
#define WDT_Time3 3
#define WDT_Time4 4
#define WDT_Time5 5
#define WDT_Time6 6
#define WDT_Time7 7

#define WDTCR *(volatile u8*)0x41


void WDT_start(u8 time);
void WDT_stop();
#endif /* WDT_INIT_H_ */