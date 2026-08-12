/*
 * TMR_interface.h
 *
 * Created: 10/17/2025 9:03:04 PM
 *  Author: mahmo
 */ 


#ifndef TMR0_INTERFACE_H_
#define TMR0_INTERFACE_H_


// enum values for prescaler
typedef enum
{
	NO_CLK_SRC,							// 0 0 0
	NO_PRESCALING,						// 0 0 1
	_8FROM_PRESCALER,					// 0 1 0
	_64FROM_PRESCALER,					// 0 1 1
	_256FROM_PRESCALER,					// 1 0 0 
	_1024FROM_PRESCALER,				// 1 0 1
} TMR0_prescaler_t;

void TMR0_voidInit(u8 copy_u8preloadValue);
void TMR0_voidStart(u8 copy_u8prescaler);
void TMR0_voidSetCallbackTMR0(void(*pToFunctionToCB)(void));
void TMR0_voidSetDelay_msUsingCTC(u16 copy_u16Delay_ms);


#endif /* TMR0_INTERFACE_H_ */
