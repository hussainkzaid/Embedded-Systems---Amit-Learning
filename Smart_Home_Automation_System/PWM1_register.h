/*
 * PWM1_register.h
 *
 * Created: 11/16/2025 9:42:14 PM
 *  Author: hussain zaid
 */ 


#ifndef PWM1_REGISTER_H_
#define PWM1_REGISTER_H_

//Timer/Counter1 Control Register A
#define TCCR1A_REG				(*(volatile u8*)0x4F)
#define COM1A1        7
#define COM1A0		  6
#define COM1B1 		  5
#define COM1B0 		  4
#define FOC1A 		  3
#define FOC1B 		  2
#define WGM11 		  1
#define WGM10		  0


//Timer/Counter1 Control Register B
#define TCCR1B_REG				(*(volatile u8*)0x4E)
#define ICNC1         7
#define ICES1		  6
#define WGM13		  4
#define WGM12		  3
#define CS12 		  2
#define CS11 		  1
#define CS10		  0

//TCNT1H and TCNT1L – Timer/Counter1
#define TCNT1_U16				(*(volatile u16*)0x4C)


//OCR1AH and OCR1AL – Output Compare Register 1 A
#define OCR1A_U16				(*(volatile u16*)0x4A)


// OCR1BH and OCR1BL – Output Compare Register 1 B
#define OCR1B_U16				(*(volatile u16*)0x48)


//ICR1H and ICR1L – Input Capture Register 1
#define ICR1_U16				(*(volatile u16*)0x46)


// Timer/Counter Interrupt Mask Register
#define TIMSK_REG				(*(volatile u8*)0x59)
#define TICIE1					5
#define OCIE1A					4
#define OCIE1B					3
#define TOIE1					2


//Timer/Counter Interrupt Flag Register
#define TIFR_REG				(*(volatile u8*)0x58)
#define ICF1					5
#define OCF1A				    4
#define OCF1B					3
#define TOV1					2

#endif /* PWM1_REGISTER_H_ */