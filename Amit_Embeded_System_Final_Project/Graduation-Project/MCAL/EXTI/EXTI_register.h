/*
 * EXTI_register.h
 *
 * Created: 10/4/2025 7:05:45 PM
 *  Author: mahmo
 */ 


#ifndef EXTI_REGISTER_H_
#define EXTI_REGISTER_H_

// External Interrupts Registers
#define GICR_REG   *((volatile u8*)0x5b)
#define INT2				5
#define INT1				7
#define INT0				6

#define GIFR_REG   *((volatile u8*)0x5a)
#define INTF2				5
#define INTF1				7
#define INTF0				6

#define MCUCR_REG   *((volatile u8*)0x55)
#define ISC11				3
#define ISC10				2
#define ISC01				1
#define ISC00				0

#define MCUCSR_REG   *((volatile u8*)0x54)
#define ISC2				6


#endif /* EXTI_REGISTER_H_ */