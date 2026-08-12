/*
 * EEPROM_program.c
 *
 * Created: 12/12/2025 1:27:45 AM
 *  Author: mahmo
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "TWI_interface.h"

#include "EEPROM_interface.h"

void EEPROM_voidInit()
{
	TWI_voidInitMaster();
}

void EEPROM_voidWriteByte(u16 copy_u16WordAdd, u8 copy_u8Data)
{
	u8 local_u8BaseAdd = 0b01010000 | (copy_u16WordAdd >> 8);
	
	//Start Condition
	TWI_voidSendStartCond();
	
	//Slave Address + Write
	TWI_voidSendSlaveAddW(local_u8BaseAdd);
	
	//Send Low Address Byte
	TWI_voidTxMasterByte((u8)copy_u16WordAdd);
	
	//Send Data Byte
	TWI_voidTxMasterByte(copy_u8Data);
	
	//Stop Condition
	TWI_voidSendStopCond();
	
	_delay_ms(5);
}


void EEPROM_voidReadByte(u16 copy_u16WordAdd, u8* copy_pu8Data)
{
	if (copy_pu8Data != NULL)
	{
		u8 local_u8BaseAdd = 0b01010000 | (copy_u16WordAdd >> 8);
		
		//Start Condition
		TWI_voidSendStartCond();
		
		//Slave Address + Write
		TWI_voidSendSlaveAddW(local_u8BaseAdd);
		
		//Send Low Address Byte
		TWI_voidTxMasterByte((u8)copy_u16WordAdd);
		
		//Repeated Start Condition
		TWI_voidSendRepStartCond();
		
		//Slave Address + Read
		TWI_voidSendSlaveAddR(local_u8BaseAdd);
		
		//Read Data Byte (STOP CONDITION INSIDE)
		TWI_voidRxMasterByteNACK(copy_pu8Data);
		
		_delay_ms(5);
	}
	else
	{
		//return Error State
	}
}

void EEPROM_voidWritePage(u16 copy_u16WordAdd, u8* copy_u8PtrData, u8 copy_u8Length)
{
	u8 local_u8BaseAdd = 0b01010000 | (copy_u16WordAdd >> 8);

	TWI_voidSendStartCond();
	TWI_voidSendSlaveAddW(local_u8BaseAdd);

	TWI_voidTxMasterByte((u8)copy_u16WordAdd);

	u8 local_u8Counter = 0;
	for(local_u8Counter = 0; local_u8Counter < copy_u8Length; local_u8Counter++)
		TWI_voidTxMasterByte(*(copy_u8PtrData + local_u8Counter));

	TWI_voidSendStopCond();

	_delay_ms(5);
}


void EEPROM_voidReadPage(u16 copy_u16WordAdd, u8* copy_u8PtrDataOut, u8 copy_u8Length)
{
	u8 local_u8BaseAdd = 0b01010000 | (copy_u16WordAdd >> 8);

	TWI_voidSendStartCond();
	
	TWI_voidSendSlaveAddW(local_u8BaseAdd);
	TWI_voidTxMasterByte((u8)copy_u16WordAdd);

	TWI_voidSendRepStartCond();
	TWI_voidSendSlaveAddR(local_u8BaseAdd);

	u8 local_u8Counter = 0;
	for(local_u8Counter = 0; local_u8Counter < copy_u8Length - 1; local_u8Counter++)
	TWI_voidRxMasterByteACK(copy_u8PtrDataOut + local_u8Counter);

	TWI_voidRxMasterByteNACK(copy_u8PtrDataOut + copy_u8Length - 1);
	TWI_voidSendStopCond();
	
	_delay_ms(5);
}
