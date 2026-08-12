/*
 * EXTI_program.c
 *
 * Created: 10/4/2025 7:03:49 PM
 *  Author: mahmo
 */ 


// utils libirary
#include "BIT_MATH.h"
#include "STD_TYPES.h"

// MCAL
#include "EXTI_interface.h"
#include "EXTI_register.h"

static void(*PRV_pToFunctionCB_INT0)(void);
static void(*PRV_pToFunctionCB_INT1)(void);

void EXIT_voidInit(EXTI_intSrc_t copy_tIntSource, EXTI_intSenseCtrl_t copy_tIntSenseCtrl)
{
	switch (copy_tIntSource)
	{
		case EXTI_INT1: 
			switch(copy_tIntSenseCtrl)
			{
				case EXTI_LOW_LEVEL:
					CLR_BIT(MCUCR_REG, ISC11);
					CLR_BIT(MCUCR_REG, ISC10);
				case EXTI_HIGH_LEVEL:
					CLR_BIT(MCUCR_REG, ISC11);
					SET_BIT(MCUCR_REG, ISC10);
				case EXTI_FALLING_EDGE:
					SET_BIT(MCUCR_REG, ISC11);
					CLR_BIT(MCUCR_REG, ISC10);
				case EXTI_RISING_EDGE:
					SET_BIT(MCUCR_REG, ISC11);
					SET_BIT(MCUCR_REG, ISC10);
			}
			break;
		case EXTI_INT0:
			switch(copy_tIntSenseCtrl)
			{
				case EXTI_LOW_LEVEL:
					CLR_BIT(MCUCR_REG, ISC01);
					CLR_BIT(MCUCR_REG, ISC00);
				case EXTI_HIGH_LEVEL:
					CLR_BIT(MCUCR_REG, ISC01);
					SET_BIT(MCUCR_REG, ISC00);
				case EXTI_FALLING_EDGE:
					SET_BIT(MCUCR_REG, ISC01);
					CLR_BIT(MCUCR_REG, ISC00);
				case EXTI_RISING_EDGE:
					SET_BIT(MCUCR_REG, ISC01);
					SET_BIT(MCUCR_REG, ISC00);
			}
			break;
		case EXTI_INT2:
			switch(copy_tIntSenseCtrl)
			{
				case EXTI_FALLING_EDGE:
					CLR_BIT(MCUCSR_REG, ISC2);
				case EXTI_RISING_EDGE:
					SET_BIT(MCUCSR_REG, ISC2);
			}
			break;
	}
}


void EXIT_voidEnable(EXTI_intSrc_t copy_tIntSource)
{
	switch (copy_tIntSource)
	{
		case EXTI_INT0:
			SET_BIT(GICR_REG, INT0);
			break;
		case EXTI_INT1:
			SET_BIT(GICR_REG, INT1);
			break;
		case EXTI_INT2:
			SET_BIT(GICR_REG, INT2);
			break;
	}
}


void EXIT_voidDisable(EXTI_intSrc_t copy_tIntSource)
{	
	switch (copy_tIntSource)
	{
		case EXTI_INT0:
			CLR_BIT(GICR_REG, INT0);
			break;
		case EXTI_INT1:
			CLR_BIT(GICR_REG, INT1);
			break;
		case EXTI_INT2:
			CLR_BIT(GICR_REG, INT2);
			break;
	}
}

void EXTI_voidSetCallbackINT0(void(*pToFunctionToCB)(void))
{
	if(pToFunctionToCB != NULL)
	{
		PRV_pToFunctionCB_INT0 = pToFunctionToCB;
	}
	else
	{
		// return error state
	}
}


void __vector_1 (void) __attribute__((signal));
void __vector_1 (void)
{
	if(PRV_pToFunctionCB_INT0 != NULL)
	{
		PRV_pToFunctionCB_INT0();
	}
	else
	{
		// return error state
	}
}



void EXTI_voidSetCallbackINT1(void(*pToFunctionToCB)(void))
{
	if(pToFunctionToCB != NULL)
	{
		PRV_pToFunctionCB_INT1 = pToFunctionToCB;
	}
	else
	{
		// return error state
	}
}


void __vector_2 (void) __attribute__((signal));
void __vector_2 (void)
{
	if(PRV_pToFunctionCB_INT1 != NULL)
	{
		PRV_pToFunctionCB_INT1();
	}
	else
	{
		// return error state
	}
}