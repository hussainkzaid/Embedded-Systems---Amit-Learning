/*
 * KPD_interface.h
 *
 * Created: 9/27/2025 6:57:06 PM
 *  Author: mahmo
 */ 


#ifndef KPD_INTERFACE_H_
#define KPD_INTERFACE_H_

#define KPD_NOT_PRESSED			0xff

// keypad macros
#define NUMBER_OF_COLUMNS		3
#define NUMBER_OF_ROWS			3

// keypad prototypes
void KPD_voidInit(void);
void KPD_voidGetValue(u8* pu8PressedValue);



#endif /* KPD_INTERFACE_H_ */