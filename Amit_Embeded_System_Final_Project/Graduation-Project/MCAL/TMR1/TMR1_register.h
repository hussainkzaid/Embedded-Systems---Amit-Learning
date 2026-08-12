/*
 * TMR1_register.h
 *
 * Created: 10/17/2025 9:07:53 PM
 *  Author: mahmo
 */ 


#ifndef TMR1_REGISTER_H_
#define TMR1_REGISTER_H_

#define TCCR1A_REG		*((volatile u8*)0x4F)
#define TCCR1B_REG		*((volatile u8*)0x4E)
#define TCNT1_REG		*((volatile u16*)0x4C)
#define TIMSK_REG		*((volatile u8*)0x59)
#define TIFR_REG		*((volatile u8*)0x58)


#endif /* TMR1_REGISTER_H_ */