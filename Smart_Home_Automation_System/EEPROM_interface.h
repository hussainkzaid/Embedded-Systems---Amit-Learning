/*
 * EEPROM_interface.h
 *
 * Created: 12/12/2025 1:27:58 AM
 *  Author: hussain zaid
 */ 


#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_


void EEPROM_voidInit();
void EEPROM_voidWriteByte(u16 copy_u16WordAdd, u8 copy_u8Data);
void EEPROM_voidReadByte(u16 copy_u16WordAdd, u8* copy_pu8Data);
void EEPROM_voidWritePage(u16 copy_u16WordAdd, u8*copy_u8Data, u8 copy_u8DataLength);
void EEPROM_voidReadPage(u16 copy_u16WordAdd, u8*copy_u8Data, u8 copy_u8DataLength);

#endif /* EEPROM_INTERFACE_H_ */