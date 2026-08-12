/*
 * SWITCH_interface.h
 *
 * Created: 9/13/2025 7:51:35 PM
 *  Author: mahmo
 */ 


#ifndef SWITCH_INTERFACE_H_
#define SWITCH_INTERFACE_H_


// Macros for Switch connection type
#define SWITCH_FORWARD_CONNECTION			0
#define SWITCH_REVERSE_CONNECTION			1

// Macros for Switch Status
#define SWITCH_PRESSED						3
#define SWITCH_NOT_PRESSED					4



void SWITCH_voidInit(u8 copy_u8SwitchPort, u8 copy_u8SwitchPin);
void SWITCH_voidGetStatus(u8 copy_u8SwitchPort, u8 copy_u8SwitchPin, u8 copy_u8SwitchConnectionType, u8* pu8SwitchStatus);


#endif /* SWITCH_INTERFACE_H_ */