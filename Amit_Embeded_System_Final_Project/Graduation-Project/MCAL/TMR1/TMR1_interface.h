/*
 * TMR1_interface.h
 *
 * Created: 10/17/2025 9:03:04 PM
 *  Author: mahmo
 */ 


#ifndef TMR1_INTERFACE_H_
#define TMR1_INTERFACE_H_


// enum values for prescaler
typedef enum
{
	NO_CLK_SRC,							// 0 0 0
	NO_PRESCALING,						// 0 0 1
	_8FROM_PRESCALER,					// 0 1 0
	_64FROM_PRESCALER,					// 0 1 1
	_256FROM_PRESCALER,					// 1 0 0 
	_1024FROM_PRESCALER,				// 1 0 1
} TMR1_prescaler_t;

void TMR1_voidInit(u16 copy_u8preloadValue);
void TMR1_voidStart(u8 copy_u8prescaler);
void TMR1_voidSetCallbackTMR1(void(*pToFunctionToCB)(void));

#endif /* TMR1_INTERFACE_H_ */
