/*
 * LCD_private.h
 *
 * Created: 9/25/2025 9:16:08 PM
 *  Author: hussain zaid
 */ 


#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_

//Macros For Connection Type
#define LCD_8_BIT_MODE		1
#define LCD_4_BIT_MODE		2

static void PRV_voidEnableTriggerWrite(void);

static void PRV_voidSet4BitsLcdPins(u8 bitsValue);


#endif /* LCD_PRIVATE_H_ */