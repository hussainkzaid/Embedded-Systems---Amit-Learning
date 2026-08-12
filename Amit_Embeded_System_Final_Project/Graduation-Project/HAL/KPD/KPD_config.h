/*
 * KPD_config.h
 *
 * Created: 9/27/2025 6:58:13 PM
 *  Author: mahmo
 */ 


#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_

// Macros for keypad columns
#define KPD_COLUMN_ZERO_PORT		DIO_PORTD
#define KPD_COLUMN_ZERO_PIN			DIO_PIN2

#define KPD_COLUMN_ONE_PORT			DIO_PORTD
#define KPD_COLUMN_ONE_PIN			DIO_PIN3

#define KPD_COLUMN_TWO_PORT			DIO_PORTD
#define KPD_COLUMN_TWO_PIN			DIO_PIN7


// Macros for keypad rows
#define KPD_ROW_ZERO_PORT			DIO_PORTA
#define KPD_ROW_ZERO_PIN			DIO_PIN1

#define KPD_ROW_ONE_PORT			DIO_PORTA
#define KPD_ROW_ONE_PIN				DIO_PIN2

#define KPD_ROW_TWO_PORT			DIO_PORTA
#define KPD_ROW_TWO_PIN				DIO_PIN3

// macro for keypad keys
#define KPD_KEYS					{{'1', '2', '3'},\
									{'4', '5', '6'},\
									{'7', '8', 'c'}}
	



#endif /* KPD_CONFIG_H_ */