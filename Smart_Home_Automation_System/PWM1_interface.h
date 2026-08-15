/*
 * PWM1_interface.h
 *
 * Created: 11/16/2025 9:41:56 PM
 *  Author: hussain zaid
 */ 


#ifndef PWM1_INTERFACE_H_
#define PWM1_INTERFACE_H_

void PWM1_voidInit();
void PWM1_voidGenerate(u8 copy_u8Frequency, f32 copy_u8Duty);
void PWM1_voidStopGenerate();

#endif /* PWM1_INTERFACE_H_ */