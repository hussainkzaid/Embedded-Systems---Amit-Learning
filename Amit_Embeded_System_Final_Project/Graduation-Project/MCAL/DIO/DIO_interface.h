/*
 * DIO_INTERFACE.h
 *
 * Created: 9/12/2025 7:48:08 PM
 *  Author: mahmo
 */ 


#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

// Macros for pin types
#define  DIO_PIN_INPUT		0
#define  DIO_PIN_OUTPUT		1

// Macros for port types
#define  DIO_PORT_INPUT		0
#define  DIO_PORT_OUTPUT	1

// Macros for ports types
#define DIO_PORTA			0
#define DIO_PORTB			1
#define DIO_PORTC			2
#define DIO_PORTD			3

// Macros for pin ID
#define DIO_PIN0			0
#define DIO_PIN1			1
#define DIO_PIN2			2
#define DIO_PIN3			3
#define DIO_PIN4			4
#define DIO_PIN5			5
#define DIO_PIN6			6
#define DIO_PIN7			7

// Macros for pin state
#define DIO_PIN_LOW			0
#define DIO_PIN_HIGH		1

// Macros for port state
#define DIO_PORT_LOW		0
#define DIO_PORT_HIGH		((u8)255)


// Pin APIs Prototypes 
void DIO_voidSetPinDirection(u8 copy_u8PortId, u8 copy_u8PinId,  u8 copy_u8PinDirection);
void DIO_voidSetPinValue(u8 copy_u8PortId, u8 copy_u8PinId,  u8 copy_u8PinValue);
void DIO_voidTogglePinValue(u8 copy_u8PortId, u8 copy_u8PinId);
u8 DIO_u8GetPinValue(u8 copy_u8PortId, u8 copy_u8PinId);
void DIO_voidGetPinValue(u8 copy_u8PortId, u8 copy_u8PinId,  u8*pu8PinValue);
void DIO_voidActivePinInternalPUR(u8 copy_u8PortId, u8 copy_u8PinId);

// Port APIs Prototypes 
void DIO_voidSetPortDirection(u8 copy_u8PortId, u8 copy_u8PortDirection);
void DIO_voidSetPortValue(u8 copy_u8PortId, u8 copy_u8PortValue);
void DIO_voidTogglePortValue(u8 copy_u8PortId);
u8 DIO_u8GetPortValue(u8 copy_u8PortId);
void DIO_voidGetPortValue(u8 copy_u8PortId, u8*pu8PortValue);
void DIO_voidActivePortInternalPUR(u8 copy_u8PortId);

#endif /* DIO_INTERFACE_H_ */