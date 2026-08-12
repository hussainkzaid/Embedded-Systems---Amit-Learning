/*
 * LCD_program.c
 *
 * Created: 9/19/2025 9:27:44 PM
 *  Author: mahmo
 */ 


// Utils Lib
#include "STD_TYPES.h"
#include "BIT_MATH.h"

// MCAL
#include "DIO_interface.h"
#include "DIO_register.h"

// HAL
#include "LCD_config.h"
#include "LCD_interface.h"
#include "LCD_private.h"


#define F_CPU 16000000UL
#include <util/delay.h>

void LCD_voidInit(void)
{
	DIO_voidSetPinDirection(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_E_PORT, LCD_E_PIN, DIO_PIN_OUTPUT);

	#if LCD_MODE == LCD_8_BIT_MODE
	DIO_voidSetPortDirection(LCD_DATA_PORT, DIO_PORT_OUTPUT);
	
	_delay_ms(40);
	
	// function set (8-bit, 2 lines, 5x7)
	LCD_voidSendCommand(0b00111000);
	_delay_us(45);
	
	#elif LCD_MODE == LCD_4_BIT_MODE
	// Set directions for D4�D7
	DIO_voidSetPinDirection(LCD_D4_PORT, LCD_D4_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_D5_PORT, LCD_D5_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_D6_PORT, LCD_D6_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_D7_PORT, LCD_D7_PIN, DIO_PIN_OUTPUT);
	
	_delay_ms(40);

	DIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_LOW);
	
	DIO_voidSetPinValue(LCD_D4_PORT, LCD_D4_PIN, DIO_PIN_LOW);
	DIO_voidSetPinValue(LCD_D5_PORT, LCD_D5_PIN, DIO_PIN_HIGH);
	DIO_voidSetPinValue(LCD_D6_PORT, LCD_D6_PIN, DIO_PIN_LOW);
	DIO_voidSetPinValue(LCD_D7_PORT, LCD_D7_PIN, DIO_PIN_LOW);
	PRV_voidEnableTriggerWrite();

	// function set: 4-bit, 2 lines, 5x7
	LCD_voidSendCommand(0b00101000);
	_delay_us(45);
	#endif
	
	// display ON, cursor ON, blink ON
	LCD_voidSendCommand(0b00001111);
	_delay_us(45);
	
	// display clear
	LCD_voidSendCommand(0b00000001);
	_delay_ms(2);
	
	// entry mode set (increment on, shift off)
	LCD_voidSendCommand(0b00000110);
	_delay_ms(2);
}


void LCD_voidSendCommand(u8 copy_u8Command)
{
	#if LCD_MODE == LCD_8_BIT_MODE
	// Set RS pin = 0 (command)
	DIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_LOW);
	
	// Writes bits of command on data pins
	DIO_voidSetPortValue(LCD_DATA_PORT, copy_u8Command);
	
	// enable
	PRV_voidEnableTriggerWrite();
	#elif LCD_MODE == LCD_4_BIT_MODE
	// RS = 0 ? command mode
	DIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_LOW);
	// RW = 0 ? write
	DIO_voidSetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_PIN_LOW);

	// send high nibble
	DIO_voidSetPinValue(LCD_D4_PORT, LCD_D4_PIN, GET_BIT(copy_u8Command, 4));
	DIO_voidSetPinValue(LCD_D5_PORT, LCD_D5_PIN, GET_BIT(copy_u8Command, 5));
	DIO_voidSetPinValue(LCD_D6_PORT, LCD_D6_PIN, GET_BIT(copy_u8Command, 6));
	DIO_voidSetPinValue(LCD_D7_PORT, LCD_D7_PIN, GET_BIT(copy_u8Command, 7));
	PRV_voidEnableTriggerWrite();

	// send low nibble
	DIO_voidSetPinValue(LCD_D4_PORT, LCD_D4_PIN, GET_BIT(copy_u8Command, 0));
	DIO_voidSetPinValue(LCD_D5_PORT, LCD_D5_PIN, GET_BIT(copy_u8Command, 1));
	DIO_voidSetPinValue(LCD_D6_PORT, LCD_D6_PIN, GET_BIT(copy_u8Command, 2));
	DIO_voidSetPinValue(LCD_D7_PORT, LCD_D7_PIN, GET_BIT(copy_u8Command, 3));
	PRV_voidEnableTriggerWrite();

	#endif
	
}


static void PRV_voidEnableTriggerWrite()
{
	DIO_voidSetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_voidSetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_PIN_LOW);
}


void LCD_voidDisplayChar(u8 copy_u8Data)
{
	// Set RS pin = 1 (char)
	DIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_HIGH);
	#if LCD_MODE == LCD_8_BIT_MODE
	
	// Writes bits of command on data pins
	DIO_voidSetPortValue(LCD_DATA_PORT, copy_u8Data);
	// enable
	PRV_voidEnableTriggerWrite();
	
	#elif LCD_MODE == LCD_4_BIT_MODE
	/* way 1
	DIO_voidSetPortValue(LCD_DATA_PORT, (PORTA_REG & 0x0f) | (copy_u8Data & 0xf0));
	PRV_voidEnableTriggerWrite();
	DIO_voidSetPortValue(LCD_DATA_PORT, (PORTA_REG & 0x0f) | ((copy_u8Data & 0x0f) << 4));
	PRV_voidEnableTriggerWrite();
	*/
	// way 2
	DIO_voidSetPinValue(LCD_D4_PORT, LCD_D4_PIN, GET_BIT(copy_u8Data, 4));
	DIO_voidSetPinValue(LCD_D5_PORT, LCD_D5_PIN, GET_BIT(copy_u8Data, 5));
	DIO_voidSetPinValue(LCD_D6_PORT, LCD_D6_PIN, GET_BIT(copy_u8Data, 6));
	DIO_voidSetPinValue(LCD_D7_PORT, LCD_D7_PIN, GET_BIT(copy_u8Data, 7));
	PRV_voidEnableTriggerWrite();
	DIO_voidSetPinValue(LCD_D4_PORT, LCD_D4_PIN, GET_BIT(copy_u8Data, 0));
	DIO_voidSetPinValue(LCD_D5_PORT, LCD_D5_PIN, GET_BIT(copy_u8Data, 1));
	DIO_voidSetPinValue(LCD_D6_PORT, LCD_D6_PIN, GET_BIT(copy_u8Data, 2));
	DIO_voidSetPinValue(LCD_D7_PORT, LCD_D7_PIN, GET_BIT(copy_u8Data, 3));
	PRV_voidEnableTriggerWrite();
	#endif
}

void LCD_voidDisplayString(u8* pu8String)
{
	u8 local_u8Counter = 0;
	while(*(pu8String+local_u8Counter) != '\0')
	{
		LCD_voidDisplayChar(*(pu8String+local_u8Counter));
		local_u8Counter++;
	}
}

void LCD_voidDisplayNumber(u8 copy_u8Number)
{
	u32 tempNumber = copy_u8Number;
	u8 local_u8NumberLength = 1;

	while ((tempNumber / 10) != 0)
	{
		local_u8NumberLength++;
		tempNumber /= 10;
	}

	u8 local_u8NumberDigits[local_u8NumberLength];
	u8 local_u8Index = 0;
	tempNumber = copy_u8Number;

	while (tempNumber != 0)
	{
		local_u8NumberDigits[local_u8Index] = (tempNumber % 10) + '0';
		tempNumber /= 10;
		local_u8Index++;
	}

	if (copy_u8Number == 0)
	{
		LCD_voidDisplayChar('0');
		return;
	}

	for (s8 i = local_u8NumberLength - 1; i >= 0; i--)
	{
		LCD_voidDisplayChar(local_u8NumberDigits[i]);
	}
}


void LCD_voidClear(void)
{
	LCD_voidSendCommand(0b00000001);
	_delay_ms(2);
}

void LCD_voidShift(u8 copy_u8ShiftingDirection)
{
	switch (copy_u8ShiftingDirection)
	{
		case LCD_SHIFT_LEFT:
			LCD_voidSendCommand(0b00011000);
			break;
		case LCD_SHIFT_RIGHT:
			LCD_voidSendCommand(0b00011100);
			break;
	}
	_delay_us(50);
}

void LCD_voidGoToStartPosition(void)
{
	LCD_voidSendCommand(0b00000010);
	_delay_us(50);
}

void LCD_voidGoToSpecificPosition(u8 copy_u8LineNumber, u8 copy_u8Position)
{

	switch (copy_u8LineNumber)
	{
		case LCD_LINE_ONE:
			LCD_voidSendCommand(0x80+copy_u8Position);
			break;
		case LCD_LINE_TWO:
			LCD_voidSendCommand(0xc0+copy_u8Position);
			break;
	}
	_delay_us(50);
}
