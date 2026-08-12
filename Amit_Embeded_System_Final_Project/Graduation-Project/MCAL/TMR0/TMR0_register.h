/*
 * TMR0_register.h
 *
 * Created: 10/17/2025 9:07:53 PM
 *  Author: mahmo
 */ 


#ifndef TMR0_REGISTER_H_
#define TMR0_REGISTER_H_

#define TCCR0_REG		*((volatile u8*)0x53)
#define TCNT0_REG		*((volatile u8*)0x52)
#define TIMSK_REG		*((volatile u8*)0x59)
#define TIFR_REG		*((volatile u8*)0x58)
#define OCR0_REG		*((volatile u8*)0x5C)

#endif /* TMR0_REGISTER_H_ */