/*
 * UART_interface.h
 *
 * Created: 11/21/2025 9:16:27 PM
 *  Author: mahmo
 */ 


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_


#define UBRR		103  // 9600 baud at 16mhz



void UART_voidInit(void);
void UART_voidTxChar(u8 copy_u8Data);
void UART_voidRxChar(u8* copy_u8ptrData);
void UART_voidTxString(u8* copy_u8ptrTxString);
void UART_voidRxString(u8* copy_u8ptrRxString);
u8 UART_u8RecieveByteNonBlocking(u8* copy_u8ptrData);

#endif /* UART_INTERFACE_H_ */