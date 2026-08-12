/*
 * DCM_config.h
 *
 * Created: 10/31/2025 8:41:45 PM
 *  Author: mahmo
 */ 


#ifndef DCM_CONFIG_H_
#define DCM_CONFIG_H_


// Motor A control pins
#define DCM_IN1_PORT     DIO_PORTC
#define DCM_IN1_PIN      DIO_PIN3
#define DCM_IN2_PORT     DIO_PORTC
#define DCM_IN2_PIN      DIO_PIN4
// FOR ac
//#define DCM_ENA_PORT     DIO_PORTB
//#define DCM_ENA_PIN      DIO_PIN3
#define DCM_ENA_PORT     DIO_PORTC
#define DCM_ENA_PIN      DIO_PIN5

// Motor B control pins
#define DCM_IN3_PORT     DIO_PORTC
#define DCM_IN3_PIN      DIO_PIN5
#define DCM_IN4_PORT     DIO_PORTC
#define DCM_IN4_PIN      DIO_PIN6
#define DCM_ENB_PORT     DIO_PORTD
#define DCM_ENB_PIN      DIO_PIN4


#endif /* DCM_CONFIG_H_ */