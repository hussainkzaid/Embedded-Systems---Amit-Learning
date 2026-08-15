/*
 * LCD_program.c
 *
 * Created: 9/25/2025 9:15:35 PM
 *  Author: hussain zaid
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>

//UTILSE_LIB
#include "BIT_MATH.h"
#include "STD_TYPES.h"

//MCAL
#include "DIO_interface.h"

//HAL
#include "LCD_config.h"
#include "LCD_interface.h"
#include "LCD_private.h"

void LCD_voidInit(void){
	DIO_voidSetPinDirection(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_E_PORT, LCD_E_PIN, DIO_PIN_OUTPUT);
	
	#if LCD_MODE == LCD_8_BIT_MODE
	
		DIO_voidSetPortDirection(LCD_DATA_PORT, DIO_PORT_OUTPUT);
	
		_delay_ms(40);
	
		//Function Set (2 Lines, 5*7 Font)
		LCD_voidSendCommand(0b00111000);
		_delay_us(45);
		
	#elif LCD_MODE == LCD_4_BIT_MODE
		//Set Pins Direction For D4-D7
		DIO_voidSetPinDirection(LCD_D4_PORT, LCD_D4_PIN, DIO_PIN_OUTPUT);
		DIO_voidSetPinDirection(LCD_D5_PORT, LCD_D5_PIN, DIO_PIN_OUTPUT);
		DIO_voidSetPinDirection(LCD_D6_PORT, LCD_D6_PIN, DIO_PIN_OUTPUT);
		DIO_voidSetPinDirection(LCD_D7_PORT, LCD_D7_PIN, DIO_PIN_OUTPUT);
		
		_delay_ms(40);
		
		//Set Rs Pin = 0 (Command)
		DIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_LOW);
		
		//Command
		DIO_voidSetPinValue(LCD_D4_PORT, LCD_D4_PIN, 0);
		DIO_voidSetPinValue(LCD_D5_PORT, LCD_D5_PIN, 1);
		DIO_voidSetPinValue(LCD_D6_PORT, LCD_D6_PIN, 0);
		DIO_voidSetPinValue(LCD_D7_PORT, LCD_D7_PIN, 0);
		
		//Enable
		PRV_voidEnableTriggerWrite();
		
		LCD_voidSendCommand(0b00101000);
		_delay_us(45);
		
	#endif
	
	//Display On/Off Control (Display On, Cursor On, Blink On)
	LCD_voidSendCommand(0b00001111);
	_delay_us(45);
	
	//Display Clear
	LCD_voidSendCommand(0b00000001);
	_delay_ms(2);
	
	//Entry Mode Set (Increment On, Shift Off)
	LCD_voidSendCommand(0b00000110);
}


void LCD_voidDisplayChar(u8 copy_u8Data){
	//Set Rs Pin = 1 (Data)
	DIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_HIGH);
	
	#if LCD_MODE == LCD_8_BIT_MODE
	
		//Write Bits Of Character(Data) On Data Pins
		DIO_voidSetPortValue(LCD_DATA_PORT, copy_u8Data);
		//Enable
		PRV_voidEnableTriggerWrite();
		
	#elif LCD_MODE == LCD_4_BIT_MODE
	
	u8 local_u8MSB = copy_u8Data & 0b11110000;
	u8 local_u8LSB = (copy_u8Data & 0b00001111) << 4;
	
		PRV_voidSet4BitsLcdPins(local_u8MSB);
		PRV_voidEnableTriggerWrite();
		
		PRV_voidSet4BitsLcdPins(local_u8LSB);
		PRV_voidEnableTriggerWrite();
	
	#endif
}


void LCD_voidSendCommand(u8 copy_u8Cmnd){
	//Set Rs Pin = 0 (Command)
	DIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_LOW);
	
	#if LCD_MODE == LCD_8_BIT_MODE
	
		//Write Bits Of Command On Data Pins
		DIO_voidSetPortValue(LCD_DATA_PORT, copy_u8Cmnd);
		//Enable
		PRV_voidEnableTriggerWrite();
	
	#elif LCD_MODE == LCD_4_BIT_MODE
	
		u8 local_u8MSB = copy_u8Cmnd & 0b11110000;
		u8 local_u8LSB = (copy_u8Cmnd & 0b00001111) << 4;
	
		PRV_voidSet4BitsLcdPins(local_u8MSB);
		PRV_voidEnableTriggerWrite();
	
		PRV_voidSet4BitsLcdPins(local_u8LSB);
		PRV_voidEnableTriggerWrite();
	
	#endif
}


void LCD_voidDisplayString(u8* copy_pu8String){
	u8 local_u8Counter= 0;
	if(copy_pu8String != NULL){
		
		while(copy_pu8String[local_u8Counter] != '\0'){
			LCD_voidDisplayChar(copy_pu8String[local_u8Counter]);
			local_u8Counter++;
		}
	}
}


void LCD_voidClear(void){
	LCD_voidSendCommand(0b00000001);
	_delay_ms(2);
}


void LCD_voidShift(u8 copy_u8ShifttingDirection){
	switch(copy_u8ShifttingDirection)
	{
		case LCD_SHIFT_RIGHT:
		LCD_voidSendCommand(0b00011100);
		_delay_us(45);
		break;
		
		case LCD_SHIFT_LEFT:
		LCD_voidSendCommand(0b00011000);
		_delay_us(45);
		break;
	}
}


void LCD_voidGoToSpecificPosition(u8 copy_u8LineNumber, u8 copy_u8Position){
	switch(copy_u8LineNumber)
	{
		case LCD_LINE_ONE:
		LCD_voidSendCommand(0b10000000 + copy_u8Position); // 0x80 + Pos
		_delay_us(45);
		break;
		
		case LCD_LINE_TWO:
		LCD_voidSendCommand(0b11000000 + copy_u8Position); // 0xC0 + Pos
		_delay_us(45);
		break;
	}
}


void LCD_voidGoToStartPosition(void){
	LCD_voidSendCommand(0b00000010);
	_delay_us(45);
}


void LCD_voidDisplayNumber(s32 copy_s32Number){
	u8 buffer[11];   
	u8 counter = 0;

	// Handle zero directly (saves loop)
	if(copy_s32Number == 0){
		LCD_voidDisplayChar('0');
		return;
	}

	// Handle negative
	if(copy_s32Number < 0){
		LCD_voidDisplayChar('-');
		copy_s32Number = -copy_s32Number;
	}

	// Convert number into buffer (reversed order)
	while(copy_s32Number > 0){
		buffer[counter++] = (copy_s32Number % 10) + '0';
		copy_s32Number /= 10;
	}

	// Print buffer in reverse
	while(counter > 0){
		LCD_voidDisplayChar(buffer[--counter]);
	}
}


static void PRV_voidEnableTriggerWrite(void){
	//Enable(H -> L)
	DIO_voidSetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_voidSetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_PIN_LOW);
}


static void PRV_voidSet4BitsLcdPins(u8 copy_u8_4_BitsValue){
	GET_BIT(copy_u8_4_BitsValue,DIO_PIN4) ? DIO_voidSetPinValue(LCD_D4_PORT, LCD_D4_PIN, DIO_PIN_HIGH) : DIO_voidSetPinValue(LCD_D4_PORT, LCD_D4_PIN, DIO_PIN_LOW);
	GET_BIT(copy_u8_4_BitsValue,DIO_PIN5) ? DIO_voidSetPinValue(LCD_D5_PORT, LCD_D5_PIN, DIO_PIN_HIGH) : DIO_voidSetPinValue(LCD_D5_PORT, LCD_D5_PIN, DIO_PIN_LOW);
	GET_BIT(copy_u8_4_BitsValue,DIO_PIN6) ? DIO_voidSetPinValue(LCD_D6_PORT, LCD_D6_PIN, DIO_PIN_HIGH) : DIO_voidSetPinValue(LCD_D6_PORT, LCD_D6_PIN, DIO_PIN_LOW);
	GET_BIT(copy_u8_4_BitsValue,DIO_PIN7) ? DIO_voidSetPinValue(LCD_D7_PORT, LCD_D7_PIN, DIO_PIN_HIGH) : DIO_voidSetPinValue(LCD_D7_PORT, LCD_D7_PIN, DIO_PIN_LOW);
}