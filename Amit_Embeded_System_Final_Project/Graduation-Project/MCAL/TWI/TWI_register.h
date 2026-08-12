/*
 * TWI_register.h
 *
 * Created: 12/11/2025 2:52:30 PM
 *  Author: hussain zaid
 */ 


#ifndef TWI_REGISTER_H_
#define TWI_REGISTER_H_


//TWBR – TWI Bit Rate Register
#define TWBR_REG			(*(volatile u8*)0x20)
#define TWBR7				7
#define TWBR6				6
#define TWBR5				5
#define TWBR4				4
#define TWBR3				3
#define TWBR2				2
#define TWBR1				1
#define TWBR0				0

//TWCR – TWI Control Register
#define TWCR_REG			(*(volatile u8*)0x56)
#define TWINT				7
#define TWEA				6
#define TWSTA				5
#define TWSTO				4
#define TWWC				3
#define TWEN				2
#define TWIE 				0

//TWSR – TWI Status Register
#define TWSR_REG			(*(volatile u8*)0x21)
#define TWS7				7
#define TWS6 				6
#define TWS5 				5
#define TWS4 				4
#define TWS3 				3
#define TWPS1 				1
#define TWPS0 				0

//TWDR – TWI Data Register
#define TWDR_REG			(*(volatile u8*)0x23)
#define TWD7				7
#define TWD6				6
#define TWD5				5
#define TWD4				4
#define TWD3				3
#define TWD2				2
#define TWD1				1
#define TWD0 				0

//TWAR – TWI (Slave) Address Register
#define TWAR_REG			(*(volatile u8*)0x22)
#define TWA6				7
#define TWA5 				6
#define TWA4 				5
#define TWA3 				4
#define TWA2 				3
#define TWA1 				2
#define TWA0 				1
#define TWGCE 				0


#endif /* TWI_REGISTER_H_ */