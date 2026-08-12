/*
 * UART_register.h
 *
 * Created: 11/21/2025 9:16:43 PM
 *  Author: mahmo
 */ 


#ifndef UART_REGISTER_H_
#define UART_REGISTER_H_

#define UDR_REG			*((volatile u8*)0x2C)
#define UBRRH_REG		*((volatile u8*)0x40)		
#define UBRRL_REG		*((volatile u8*)0x29)
#define UCSRA_REG		*((volatile u8*)0x2B)
#define UCSRB_REG		*((volatile u8*)0x2A)
#define UCSRC_REG		*((volatile u8*)0x40)




#endif /* UART_REGISTER_H_ */