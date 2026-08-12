/*
 * SWICU_register.h
 *
 * Created: 11/14/2025 8:40:17 PM
 *  Author: mahmo
 */ 


#ifndef SWICU_REGISTER_H_
#define SWICU_REGISTER_H_

// timer0
#define TCCR0_REG		*((volatile u8*)0x53)
#define TCNT0_REG		*((volatile u8*)0x52)
#define TIMSK_REG		*((volatile u8*)0x59)
#define TIFR_REG		*((volatile u8*)0x58)
#define OCR0_REG		*((volatile u8*)0x5C)



#endif /* SWICU_REGISTER_H_ */