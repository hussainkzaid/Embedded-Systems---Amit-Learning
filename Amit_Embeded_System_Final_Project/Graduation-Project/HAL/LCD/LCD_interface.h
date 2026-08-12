/*
 * LCD_interface.h
 *
 * Created: 9/19/2025 9:27:29 PM
 *  Author: mahmo
 */ 


#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_


// Macros for shift direction
#define LCD_SHIFT_LEFT			1
#define LCD_SHIFT_RIGHT			2

// Macros for line number 
#define LCD_LINE_ONE			1
#define LCD_LINE_TWO			2

// APIs Prototypes

void LCD_voidInit(void);
void LCD_voidDisplayChar(u8 copy_u8Data);
void LCD_voidDisplayString(u8* pu8String);
void LCD_voidDisplayNumber(u8 copy_u8Number);
void LCD_voidSendCommand(u8 copy_u8Command);
void LCD_voidClear(void);
void LCD_voidShift(u8 copy_u8ShiftingDirection);
void LCD_voidGoToStartPosition(void);
void LCD_voidGoToSpecificPosition(u8 copy_u8LineNumber, u8 copy_u8Position);




#endif /* LCD_INTERFACE_H_ */