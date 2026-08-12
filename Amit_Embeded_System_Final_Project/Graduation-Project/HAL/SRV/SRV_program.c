/*
 * SRV_program.c
 *
 * Created: 11/1/2025 9:12:47 PM
 *  Author: mahmo
 */ 

#include "STD_TYPES.h"
#include "SRV_interface.h"
#include "DIO_interface.h"
#include "TMR1PWM_interface.h"


u8 global_u8LastAngle = 90;
void SRV_voidInit(void)
{
	DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN5, DIO_PIN_OUTPUT);
	TMR1PWM_voidInit();
	TMR1PWM_voidGenerate(50, 7.5, _64FROM_PRESCALER);
	global_u8LastAngle = 90;
}
void SRV_voidOn(u8 copy_u8Angle)
{
    //if (copy_u8Angle > 180) return;
    if (copy_u8Angle == global_u8LastAngle) return;

    f32 local_f32Duty = 5.0f + ((float)copy_u8Angle / 180.0f) * 5.0f;

    TMR1PWM_voidGenerate(50, local_f32Duty, _64FROM_PRESCALER);
    global_u8LastAngle = copy_u8Angle;
}
void SRV_voidOff()
{
	TMR1PWM_voidStop();
}