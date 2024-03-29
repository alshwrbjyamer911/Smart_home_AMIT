/*
 * MOTOR_INIT.h
 *
 * Created: 2/23/2024 7:44:56 PM
 *  Author: biso2
 */ 


#ifndef MOTOR_INIT_H_
#define MOTOR_INIT_H_

#define MOTOR_RIGHT 0
#define MOTOR_LEFT 1
static void MOTOR_setDir(u8 dir);

static void MOTOR_setSpeed(u8 duty);

void MOTOR_start(u8 duty,u8 dir);



#endif /* MOTOR_INIT_H_ */