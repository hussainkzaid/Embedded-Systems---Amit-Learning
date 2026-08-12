/*
 * EXTI_interface.h
 *
 * Created: 10/4/2025 7:04:21 PM
 *  Author: mahmo
 */ 


#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_


// enum values for interrupt pins
typedef enum 
{
	EXTI_INT0,	
	EXTI_INT1,
	EXTI_INT2,
} EXTI_intSrc_t;

// enum values for interrupt trigger edge
typedef enum
{
	EXTI_RISING_EDGE,
	EXTI_FALLING_EDGE,
	EXTI_HIGH_LEVEL,
	EXTI_LOW_LEVEL,
} EXTI_intSenseCtrl_t;




void EXIT_voidInit(EXTI_intSrc_t copy_tIntSource, EXTI_intSenseCtrl_t copy_tIntSenseCtrl);
void EXIT_voidEnable(EXTI_intSrc_t copy_tIntSource);
void EXIT_voidDisable(EXTI_intSrc_t copy_tIntSource);
void EXTI_voidSetCallbackINT0(void(*pToFunctionToCB)(void));
void EXTI_voidSetCallbackINT1(void(*pToFunctionToCB)(void));

#endif /* EXTI_INTERFACE_H_ */