/*
 * TMR1PWM_interface.h
 *
 * Created: 11/1/2025 7:30:46 PM
 *  Author: mahmo
 */ 


#ifndef TMR1PWM_INTERFACE_H_
#define TMR1PWM_INTERFACE_H_

#include "STD_TYPES.h"

typedef enum
{
	NO_CLK_SRC,							// 0 0 0
	NO_PRESCALING,						// 0 0 1
	_8FROM_PRESCALER,					// 0 1 0
	_64FROM_PRESCALER,					// 0 1 1
	_256FROM_PRESCALER,					// 1 0 0
	_1024FROM_PRESCALER,				// 1 0 1
} TMR1PWM_prescaler_t;

void TMR1PWM_voidInit(void);
void TMR1PWM_voidGenerate(u32 copy_u32Frequency, f32 copy_u8DutyRatio, u8 copy_u8prescaler);
void TMR1PWM_voidStop();


#endif /* TMR1PWM_INTERFACE_H_ */