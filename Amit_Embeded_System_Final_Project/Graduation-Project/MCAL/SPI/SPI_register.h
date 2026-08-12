/*
 * SPI_register.h
 *
 * Created: 11/22/2025 6:14:58 PM
 *  Author: mahmo
 */ 


#ifndef SPI_REGISTER_H_
#define SPI_REGISTER_H_

#define SPCR_REG   *((volatile u8*)0x2D)
#define SPIE		7
#define SPE			6
#define DORD		5
#define MSTR		4
#define CPOL		3
#define CPHA		2
#define SPR1		1
#define SPR0		0

#define SPSR_REG   *((volatile u8*)0x2E)
#define SPIF		7
#define WCOL		6
#define SPI2X		0

#define SPDR_REG   *((volatile u8*)0x2F)


#endif /* SPI_REGISTER_H_ */