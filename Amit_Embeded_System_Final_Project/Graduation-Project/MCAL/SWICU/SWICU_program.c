/*
 * SWICU_program.c
 *
 * Created: 11/14/2025 8:30:04 PM
 *  Author: mahmo
 */ 

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "SWICU_interface.h"
#include "SWICU_register.h"

#include "DIO_interface.h"
#include "TMR0_interface.h"
#include "GI_interface.h"
#include "EXTI_interface.h"



volatile u8 global_u8State = 0;

volatile u32 global_u32Count;
volatile u32 global_u32OnCount;
volatile u32 global_u32OnTick;
volatile u32 global_u32TotalCount;
volatile u32 global_u32TotalTick;


void SWICU_voidInit(void)
{
	DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN2, DIO_PIN_INPUT);
	GI_voidEnableGeneralInterrupts();
	
	// SET to normal mode
	CLR_BIT(TCCR0_REG, 6);
	CLR_BIT(TCCR0_REG, 3);
	
	// enable interrupt
	SET_BIT(TIMSK_REG, 0);	
	
	EXIT_voidInit(EXTI_INT0, EXTI_RISING_EDGE);

}


void SWICU_voidStart(void)
{

	TMR0_voidSetCallbackTMR0(&TMR0_ISR_Function);
	EXTI_voidSetCallbackINT0(&INT0_ISR_Function);
	
	TMR0_voidStart(_64FROM_PRESCALER);
	EXIT_voidEnable(EXTI_INT0);
}


void SWICU_voidGetData(f32* copy_f32PtrFrequency, f32* copy_f32PtrDuty)
{	
	if(global_u8State == 3)
	{
		*copy_f32PtrFrequency = (float)1000000 / (float)((global_u32TotalTick + global_u32TotalCount * 256) * 4);
		*copy_f32PtrDuty = ((float)(global_u32OnTick + global_u32OnCount * 256) / (float)(global_u32TotalTick + global_u32TotalCount * 256)) * 100;
		global_u8State = 0;
	}
}



void TMR0_ISR_Function(void)
{
	global_u32Count++;
}

void INT0_ISR_Function(void)
{
	GIFR_REG = GIFR_REG & 1; // clear int0 flag
	switch(global_u8State)
	{
		case 0:
			global_u32Count = 0;
			TCNT0_REG = 0x00;
			SET_BIT(MCUCR_REG, ISC01);
			CLR_BIT(MCUCR_REG, ISC00);
			global_u8State++;
			break;
		case 1:
			global_u32OnCount = global_u32Count;
			global_u32OnTick = TCNT0_REG;
			SET_BIT(MCUCR_REG, ISC01);
			SET_BIT(MCUCR_REG, ISC00);
			global_u8State++;
			break;
		case 2:
			global_u32TotalCount = global_u32Count;
			global_u32TotalTick = TCNT0_REG;
			global_u8State++;
			break;
	}
}

