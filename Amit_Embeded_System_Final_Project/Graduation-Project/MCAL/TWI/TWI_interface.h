/*
 * TWI_interface.h
 *
 * Created: 12/11/2025 2:52:16 PM
 *  Author: hussain zaid
 */ 


#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

#include "STD_TYPES.h"

//Master
void TWI_voidInitMaster();
void TWI_voidSendStartCond();
void TWI_voidSendRepStartCond();
void TWI_voidSendStopCond();
void TWI_voidSendSlaveAddW(u8 copy_u8SlaveAdd);
void TWI_voidSendSlaveAddR(u8 copy_u8SlaveAdd);
void TWI_voidTxMasterByte(u8 copy_u8DataTransmit);
void TWI_voidRxMasterByteACK(u8* copy_u8DataReceived);
void TWI_voidRxMasterByteNACK(u8* copy_u8DataReceived);

//Slave
void TWI_voidInitSlave(u8 copy_u8SlaveAddress);
void TWI_voidSlaveListen();
void TWI_voidTxSlaveByte(u8 copy_u8DataTransmit);
void TWI_voidRxSlaveByteACK(u8* copy_u8DataReceived);
void TWI_voidRxSlaveByteNACK(u8* copy_u8DataReceived);



#endif /* TWI_INTERFACE_H_ */