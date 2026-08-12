/*
 * TMR0PWM_program.c
 *
 * Created: 10/24/2025 7:58:55 PM
 *  Author: mahmo
 */ 
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "TMR0PWM_config.h"
#include "TMR0PWM_interface.h"
#include "TMR0PWM_register.h"

void TMR0PWM_voidInit()
{
	// Select PWM mode
	#if TMR0PWM_MODE == TMR0PWM_FAST_PWM
		SET_BIT(TCCR0_REG, 3);
		SET_BIT(TCCR0_REG, 6);
	#elif TMR0PWM_MODE == TMR0PWM_PHASE_CORRECT
		SET_BIT(TCCR0_REG, 3);
		CLR_BIT(TCCR0_REG, 6);
	#endif
	
	// select fast PWM mode mode
	#if TMR0PWM_FAST_PWM_MODE == TMR0PWM_FAST_PWM_NON_INVERTING
		SET_BIT(TCCR0_REG, 5);
		CLR_BIT(TCCR0_REG, 4);
	#elif TMR0PWM_FAST_PWM_MODE == TMR0PWM_FAST_PWM_INVERTING
		SET_BIT(TCCR0_REG, 5);
		SET_BIT(TCCR0_REG, 4);
	#endif
}

void TMR0PWM_voidGenerate(u8 copy_u8DutyRatio,u8 copy_u8prescaler)
{
	// setting duty ratio
	#if TMR0PWM_FAST_PWM_MODE == TMR0PWM_FAST_PWM_NON_INVERTING
		OCR0_REG = ((u32)copy_u8DutyRatio * 255) / 100;
	#elif TMR0PWM_FAST_PWM_MODE == TMR0PWM_FAST_PWM_INVERTING
		OCR0_REG = 255 - (((u32)copy_u8DutyRatio * 255) / 100);
	#endif 
	// setting prescaler value5
	TCCR0_REG = ((TCCR0_REG & 0b11111000) | copy_u8prescaler);
}

void TMR0PWM_voidStop()
{
	// stop by setting the prescaler 0
	TCCR0_REG = (TCCR0_REG & 0b11111000);
}