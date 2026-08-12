/*
 * SPI_interface.h
 *
 * Created: 11/22/2025 6:15:12 PM
 *  Author: mahmo
 */ 


#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_


#define SPI_SLAVE		0
#define SPI_MASTER		1

typedef enum
{
	SCK_FOSC_DIV_4,     // SPI2X=0, SPR1=0, SPR0=0
	SCK_FOSC_DIV_16,    // SPI2X=0, SPR1=0, SPR0=1
	SCK_FOSC_DIV_64,    // SPI2X=0, SPR1=1, SPR0=0
	SCK_FOSC_DIV_128,   // SPI2X=0, SPR1=1, SPR0=1
	SCK_FOSC_DIV_2,     // SPI2X=1, SPR1=0, SPR0=0
	SCK_FOSC_DIV_8,     // SPI2X=1, SPR1=0, SPR0=1
	SCK_FOSC_DIV_32,    // SPI2X=1, SPR1=1, SPR0=0
	SCK_FOSC_DIV_64_2   // SPI2X=1, SPR1=1, SPR0=1 
} SPI_clockrate_t;

#define SPI_CLOCK_RATE		SCK_FOSC_DIV_128

void SPI_voidInit(u8 copy_u8Mode);
void SPI_voidTx(u8* copy_u8Data);



#endif /* SPI_INTERFACE_H_ */