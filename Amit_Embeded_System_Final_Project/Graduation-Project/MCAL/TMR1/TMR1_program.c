/*
 * TMR1_program.c
 *
 * Created: 10/17/2025 9:04:18 PM
 *  Author: mahmo
 */ 
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "TMR1_config.h"
#include "TMR1_interface.h"
#include "TMR1_private.h"
#include "TMR1_register.h"




static void(*PRV_pToFunctionCB_TMR1)(void);

void TMR1_voidInit(u16 copy_u8preloadValue)
{
	// SET to normal mode
	TCCR1A_REG = 0x00;
	CLR_BIT(TCCR1B_REG, 4);
	CLR_BIT(TCCR1B_REG, 3);
	
	// enable interrupt
	SET_BIT(TIMSK_REG, 2);
	
	// set preload value
	TCNT1_REG = copy_u8preloadValue;
}

void TMR1_voidStart(u8 copy_u8prescaler)
{
	TCCR1B_REG = ((TCCR1B_REG & 0b11111000) | copy_u8prescaler);
}



void TMR1_voidSetCallbackTMR1(void(*pToFunctionToCB)(void))
{
	if(pToFunctionToCB != NULL)
	{
		PRV_pToFunctionCB_TMR1 = pToFunctionToCB;
	}
	else
	{
		// return error state
	}
}


void __vector_9 (void) __attribute__((signal));
void __vector_9 (void)
{
	if(PRV_pToFunctionCB_TMR1 != NULL)
	{
		PRV_pToFunctionCB_TMR1();
	}
	else
	{
		// return error state
	}
}
