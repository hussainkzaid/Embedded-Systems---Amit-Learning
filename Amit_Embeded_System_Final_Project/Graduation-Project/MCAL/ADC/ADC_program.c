/*
 * ADC_program.c
 *
 * Created: 10/11/2025 7:25:19 PM
 *  Author: mahmo
 */ 

#include "BIT_MATH.h"
#include "STD_TYPES.h"


#include "ADC_interface.h"
#include "ADC_register.h"


// APIs ProtoTypes
void ADC_voidInit(ADC_reference_t copy_tRefVolt)
{
		/* Clear reference selection bits (bit 6 and 7) */
		ADMUX_REG &= 0b00111111;
		/* Set reference selection bits */
		ADMUX_REG |= (copy_tRefVolt << 6);
		/* Enable ADC and set prescaler to 128 */
		ADCSRA_REG = 0b10000111;
}

void ADC_voidGetDigitalValue(ADC_channelId_t copy_tChannelId, u16* pu16DigitalValue )
{
	if((copy_tChannelId < 32) && (pu16DigitalValue != NULL))
	{
		ADMUX_REG = (ADMUX_REG & 0b11100000) | copy_tChannelId;
		SET_BIT(ADCSRA_REG, 6);
		while(!GET_BIT(ADCSRA_REG, 4));
		*pu16DigitalValue = ADCDATA_REG;
		CLR_BIT(ADCSRA_REG, 4);
	}
	else
	{
		// return error state
	}
}