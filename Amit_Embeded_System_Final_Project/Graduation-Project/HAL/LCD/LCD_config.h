/*
 * LCD_config.h
 *
 * Created: 9/19/2025 9:27:15 PM
 *  Author: mahmo
 */ 


#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

// Macros for LCD mode configuration
#define LCD_MODE			4

// Macros for RS configuration
#define LCD_RS_PORT		DIO_PORTB
#define LCD_RS_PIN		DIO_PIN1

// Macros for Enable configuration
#define LCD_E_PORT		DIO_PORTB
#define LCD_E_PIN		DIO_PIN2

// Macros for data port 8_bit
#define LCD_DATA_PORT	DIO_PORTD

// Macors for data ports and pins 4_bit
#define LCD_D4_PORT			DIO_PORTA
#define LCD_D4_PIN			DIO_PIN4

#define LCD_D5_PORT			DIO_PORTA
#define LCD_D5_PIN			DIO_PIN5

#define LCD_D6_PORT			DIO_PORTA
#define LCD_D6_PIN			DIO_PIN6

#define LCD_D7_PORT			DIO_PORTA
#define LCD_D7_PIN			DIO_PIN7

#endif /* LCD_CONFIG_H_ */