/*
 * DCM_program.c
 *
 * Created: 10/31/2025 8:41:28 PM
 *  Author: mahmo
 */ 


#include "STD_TYPES.h"
#include "BIT_MATH.h"


#include "DIO_interface.h"

#include "DCM_config.h"
#include "DCM_interface.h"


#include "TMR0PWM_interface.h"

void DCM_voidInit(u8 copy_u8ChannelID)
{
	 switch(copy_u8ChannelID)
	 {
		 case DCM_CHANNEL_A:
			DIO_voidSetPinDirection(DCM_IN1_PORT, DCM_IN1_PIN, DIO_PIN_OUTPUT);
			DIO_voidSetPinDirection(DCM_IN2_PORT, DCM_IN2_PIN, DIO_PIN_OUTPUT);
			DIO_voidSetPinDirection(DCM_ENA_PORT, DCM_ENA_PIN, DIO_PIN_OUTPUT);
		 break;
		 case DCM_CHANNEL_B:
			DIO_voidSetPinDirection(DCM_IN3_PORT, DCM_IN3_PIN, DIO_PIN_OUTPUT);
			DIO_voidSetPinDirection(DCM_IN4_PORT, DCM_IN4_PIN, DIO_PIN_OUTPUT);
			DIO_voidSetPinDirection(DCM_ENB_PORT, DCM_ENB_PIN, DIO_PIN_OUTPUT);
		 break;
	 }
}
void DCM_voidOn(u8 copy_u8Direction, u8 copy_u8ChannelID)
{
	 switch(copy_u8ChannelID)
	 {
		case DCM_CHANNEL_A: 
			if (copy_u8Direction == DCM_CW)
			{
				DIO_voidSetPinValue(DCM_IN1_PORT, DCM_IN1_PIN, DIO_PIN_HIGH);
				DIO_voidSetPinValue(DCM_IN2_PORT, DCM_IN2_PIN, DIO_PIN_LOW);
			}
			else if (copy_u8Direction == DCM_CCW)
			{
				DIO_voidSetPinValue(DCM_IN1_PORT, DCM_IN1_PIN, DIO_PIN_LOW);
				DIO_voidSetPinValue(DCM_IN2_PORT, DCM_IN2_PIN, DIO_PIN_HIGH);
			}
			DIO_voidSetPinValue(DCM_ENA_PORT, DCM_ENA_PIN, DIO_PIN_HIGH);
			break;
			
		case DCM_CHANNEL_B:
			if (copy_u8Direction == DCM_CW)
			{
				DIO_voidSetPinValue(DCM_IN3_PORT, DCM_IN3_PIN, DIO_PIN_HIGH);
				DIO_voidSetPinValue(DCM_IN4_PORT, DCM_IN4_PIN, DIO_PIN_LOW);
			}
			else if (copy_u8Direction == DCM_CCW)
			{
				DIO_voidSetPinValue(DCM_IN3_PORT, DCM_IN3_PIN, DIO_PIN_LOW);
				DIO_voidSetPinValue(DCM_IN4_PORT, DCM_IN4_PIN, DIO_PIN_HIGH);
			}
			DIO_voidSetPinValue(DCM_ENB_PORT, DCM_ENB_PIN, DIO_PIN_HIGH);
			break;			
	 }
}
void DCM_voidOff(u8 copy_u8ChannelID)
{
	 switch(copy_u8ChannelID)
	 {
		 case DCM_CHANNEL_A:
			 // Clear direction pins first
			 DIO_voidSetPinValue(DCM_IN1_PORT, DCM_IN1_PIN, DIO_PIN_LOW);
			 DIO_voidSetPinValue(DCM_IN2_PORT, DCM_IN2_PIN, DIO_PIN_LOW);
			 // Then disable the motor
			 DIO_voidSetPinValue(DCM_ENA_PORT, DCM_ENA_PIN, DIO_PIN_LOW);
			break;
		 
		 case DCM_CHANNEL_B:
			 // Clear direction pins first
			 DIO_voidSetPinValue(DCM_IN3_PORT, DCM_IN3_PIN, DIO_PIN_LOW);
			 DIO_voidSetPinValue(DCM_IN4_PORT, DCM_IN4_PIN, DIO_PIN_LOW);
			 // Then disable the motor
			 DIO_voidSetPinValue(DCM_ENB_PORT, DCM_ENB_PIN, DIO_PIN_LOW);
			break;
	 }
}



void DCM_voidInitWithCtrlSpeed(u8 copy_u8ChannelID)
{
	 switch(copy_u8ChannelID)
	 {
		 case DCM_CHANNEL_A:
		 DIO_voidSetPinDirection(DCM_IN1_PORT, DCM_IN1_PIN, DIO_PIN_OUTPUT);
		 DIO_voidSetPinDirection(DCM_IN2_PORT, DCM_IN2_PIN, DIO_PIN_OUTPUT);
		 DIO_voidSetPinDirection(DCM_ENA_PORT, DCM_ENA_PIN, DIO_PIN_OUTPUT);
		 
		 TMR0PWM_voidInit();

		 break;
		 case DCM_CHANNEL_B:
		 DIO_voidSetPinDirection(DCM_IN3_PORT, DCM_IN3_PIN, DIO_PIN_OUTPUT);
		 DIO_voidSetPinDirection(DCM_IN4_PORT, DCM_IN4_PIN, DIO_PIN_OUTPUT);
		 DIO_voidSetPinDirection(DCM_ENB_PORT, DCM_ENB_PIN, DIO_PIN_OUTPUT);
		 break;
	 }
}
void DCM_voidOnWithCtrlSpeed(u8 copy_u8Direction, u8 copy_u8Speed, u8 copy_u8ChannelID)
{
	 switch(copy_u8ChannelID)
	 {
		 case DCM_CHANNEL_A:
			if (copy_u8Direction == DCM_CW)
			{
				DIO_voidSetPinValue(DCM_IN1_PORT, DCM_IN1_PIN, DIO_PIN_HIGH);
				DIO_voidSetPinValue(DCM_IN2_PORT, DCM_IN2_PIN, DIO_PIN_LOW);
			}
			else if (copy_u8Direction == DCM_CCW)
			{
				DIO_voidSetPinValue(DCM_IN1_PORT, DCM_IN1_PIN, DIO_PIN_LOW);
				DIO_voidSetPinValue(DCM_IN2_PORT, DCM_IN2_PIN, DIO_PIN_HIGH);
			}
			TMR0PWM_voidGenerate(copy_u8Speed, _64FROM_PRESCALER);
			break;
		 
		 case DCM_CHANNEL_B:
			if (copy_u8Direction == DCM_CW)
			{
				 DIO_voidSetPinValue(DCM_IN3_PORT, DCM_IN3_PIN, DIO_PIN_HIGH);
				 DIO_voidSetPinValue(DCM_IN4_PORT, DCM_IN4_PIN, DIO_PIN_LOW);
			}
			else if (copy_u8Direction == DCM_CCW)
			{
				 DIO_voidSetPinValue(DCM_IN3_PORT, DCM_IN3_PIN, DIO_PIN_LOW);
				 DIO_voidSetPinValue(DCM_IN4_PORT, DCM_IN4_PIN, DIO_PIN_HIGH);
			}
			/* Channel B speed control is typically tied to the same PWM channel or another timer. 
			   Assuming single speed control for simplicity as per requirement. */
			#if DCM_USE_SPEED_B == 1
			// TMRxPWM_voidGenerate(copy_u8Speed, ...) 
			#endif
			DIO_voidSetPinValue(DCM_ENB_PORT, DCM_ENB_PIN, DIO_PIN_HIGH); 
			break;
	 }
}

void DCM_voidOffWithCtrlSpeed(u8 copy_u8ChannelID)
{
	 switch(copy_u8ChannelID)
	 {
		 case DCM_CHANNEL_A:
		 TMR0PWM_voidStop();
		 break;
		 
		 case DCM_CHANNEL_B:
			
		 break;
	 }
}