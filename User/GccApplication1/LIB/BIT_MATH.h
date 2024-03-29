/*
 * BIT_MATH.h
 *
 * Created: 1/20/2024 6:16:10 PM
 *  Author: biso2
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(x,bitnumber) ((x)|=(1<<(bitnumber)))
#define CLEAR_BIT(x,bitnumber) ((x)&=~(1<<(bitnumber)))
#define TOGGLE(x,bitnumber) ((x)^=(1<<(bitnumber)))
#define GET_BIT(x,bitnumber) ((x>>bitnumber)&1)



#endif /* BIT_MATH_H_ */