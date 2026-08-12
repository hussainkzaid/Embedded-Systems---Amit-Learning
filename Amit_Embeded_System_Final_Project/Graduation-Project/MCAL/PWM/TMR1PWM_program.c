/*
 * TMR1PWM_program.c
 *
 * Created: 11/1/2025 7:32:51 PM
 *  Author: mahmo
 */ 



#include "TMR1PWM_config.h"
#include "TMR1PWM_interface.h"
#include "TMR1PWM_private.h"
#include "TMR1PWM_register.h"

#include "BIT_MATH.h"



void TMR1PWM_voidInit(void)
{
	// fast PWM mode
	SET_BIT(TCCR1A_REG, 1);
	CLR_BIT(TCCR1A_REG, 0);
	SET_BIT(TCCR1B_REG, 4);
	SET_BIT(TCCR1B_REG, 3);

	// non-inverting mode
	SET_BIT(TCCR1A_REG, 7);
	CLR_BIT(TCCR1A_REG, 6);
}

void TMR1PWM_voidGenerate(u32 copy_u32Frequency, f32 copy_u8DutyRatio, u8 copy_u8prescaler)
{

	ICR1_REG = ((1000000UL / copy_u32Frequency) / 4) - 1;


	OCR1A_REG = ((copy_u8DutyRatio * (ICR1_REG + 1)) / 100) - 1;

	// start
	TCCR1B_REG = (TCCR1B_REG & 0b11111000) | copy_u8prescaler;
}

void TMR1PWM_voidStop()
{
	// stop by setting the prescaler 0
	TCCR1B_REG = (TCCR1B_REG & 0b11111000);
}


