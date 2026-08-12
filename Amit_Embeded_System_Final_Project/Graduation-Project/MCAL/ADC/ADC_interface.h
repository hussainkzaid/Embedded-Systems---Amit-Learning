/*
 * ADC_interface.h
 *
 * Created: 10/11/2025 7:25:37 PM
 *  Author: mahmo
 */ 


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_


// enum for reference voltage
typedef enum
{
	ADC_REFERENCE_AREF,
	ADC_REFERENCE_AVCC,
	ADC_REFERENCE_RESERVED,
	ADC_REFERENCE_INTERNAL,
} ADC_reference_t;


// enum for targeted channel
typedef enum
{
	ADC_CHANNEL_0,
	ADC_CHANNEL_1,
	ADC_CHANNEL_2,
	ADC_CHANNEL_3,
	ADC_CHANNEL_4,
	ADC_CHANNEL_5,
	ADC_CHANNEL_6,
	ADC_CHANNEL_7,
} ADC_channelId_t;

// APIs ProtoTypes
void ADC_voidInit(ADC_reference_t copy_tRefVolt);
void ADC_voidGetDigitalValue(ADC_channelId_t copy_tChannelId, u16* pu16DigitalValue );


#endif /* ADC_INTERFACE_H_ */