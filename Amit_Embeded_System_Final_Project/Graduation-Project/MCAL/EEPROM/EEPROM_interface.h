/*
 * EEPROM_interface.h
 *
 * Created: 12/12/2025 1:27:58 AM
 *  Author: mahmo
 */ 


#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

#include "STD_TYPES.h"

void EEPROM_voidInit();
void EEPROM_voidWriteByte(u16 copy_u16WordAdd, u8 copy_u8Data);
void EEPROM_voidReadByte(u16 copy_u16WordAdd, u8* copy_pu8Data);
void EEPROM_voidWritePage(u16 copy_u16WordAdd, u8* copy_u8PtrData, u8 copy_u8Length);
void EEPROM_voidReadPage(u16 copy_u16WordAdd, u8* copy_u8PtrDataOut, u8 copy_u8Length);

#endif /* EEPROM_INTERFACE_H_ */