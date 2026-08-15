/*
 * SRVM_program.c
 *
 * Created: 11/16/2025 10:00:04 PM
 *  Author: hussain zaid
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "DIO_interface.h"
#include "PWM1_interface.h"

#include "SRVM_interface.h"

void SRVM_voidInit()
{
	DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN5, DIO_PIN_OUTPUT);
	
	PWM1_voidInit();
}


void SRVM_voidOn(u16 copy_u16Angle)
{
	f32 tOn = (copy_u16Angle/180.0) + 1 ;
	
	f32 duty = (tOn/20.0)*100 ;
	
	PWM1_voidGenerate(50, duty);
}


void SRVM_voidOff()
{
	PWM1_voidStopGenerate();
}