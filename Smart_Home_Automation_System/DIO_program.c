/*
 * DIO_program.c
 *
 * Created: 9/16/2025 10:32:24 PM
 *  Author: hussain zaid
 */ 

#include <avr/io.h> //temporary

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "DIO_register.h"

/* PIN APIs */
void DIO_voidSetPinDirection(u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinDirection){
	switch(copy_u8PinDirection)
	{
		case DIO_PIN_INPUT: 
		switch(copy_u8PortId)
		{
			case DIO_PORTA: CLR_BIT(DDRA_REG, copy_u8PinId); break;
			case DIO_PORTB: CLR_BIT(DDRB_REG, copy_u8PinId); break;
			case DIO_PORTC: CLR_BIT(DDRC_REG, copy_u8PinId); break;
			case DIO_PORTD: CLR_BIT(DDRD_REG, copy_u8PinId); break;
		}
		break;
		
		case DIO_PIN_OUTPUT:
		switch(copy_u8PortId)
		{
			case DIO_PORTA: SET_BIT(DDRA_REG, copy_u8PinId); break;
			case DIO_PORTB: SET_BIT(DDRB_REG, copy_u8PinId); break;
			case DIO_PORTC: SET_BIT(DDRC_REG, copy_u8PinId); break;
			case DIO_PORTD: SET_BIT(DDRD_REG, copy_u8PinId); break;
		}
		break;
	}
}


void DIO_voidSetPinValue(u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinValue){
	switch(copy_u8PinValue)
	{
		case DIO_PIN_LOW:
		switch(copy_u8PortId)
		{
			case DIO_PORTA: CLR_BIT(PORTA_REG, copy_u8PinId); break;
			case DIO_PORTB: CLR_BIT(PORTB_REG, copy_u8PinId); break;
			case DIO_PORTC: CLR_BIT(PORTC_REG, copy_u8PinId); break;
			case DIO_PORTD: CLR_BIT(PORTD_REG, copy_u8PinId); break;
		}
		break;
		
		case DIO_PIN_HIGH:
		switch(copy_u8PortId)
		{
			case DIO_PORTA: SET_BIT(PORTA_REG, copy_u8PinId); break;
			case DIO_PORTB: SET_BIT(PORTB_REG, copy_u8PinId); break;
			case DIO_PORTC: SET_BIT(PORTC_REG, copy_u8PinId); break;
			case DIO_PORTD: SET_BIT(PORTD_REG, copy_u8PinId); break;
		}
		break;
	}
}


void DIO_voidTogglePinValue(u8 copy_u8PortId, u8 copy_u8PinId){
	switch(copy_u8PortId)
	{
		case DIO_PORTA: TOGGLE_BIT(PORTA_REG, copy_u8PinId); break;
		case DIO_PORTB: TOGGLE_BIT(PORTB_REG, copy_u8PinId); break;
		case DIO_PORTC: TOGGLE_BIT(PORTC_REG, copy_u8PinId); break;
		case DIO_PORTD: TOGGLE_BIT(PORTD_REG, copy_u8PinId); break;
	}
}


u8 DIO_u8GetPinValue(u8 copy_u8PortId, u8 copy_u8PinId){
	u8 local_u8PinValue;
	switch(copy_u8PortId)
	{
		case DIO_PORTA: local_u8PinValue = GET_BIT(PINA_REG, copy_u8PinId); break;
		case DIO_PORTB: local_u8PinValue = GET_BIT(PINB_REG, copy_u8PinId); break;
		case DIO_PORTC: local_u8PinValue = GET_BIT(PINC_REG, copy_u8PinId); break;
		case DIO_PORTD: local_u8PinValue = GET_BIT(PIND_REG, copy_u8PinId); break;
	}
	return local_u8PinValue;
}


void DIO_voidGetPinValue(u8 copy_u8PortId, u8 copy_u8PinId, u8* copy_pu8PinValue){
	if(copy_pu8PinValue != NULL){
		switch(copy_u8PortId)
		{
			case DIO_PORTA: *copy_pu8PinValue = GET_BIT(PINA_REG, copy_u8PinId); break;
			case DIO_PORTB: *copy_pu8PinValue = GET_BIT(PINB_REG, copy_u8PinId); break;
			case DIO_PORTC: *copy_pu8PinValue = GET_BIT(PINC_REG, copy_u8PinId); break;
			case DIO_PORTD: *copy_pu8PinValue = GET_BIT(PIND_REG, copy_u8PinId); break;
		}
	}
}


void DIO_voidActivePinInternalPUR(u8 copy_u8PortId, u8 copy_u8PinId){
	switch(copy_u8PortId)
	{
		case DIO_PORTA: SET_BIT(PORTA_REG, copy_u8PinId); break;
		case DIO_PORTB: SET_BIT(PORTB_REG, copy_u8PinId); break;
		case DIO_PORTC: SET_BIT(PORTC_REG, copy_u8PinId); break;
		case DIO_PORTD: SET_BIT(PORTD_REG, copy_u8PinId); break;
	}
}



/* Port APIs */
void DIO_voidSetPortDirection(u8 copy_u8PortId, u8 copy_u8PortDirection){
	switch(copy_u8PortDirection)
	{
		case DIO_PORT_INPUT:
		switch(copy_u8PortId)
		{
			case DIO_PORTA: DDRA_REG = 0X00; break;
			case DIO_PORTB: DDRB_REG = 0X00; break;
			case DIO_PORTC: DDRC_REG = 0X00; break;
			case DIO_PORTD: DDRD_REG = 0X00; break;
		}
		break;
		
		case DIO_PORT_OUTPUT:
		switch(copy_u8PortId)
		{
			case DIO_PORTA: DDRA_REG = 0XFF; break;
			case DIO_PORTB: DDRB_REG = 0XFF; break;
			case DIO_PORTC: DDRC_REG = 0XFF; break;
			case DIO_PORTD: DDRD_REG = 0XFF; break;
		}
		break;
	}
}


void DIO_voidSetPortValue(u8 copy_u8PortId, u8 copy_u8PortValue){
	switch(copy_u8PortId)
	{
		case DIO_PORTA: PORTA_REG = copy_u8PortValue; break;
		case DIO_PORTB: PORTB_REG = copy_u8PortValue; break;
		case DIO_PORTC: PORTC_REG = copy_u8PortValue; break;
		case DIO_PORTD: PORTD_REG = copy_u8PortValue; break;
	}
}


void DIO_voidTogglePortValue(u8 copy_u8PortId){
	switch(copy_u8PortId)
	{
		case DIO_PORTA: PORTA_REG ^= 0XFF; break;
		case DIO_PORTB: PORTB_REG ^= 0XFF; break;
		case DIO_PORTC: PORTC_REG ^= 0XFF; break;
		case DIO_PORTD: PORTD_REG ^= 0XFF; break;
	}
}


void DIO_voidGetPortValue(u8 copy_u8PortId, u8* copy_pu8PortValue){
	if(copy_pu8PortValue != NULL){
		switch(copy_u8PortId)
		{
			case DIO_PORTA: *copy_pu8PortValue = PINA_REG; break;
			case DIO_PORTB: *copy_pu8PortValue = PINB_REG; break;
			case DIO_PORTC: *copy_pu8PortValue = PINC_REG; break;
			case DIO_PORTD: *copy_pu8PortValue = PIND_REG; break;
		}
	}
}


void DIO_voidActivePortInternalPUR(u8 copy_u8PortId){
	switch(copy_u8PortId)
	{
		case DIO_PORTA: PORTA_REG = 0XFF; break;
		case DIO_PORTB: PORTB_REG = 0XFF; break;
		case DIO_PORTC: PORTC_REG = 0XFF; break;
		case DIO_PORTD: PORTD_REG = 0XFF; break;
	}
}
