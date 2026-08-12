/*
 * LED_interface.h
 *
 * Created: 9/13/2025 7:11:28 PM
 *  Author: mahmo
 */ 

// Macros for LED connection type 
#define LED_FORWARD_CONNECTION		0
#define LED_REVERSE_CONNECTION 		1

#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

void LED_voidInit(u8 copy_u8LedPort, u8 copy_u8LedPin);
void LED_voidOn(u8 copy_u8LedPort, u8 copy_u8LedPin, u8 copy_u8LedConnectionType);
void LED_voidOff(u8 copy_u8LedPort, u8 copy_u8LedPin, u8 copy_u8LedConnectionType);
void LED_voidToggle(u8 copy_u8LedPort, u8 copy_u8LedPin);



#endif /* LED_INTERFACE_H_ */