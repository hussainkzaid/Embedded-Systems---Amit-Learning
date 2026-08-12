/*
 * SWICU_interface.h
 *
 * Created: 11/14/2025 8:29:46 PM
 *  Author: mahmo
 */ 


#ifndef SWICU_INTERFACE_H_
#define SWICU_INTERFACE_H_



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



void SWICU_voidInit(void);
void SWICU_voidStart(void);
void SWICU_voidGetData(f32* copy_f32PtrFrequency, f32* copy_f32PtrDuty);

void TMR0_ISR_Function(void);
void INT0_ISR_Function(void);

#endif /* SWICU_INTERFACE_H_ */