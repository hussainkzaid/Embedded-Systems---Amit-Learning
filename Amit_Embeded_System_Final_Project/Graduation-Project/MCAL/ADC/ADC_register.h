/*
 * ADC_register.h
 *
 * Created: 10/11/2025 7:26:37 PM
 *  Author: mahmo
 */ 


#ifndef ADC_REGISTER_H_
#define ADC_REGISTER_H_

#define ADMUX_REG		*((volatile u8*)0x27)
#define ADCSRA_REG		*((volatile u8*)0x26)
#define ADCDATA_REG		*((volatile u16*)0x24)


#endif /* ADC_REGISTER_H_ */