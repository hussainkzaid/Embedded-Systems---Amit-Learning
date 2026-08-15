/*
 * DIO_interface.h
 *
 * Created: 9/16/2025 10:32:44 PM
 *  Author: hussain zaid
 */ 


#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

// Macros For Pin Type
#define DIO_PIN_INPUT		0		
#define DIO_PIN_OUTPUT		1

// Macros For Port Type
#define DIO_PORT_INPUT		0X00
#define DIO_PORT_OUTPUT		0XFF

// Macros For Port Id
#define DIO_PORTA		0
#define DIO_PORTB		1
#define DIO_PORTC		2
#define DIO_PORTD		3

//Macros For Pin Id
#define DIO_PIN0		0
#define DIO_PIN1		1
#define DIO_PIN2		2
#define DIO_PIN3		3
#define DIO_PIN4		4
#define DIO_PIN5		5
#define DIO_PIN6		6
#define DIO_PIN7		7

//Macros For Output 
#define DIO_PIN_LOW			0 //THIS VALUE HAS NO EFFECT ITS FOR CHECK ONLY
#define DIO_PIN_HIGH		1 //THIS VALUE HAS NO EFFECT ITS FOR CHECK ONLY

/*************** APIs Prototypes ***************/

/* PIN APIs */
void DIO_voidSetPinDirection(u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinDirection);
void DIO_voidSetPinValue(u8 copy_u8PortId, u8 copy_u8PinId, u8 copy_u8PinValue);
void DIO_voidTogglePinValue(u8 copy_u8PortId, u8 copy_u8PinId);
u8 DIO_u8GetPinValue(u8 copy_u8PortId, u8 copy_u8PinId);
void DIO_voidGetPinValue(u8 copy_u8PortId, u8 copy_u8PinId, u8* copy_pu8PinValue);
void DIO_voidActivePinInternalPUR(u8 copy_u8PortId, u8 copy_u8PinId);

/* Port APIs */
void DIO_voidSetPortDirection(u8 copy_u8PortId, u8 copy_u8PortDirection);
void DIO_voidSetPortValue(u8 copy_u8PortId, u8 copy_u8PortValue);
void DIO_voidTogglePortValue(u8 copy_u8PortId);
void DIO_voidGetPortValue(u8 copy_u8PortId, u8* copy_pu8PortValue);
void DIO_voidActivePortInternalPUR(u8 copy_u8PortId);


#endif /* DIO_INTERFACE_H_ */