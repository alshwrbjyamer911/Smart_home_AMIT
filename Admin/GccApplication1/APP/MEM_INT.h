/*
 * MEM_INT.h
 *
 * Created: 3/20/2024 9:17:32 PM
 *  Author: biso2
 */ 


#ifndef MEM_INT_H_
#define MEM_INT_H_
u8 adminLogin();
void adminInput (u8 *input);
u8 addOnlineUser();
u8 addOfflineUser();
u8 deleteOnlineUser();
u8 deleteOfflineUser();
u8 Door(u8 val);
void LED_DIMMER(u8 duty);



#endif /* MEM_INT_H_ */