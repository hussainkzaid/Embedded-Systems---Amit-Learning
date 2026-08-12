/*
 * TMR0PWM_interface.h
 *
 * Created: 10/24/2025 7:58:29 PM
 *  Author: mahmo
 */ 


#ifndef TMR0PWM_INTERFACE_H_
#define TMR0PWM_INTERFACE_H_


typedef enum
{
	NO_CLK_SRC,							// 0 0 0
	NO_PRESCALING,						// 0 0 1
	_8FROM_PRESCALER,					// 0 1 0
	_64FROM_PRESCALER,					// 0 1 1
	_256FROM_PRESCALER,					// 1 0 0
	_1024FROM_PRESCALER,				// 1 0 1
} TMR0PWM_prescaler_t;

void TMR0PWM_voidInit(void);
void TMR0PWM_voidGenerate(u8 copy_u8DutyRatio,u8 copy_u8prescaler);
void TMR0PWM_voidStop();


#endif /* TMR0PWM_INTERFACE_H_ */