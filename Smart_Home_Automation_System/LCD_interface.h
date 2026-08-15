/*
 * LCD_interface.h
 *
 * Created: 9/25/2025 9:15:46 PM
 *  Author: hussain zaid
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

//Macros For Shift Direction
#define LCD_SHIFT_LEFT		1
#define LCD_SHIFT_RIGHT		2

//Macros For Line Number and position will be from 0 to 15
#define  LCD_LINE_ONE		1
#define  LCD_LINE_TWO		2

/*************************************************** APIs Prototypes ***************************************************/
void LCD_voidInit(void);

void LCD_voidDisplayChar(u8 copy_u8Data);
void LCD_voidSendCommand(u8 copy_u8Cmnd);
void LCD_voidDisplayString(u8* copy_pu8String);
void LCD_voidDisplayNumber(s32 copy_s32Number);
void LCD_voidClear(void);
void LCD_voidShift(u8 copy_u8ShifttingDirection);
void LCD_voidGoToSpecificPosition(u8 copy_u8LineNumber, u8 copy_u8Position);
void LCD_voidGoToStartPosition(void);


#endif /* LCD_INTERFACE_H_ */