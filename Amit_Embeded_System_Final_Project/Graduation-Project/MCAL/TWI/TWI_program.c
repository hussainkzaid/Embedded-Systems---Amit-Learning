/*
 * TWI_program.c
 *
 * Created: 12/11/2025 2:52:02 PM
 *  Author: hussain zaid
 */ 

//UTILSE_LIB
#include "BIT_MATH.h"
#include "STD_TYPES.h"

//MCAL
#include "TWI_interface.h"
#include "TWI_private.h"
#include "TWI_register.h"

//clear the flag is like enable
void TWI_voidInitMaster()
{
	//Set Prtscaller = 1, SCL frequency = 400KHZ
	TWBR_REG = 12;
	CLR_BIT(TWSR_REG, TWPS1);
	CLR_BIT(TWSR_REG, TWPS0);
	
	//Disable Interrupt, Disable ACK For Master
	CLR_BIT(TWCR_REG, TWIE);
	CLR_BIT(TWCR_REG, TWEA);
	
	//Enable TWI
	SET_BIT(TWCR_REG, TWEN);
}


void TWI_voidSendStartCond()
{
	//START Condition
	SET_BIT(TWCR_REG, TWSTA);
	
	//Clear Flag to start current job (write one to clear)
	SET_BIT(TWCR_REG, TWINT);

	//Busy wait for flag
	while(GET_BIT(TWCR_REG, TWINT) == 0);
	//Check Status code = start condition status code
	while(TWI_STATUS_VALUE != 0x08);
}


void TWI_voidSendRepStartCond()
{
	//Start Condition
	SET_BIT(TWCR_REG, TWSTA);
	
	//Clear Flag to start current job (write one to clear)
	SET_BIT(TWCR_REG, TWINT); 
	
	//Busy wait for flag
	while(GET_BIT(TWCR_REG, TWINT) == 0);
	//Check Status code 
	while(TWI_STATUS_VALUE != 0x10);
}


void TWI_voidSendStopCond()
{
	//Clear Flag to start current job (write one to clear)
	SET_BIT(TWCR_REG, TWINT);
	
	//Stop Condition
	SET_BIT(TWCR_REG, TWSTO);
}


void TWI_voidSendSlaveAddW(u8 copy_u8SlaveAdd)
{
	if(copy_u8SlaveAdd < 128)
	{
		//Write Slave Address to SDA bus
		TWDR_REG = (copy_u8SlaveAdd << 1); //THE LSB BIT(R/W BIT) IS WRITE -> 0
		
		//Clear Start
		CLR_BIT(TWCR_REG, TWSTA);
		
		//Clear Flag to start current job (write one to clear)
		SET_BIT(TWCR_REG, TWINT);
		
		//Note: Clearing TWSTA AND TWINT IS LIKE ENABLES
		
		//Busy wait for flag
		while(GET_BIT(TWCR_REG, TWINT) == 0);
		//Check Status code
		while(TWI_STATUS_VALUE != 0x18);
	}
	else
	{
		//return Error State
	}
}


void TWI_voidSendSlaveAddR(u8 copy_u8SlaveAdd)
{
	if(copy_u8SlaveAdd < 128)
	{
		//Write Slave Address to SDA bus
		TWDR_REG = (copy_u8SlaveAdd << 1) | 1; //THE LSB BIT(R/W BIT) IS READ -> 1
		
		//Clear Start
		CLR_BIT(TWCR_REG, TWSTA);
		
		//Clear Flag to start current job (write one to clear)
		SET_BIT(TWCR_REG, TWINT);
		
		//Note: Clearing TWSTA AND TWINT IS LIKE ENABLES
		
		//Busy wait for flag
		while(GET_BIT(TWCR_REG, TWINT) == 0);
		//Check Status code
		while(TWI_STATUS_VALUE != 0x40);
	}
	else
	{
		//return Error State
	}
}


void TWI_voidTxMasterByte(u8 copy_u8DataTransmit)
{
	//Write Data on SDA bus
	TWDR_REG = copy_u8DataTransmit;
	
	//Clear Flag to start current job (write one to clear)
	SET_BIT(TWCR_REG, TWINT);
	
	//Busy wait for flag
	while(GET_BIT(TWCR_REG, TWINT) == 0);
	//Check Status code
	while(TWI_STATUS_VALUE!= 0x28);
}


void TWI_voidRxMasterByteACK(u8* copy_u8DataReceived)
{
	if (copy_u8DataReceived != NULL)
	{
		//Enable ACK
		SET_BIT(TWCR_REG, TWEA);
		
		//Clear Flag to start current job (write one to clear)
		SET_BIT(TWCR_REG, TWINT);
		
		//Busy wait for flag
		while(GET_BIT(TWCR_REG, TWINT) == 0);
		//Check Status code
		while(TWI_STATUS_VALUE != 0x50);
		
		//Pass Out Received Data
		*copy_u8DataReceived = TWDR_REG;
		
		//Disable ACK
		CLR_BIT(TWCR_REG, TWEA);
	}
	else
	{
		//return Error State
	}
}


void TWI_voidRxMasterByteNACK(u8* copy_u8DataReceived)
{
	if (copy_u8DataReceived != NULL)
	{
		//Clear Flag to start current job (write one to clear)
		SET_BIT(TWCR_REG, TWINT);
		
		//Busy wait for flag
		while(GET_BIT(TWCR_REG, TWINT) == 0);
		//Check Status code
		while(TWI_STATUS_VALUE != 0x58);
		
		//Pass Out Received Data
		*copy_u8DataReceived = TWDR_REG;
		
		TWI_voidSendStopCond();
	}
	else
	{
		//return Error State
	}
}




void TWI_voidInitSlave(u8 copy_u8SlaveAddress)
{
	SET_BIT(TWCR_REG, TWEA);
	SET_BIT(TWCR_REG, TWEN);
	
	TWAR_REG = copy_u8SlaveAddress<<1;
}


void TWI_voidSlaveListen();