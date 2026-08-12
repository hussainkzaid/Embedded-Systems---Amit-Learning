/*
 * SPI_program.c
 *
 * Created: 11/22/2025 6:15:24 PM
 *  Author: mahmo
 */ 

#include "STD_TYPES.h"
#include "SPI_register.h"
#include "SPI_interface.h"


void SPI_voidInit(u8 copy_u8Mode)
{
	CLR_BIT(SPCR_REG, SPIE);	// interrupt disable
	SET_BIT(SPCR_REG, DORD);	// data order  LSB first
	switch(copy_u8Mode)
	{
		case SPI_SLAVE:
			CLR_BIT(SPCR_REG, MSTR);
			break;
		case SPI_MASTER:
			SET_BIT(SPCR_REG, MSTR);
			break;
		default:
			break;
	}
	SET_BIT(SPCR_REG, CPOL);	// clock polarity
	SET_BIT(SPCR_REG, CPHA);	// clock phase
	
	
	// setting clock rate
	CLR_BIT(SPSR_REG, 0);
	SPSR_REG | GET_BIT(SPI_CLOCK_RATE, 2);
	
	CLR_BIT(SPI_CLOCK_RATE, 2);
	SPCR_REG = (SPCR_REG & 0b11111100) | SPI_CLOCK_RATE;
	
	
	SET_BIT(SPCR_REG, SPE);		// SPI enable

}

void SPI_voidTransceive(u8 copy_u8TxData, u8* pu8RxData)
{
	if (pu8RxData != NULL)
	{
		SPDR_REG = copy_u8TxData;

		while (GET_BIT(SPSR_REG, SPIF) == 0);

		*pu8RxData = SPDR_REG;                 
	}
	else
	{
		// return error state
	}
}
