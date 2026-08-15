/*
 * LED_interface.h
 *
 * Created: 9/19/2025 2:21:53 AM
 *  Author: hussain zaid
 */ 


#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_


// Macros For Led Connection Type
#define LED_REVERSE_CONNECTION			0
#define LED_FORWARD_CONNECTION			1

/******************************************* APIs Prototypes *******************************************/
void LED_voidInit(u8 copy_u8LedPort, u8 copy_u8LedPin);
void LED_voidOn(u8 copy_u8LedPort, u8 copy_u8LedPin, u8 copy_u8LedConnectionType);
void LED_voidOff(u8 copy_u8LedPort, u8 copy_u8LedPin, u8 copy_u8LedConnectionType);
void LED_voidToggle(u8 copy_u8LedPort, u8 copy_u8LedPin);

#endif /* LED_INTERFACE_H_ */