/*
* DIO_program.c
 *
 * Created: 9/12/2025 7:49:47 PM
 *  Author: mahmo
 */ 

#include "avr/io.h"

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "DIO_register.h"

void DIO_voidSetPinDirection(u8 copy_u8PortId, u8 copy_u8PinId,  u8 copy_u8PinDirection)
{
	switch (copy_u8PinDirection)
	{
		case DIO_PIN_INPUT:
			switch (copy_u8PortId)
			{
				case DIO_PORTA: CLR_BIT(DDRA_REG, copy_u8PinId); break;					
				case DIO_PORTB: CLR_BIT(DDRB_REG, copy_u8PinId); break;
				case DIO_PORTC: CLR_BIT(DDRC_REG, copy_u8PinId); break;
				case DIO_PORTD: CLR_BIT(DDRD_REG, copy_u8PinId); break;
			}							
		break;								
		case DIO_PIN_OUTPUT:			
			switch (copy_u8PortId)			
			{								
				case DIO_PORTA: SET_BIT(DDRA_REG, copy_u8PinId); break;
				case DIO_PORTB: SET_BIT(DDRB_REG, copy_u8PinId); break;
				case DIO_PORTC: SET_BIT(DDRC_REG, copy_u8PinId); break;
				case DIO_PORTD: SET_BIT(DDRD_REG, copy_u8PinId); break;
			}
		break;
	}
}

void DIO_voidSetPinValue(u8 copy_u8PortId, u8 copy_u8PinId,  u8 copy_u8PinValue)
{
	switch (copy_u8PinValue)
	{
		case DIO_PIN_LOW:
		switch (copy_u8PortId)
		{
			case DIO_PORTA: CLR_BIT(PORTA_REG, copy_u8PinId); break;
			case DIO_PORTB: CLR_BIT(PORTB_REG, copy_u8PinId); break;
			case DIO_PORTC: CLR_BIT(PORTC_REG, copy_u8PinId); break;
			case DIO_PORTD: CLR_BIT(PORTD_REG, copy_u8PinId); break;
		}
		break;
		case DIO_PIN_HIGH:
		switch (copy_u8PortId)
		{
			case DIO_PORTA: SET_BIT(PORTA_REG, copy_u8PinId); break;
			case DIO_PORTB: SET_BIT(PORTB_REG, copy_u8PinId); break;
			case DIO_PORTC: SET_BIT(PORTC_REG, copy_u8PinId); break;
			case DIO_PORTD: SET_BIT(PORTD_REG, copy_u8PinId); break;
		}
		break;
	}
}

void DIO_voidTogglePinValue(u8 copy_u8PortId, u8 copy_u8PinId)
{
	switch (copy_u8PortId)
	{
		case DIO_PORTA: TOG_BIT(PORTA_REG, copy_u8PinId); break;
		case DIO_PORTB: TOG_BIT(PORTB_REG, copy_u8PinId); break;
		case DIO_PORTC: TOG_BIT(PORTC_REG, copy_u8PinId); break;
		case DIO_PORTD: TOG_BIT(PORTD_REG, copy_u8PinId); break;

	}	
}

u8 DIO_u8GetPinValue(u8 copy_u8PortId, u8 copy_u8PinId)
{
	u8 local_u8PinValue;
	switch(copy_u8PortId)
	{
		case DIO_PORTA: local_u8PinValue = GET_BIT(PINA_REG, copy_u8PinId); break;
		case DIO_PORTB: local_u8PinValue = GET_BIT(PINB_REG, copy_u8PinId); break;
		case DIO_PORTC: local_u8PinValue = GET_BIT(PINC_REG, copy_u8PinId); break;
		case DIO_PORTD: local_u8PinValue = GET_BIT(PIND_REG, copy_u8PinId); break;
		default: local_u8PinValue = 0; break;
	}
	return local_u8PinValue;
}

void DIO_voidGetPinValue(u8 copy_u8PortId, u8 copy_u8PinId,  u8*pu8PinValue)
{
	// bool local_tErrorState = TRUE;
	if ((copy_u8PortId <= 3 ) && (copy_u8PinId <= 7) && (pu8PinValue != NULL))
	{
		switch(copy_u8PortId)
		{
			case DIO_PORTA: *pu8PinValue = GET_BIT(PINA_REG, copy_u8PinId); break;
			case DIO_PORTB: *pu8PinValue = GET_BIT(PINB_REG, copy_u8PinId); break;
			case DIO_PORTC: *pu8PinValue = GET_BIT(PINC_REG, copy_u8PinId); break;
			case DIO_PORTD: *pu8PinValue = GET_BIT(PIND_REG, copy_u8PinId); break;

		}
	}

}

void DIO_voidActivePinInternalPUR(u8 copy_u8PortId, u8 copy_u8PinId)
{
		if ((copy_u8PortId <= 3 ) && (copy_u8PinId <= 7))
		{
			switch(copy_u8PortId)
			{
				case DIO_PORTA: SET_BIT(PORTA_REG, copy_u8PinId); break;
				case DIO_PORTB: SET_BIT(PORTB_REG, copy_u8PinId); break;
				case DIO_PORTC: SET_BIT(PORTC_REG, copy_u8PinId); break;
				case DIO_PORTD: SET_BIT(PORTD_REG, copy_u8PinId); break;

			}
		}
}

void DIO_voidSetPortDirection(u8 copy_u8PortId, u8 copy_u8PortDirection)
{
	switch(copy_u8PortDirection)
	{
		case DIO_PORT_INPUT: 
			switch(copy_u8PortId)
			{
				case DIO_PORTA: DDRA_REG = DIO_PORT_LOW; break;
				case DIO_PORTB: DDRB_REG = DIO_PORT_LOW; break;
				case DIO_PORTC: DDRC_REG = DIO_PORT_LOW; break;
				case DIO_PORTD: DDRD_REG = DIO_PORT_LOW; break;
			}
			break;
		case DIO_PORT_OUTPUT:
			switch(copy_u8PortId)
			{
				case DIO_PORTA: DDRA_REG = DIO_PORT_HIGH; break;
				case DIO_PORTB: DDRB_REG = DIO_PORT_HIGH; break;
				case DIO_PORTC: DDRC_REG = DIO_PORT_HIGH; break;
				case DIO_PORTD: DDRD_REG = DIO_PORT_HIGH; break;
			}
			break;
	}
}

void DIO_voidSetPortValue(u8 copy_u8PortId, u8 copy_u8PortValue)
{
	switch(copy_u8PortId)
	{
		case DIO_PORTA: PORTA_REG = copy_u8PortValue; break;
		case DIO_PORTB: PORTB_REG = copy_u8PortValue; break;
		case DIO_PORTC: PORTC_REG = copy_u8PortValue; break;
		case DIO_PORTD: PORTD_REG = copy_u8PortValue; break;
	}
}

void DIO_voidTogglePortValue(u8 copy_u8PortId)
{
	switch(copy_u8PortId)
	{
		case DIO_PORTA: PORTA_REG = ~PORTA_REG; break;
		case DIO_PORTB: PORTB_REG = ~PORTB_REG; break;
		case DIO_PORTC: PORTC_REG = ~PORTC_REG; break;
		case DIO_PORTD: PORTD_REG = ~PORTD_REG; break;
	}
}

u8 DIO_u8GetPortValue(u8 copy_u8PortId)
{
	u8 u8PortValue;
	switch(copy_u8PortId)
	{
		case DIO_PORTA: u8PortValue = PINA_REG; break;
		case DIO_PORTB: u8PortValue = PINB_REG; break;
		case DIO_PORTC: u8PortValue = PINC_REG; break;
		case DIO_PORTD: u8PortValue = PIND_REG; break;
		default: u8PortValue = DIO_PORT_LOW; break;
	}
	return u8PortValue;
}

void DIO_voidGetPortValue(u8 copy_u8PortId, u8*pu8PortValue)
{
	switch(copy_u8PortId)
	{
		case DIO_PORTA: *pu8PortValue = PINA_REG; break;
		case DIO_PORTB: *pu8PortValue = PINB_REG; break;
		case DIO_PORTC: *pu8PortValue = PINC_REG; break;
		case DIO_PORTD: *pu8PortValue = PIND_REG; break;
	}
}

void DIO_voidActivePortInternalPUR(u8 copy_u8PortId)
{
	switch(copy_u8PortId)
	{
		case DIO_PORTA: PORTA_REG = DIO_PORT_HIGH; break;
		case DIO_PORTB: PORTB_REG = DIO_PORT_HIGH; break;
		case DIO_PORTC: PORTC_REG = DIO_PORT_HIGH; break;
		case DIO_PORTD: PORTD_REG = DIO_PORT_HIGH; break;
	}
}