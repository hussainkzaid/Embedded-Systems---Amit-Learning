/*
 * SWITCH_program.c
 *
 * Created: 9/13/2025 7:52:04 PM
 *  Author: mahmo
 */ 


// UTILES_LIB
#include "STD_TYPES.h"
#include "BIT_MATH.h"

// MCAL
#include "DIO_INTERFACE.h"

// HAL
#include "SWITCH_interface.h"



void SWITCH_voidInit(u8 copy_u8SwitchPort, u8 copy_u8SwitchPin)
{
	DIO_voidSetPinDirection(copy_u8SwitchPort, copy_u8SwitchPin, DIO_PIN_INPUT);
	DIO_voidActivePinInternalPUR(copy_u8SwitchPort, copy_u8SwitchPin);
}


void SWITCH_voidGetStatus(u8 copy_u8SwitchPort, u8 copy_u8SwitchPin, u8 copy_u8SwitchConnectionType, u8* pu8SwitchStatus)
{
	u8 local_u8PinVal;
	switch(copy_u8SwitchConnectionType)
	{
		case SWITCH_FORWARD_CONNECTION:
		DIO_voidGetPinValue(copy_u8SwitchPort, copy_u8SwitchPin, &local_u8PinVal);
		switch(local_u8PinVal)
		{
			case DIO_PIN_HIGH:
			*pu8SwitchStatus = SWITCH_PRESSED;
			break;
			
			case DIO_PIN_LOW:
			*pu8SwitchStatus = SWITCH_NOT_PRESSED;
			break;
		}
		break;
		
		case SWITCH_REVERSE_CONNECTION:
		DIO_voidGetPinValue(copy_u8SwitchPort, copy_u8SwitchPin, &local_u8PinVal);
		switch(local_u8PinVal)
		{
			case DIO_PIN_HIGH:
			*pu8SwitchStatus = SWITCH_NOT_PRESSED;
			break;
			
			case DIO_PIN_LOW:
			*pu8SwitchStatus = SWITCH_PRESSED;
			break;
		}
		break;
	}
}