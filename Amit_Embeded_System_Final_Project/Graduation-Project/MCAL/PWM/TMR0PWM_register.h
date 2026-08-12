/*
 * TMR0PWM_register.h
 *
 * Created: 10/24/2025 8:35:39 PM
 *  Author: mahmo
 */ 


#ifndef TMR0PWM_REGISTER_H_
#define TMR0PWM_REGISTER_H_

#define TCCR0_REG		*((volatile u8*)0x53)
#define TCNT0_REG		*((volatile u8*)0x52)
#define TIMSK_REG		*((volatile u8*)0x59)
#define TIFR_REG		*((volatile u8*)0x58)
#define OCR0_REG		*((volatile u8*)0x5C)



#endif /* TMR0PWM_REGISTER_H_ */