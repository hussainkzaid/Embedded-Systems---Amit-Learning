/*
 * TMR0_program.c
 *
 * Created: 10/17/2025 9:04:18 PM
 *  Author: mahmo
 */ 
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "TMR0_config.h"
#include "TMR0_interface.h"
#include "TMR0_private.h"
#include "TMR0_register.h"


extern u32 global_u32NumOfIntrrupts;

static void(*PRV_pToFunctionCB_TMR0)(void);

void TMR0_voidInit(u8 copy_u8preloadValue)
{
	#if TMR0_MODE == TMR0_CTC_MODE
	// SET to normal mode
	CLR_BIT(TCCR0_REG, 6);
	CLR_BIT(TCCR0_REG, 3);
	
	// enable interrupt
	SET_BIT(TIMSK_REG, 0);
	
	// set preload value
	TCNT0_REG = copy_u8preloadValue;
	
	#elif
	// SET to CTC mode
	CLR_BIT(TCCR0_REG, 6);
	SET_BIT(TCCR0_REG, 3);
	
	// enable OSR0 request
	SET_BIT(TIMSK_REG, 1);
	
	// set preload value
	OCR0_REG = copy_u8preloadValue;	
	#endif
}

void TMR0_voidStart(u8 copy_u8prescaler)
{
	TCCR0_REG = ((TCCR0_REG & 0b11111000) | copy_u8prescaler);
}



void TMR0_voidSetCallbackTMR0(void(*pToFunctionToCB)(void))
{
	if(pToFunctionToCB != NULL)
	{
		PRV_pToFunctionCB_TMR0 = pToFunctionToCB;
	}
	else
	{
		// return error state
	}
}

void TMR0_voidSetDelay_msUsingCTC(u16 copy_u16Delay_ms)
{
	#define F_CPU       16000000UL
	#define PRESCALER   64
	#define TICK_TIME   ((float)PRESCALER / F_CPU)

	float desired_delay_sec = copy_u16Delay_ms / 1000.0;

	u8 OCR0_value = 249;

	float time_per_interrupt = (OCR0_value + 1) * TICK_TIME;
	
	global_u32NumOfIntrrupts = desired_delay_sec / time_per_interrupt;
}





void __vector_11 (void) __attribute__((signal));
void __vector_11 (void)
{
	if(PRV_pToFunctionCB_TMR0 != NULL)
	{
		PRV_pToFunctionCB_TMR0();
	}
	else
	{
		// return error state
	}
}
