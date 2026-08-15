/*
 * BUZZER_interface.h
 *
 * Created: 9/19/2025 2:44:41 AM
 *  Author: hussain zaid
 */ 


#ifndef BUZZER_INTERFACE_H_
#define BUZZER_INTERFACE_H_

/***************************************** APIs Prototypes *****************************************/
void BUZZER_voidInit(u8 copy_u8BuzzerPort, u8 copy_u8BuzzerPin);
void BUZZER_voidOn(u8 copy_u8BuzzerPort, u8 copy_u8BuzzerPin);
void BUZZER_voidOff(u8 copy_u8BuzzerPort, u8 copy_u8BuzzerPin);
void BUZZER_voidToggle(u8 copy_u8BuzzerPort, u8 copy_u8BuzzerPin);

#endif /* BUZZER_INTERFACE_H_ */