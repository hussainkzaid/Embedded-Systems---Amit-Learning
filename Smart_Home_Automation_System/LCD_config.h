/*
 * LCD_config.h
 *
 * Created: 9/25/2025 9:15:57 PM
 *  Author: hussain zaid
 */ 


#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

/* Option For LCD Mode
1- LCD_8_BIT_MODE
2- LCD_4_BIT_MODE
*/
#define LCD_MODE		LCD_4_BIT_MODE

//Macros For RS Configuration
#define LCD_RS_PORT		DIO_PORTB
#define LCD_RS_PIN		DIO_PIN1

//Macros For Data Port 8_bit
#define LCD_DATA_PORT		DIO_PORTD

//Macros For Enable Configuration
#define LCD_E_PORT		DIO_PORTB	
#define LCD_E_PIN		DIO_PIN2

//Macros For Data Port & Pins 4_b
#define LCD_D4_PORT		DIO_PORTA
#define LCD_D4_PIN		DIO_PIN4

#define LCD_D5_PORT		DIO_PORTA
#define LCD_D5_PIN		DIO_PIN5

#define LCD_D6_PORT		DIO_PORTA
#define LCD_D6_PIN		DIO_PIN6

#define LCD_D7_PORT		DIO_PORTA
#define LCD_D7_PIN		DIO_PIN7

#endif /* LCD_CONFIG_H_ */