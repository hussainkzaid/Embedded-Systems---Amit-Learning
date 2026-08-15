/*
 * KPD_config.h
 *
 * Created: 10/2/2025 6:52:48 PM
 *  Author: hussain zaid
 */ 


#ifndef KPD_CONFIG_H_
#define KPD_CONFIG_H_

#define KPD_NUMBER_OF_ROWS		4
#define KPD_NUMBER_OF_COLS		3
						
						/* MACROS FOR KPD ROWS PORTS & PINS CONFIGURATION */
#define KPD_ROW0_PORT		DIO_PORTA
#define KPD_ROW0_PIN		DIO_PIN0
	
#define KPD_ROW1_PORT		DIO_PORTA
#define KPD_ROW1_PIN		DIO_PIN1
	
#define KPD_ROW2_PORT		DIO_PORTA
#define KPD_ROW2_PIN		DIO_PIN2

#define KPD_ROW3_PORT		DIO_PORTA
#define KPD_ROW3_PIN		DIO_PIN3
						
						/* MACROS FOR KPD COLUMNS PORTS & PINS CONFIGURATION */
#define KPD_COL0_PORT		DIO_PORTD
#define KPD_COL0_PIN		DIO_PIN0
		
#define KPD_COL1_PORT		DIO_PORTD
#define KPD_COL1_PIN		DIO_PIN1
		
#define KPD_COL2_PORT		DIO_PORTD
#define KPD_COL2_PIN		DIO_PIN2

//Keypad Mapping
#define KPD_KEYS	   {{'1','2','3'},\
						{'4','5','6'},\
						{'7','8','9'},\
						{'*','0','#'}}
	
#endif /* KPD_CONFIG_H_ */