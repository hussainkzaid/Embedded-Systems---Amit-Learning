/*
 * TMR1PWM_register.h
 *
 * Created: 11/1/2025 7:32:28 PM
 *  Author: mahmo
 */ 


#ifndef TMR1PWM_REGISTER_H_
#define TMR1PWM_REGISTER_H_


#define TCCR1A_REG		*((volatile u8*)0x4F)
#define TCCR1B_REG		*((volatile u8*)0x4E)
#define TCNT1_REG		*((volatile u16*)0x4C)
#define TIMSK_REG		*((volatile u8*)0x59)
#define TIFR_REG		*((volatile u8*)0x58)

#define ICR1_REG		*((volatile u16*)0x46)
#define OCR1A_REG		*((volatile u16*)0x4A)


#endif /* TMR1PWM_REGISTER_H_ */