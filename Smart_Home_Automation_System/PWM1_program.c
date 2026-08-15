/*
 * PWM1_program.c
 *
 * Created: 11/16/2025 9:41:43 PM
 *  Author: hussain zaid
 */ 


#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "PWM1_config.h"
#include "PWM1_interface.h"
#include "PWM1_private.h"
#include "PWM1_register.h"

void PWM1_voidInit()
{
	//PWM Mode
	#if PWM1_MODE == PWM1_FAST_MODE_14
	//Select PWM1 Mode 14
	SET_BIT(TCCR1B_REG, WGM13);
	SET_BIT(TCCR1B_REG, WGM12);
	SET_BIT(TCCR1A_REG, WGM11);
	CLR_BIT(TCCR1A_REG, WGM10);
	
	#endif
	
	#if PWM1_COMPARE_MODE == PWM1_NON_INVERTING_MODE
	//Select PWM1 Non Inverting Mode
	SET_BIT(TCCR1A_REG, COM1A1);
	CLR_BIT(TCCR1A_REG, COM1A0);
	#endif
}


void PWM1_voidGenerate(u8 copy_u8Frequency, f32 copy_f32Duty)
{
	//Set Frequency
	ICR1_U16 = ((1000000.0/copy_u8Frequency) / 4.0) - 1 ;
	
	//Set Duty Ratio
	if(copy_f32Duty <= 100)
	{
		OCR1A_U16 = ((copy_f32Duty/100.0)*(ICR1_U16 + 1)) - 1 ;
	}
	
	//prescaler
	#if TMR1_PRESCALER == 64
	CLR_BIT(TCCR1B_REG, CS12);
	SET_BIT(TCCR1B_REG, CS11);
	SET_BIT(TCCR1B_REG, CS10);
	#endif
}


void PWM1_voidStopGenerate()
{
	CLR_BIT(TCCR1B_REG, CS12);
	CLR_BIT(TCCR1B_REG, CS11);
	CLR_BIT(TCCR1B_REG, CS10);
}