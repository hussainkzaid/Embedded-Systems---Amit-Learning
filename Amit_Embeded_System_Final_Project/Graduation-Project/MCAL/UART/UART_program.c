/*
 * UART_program.c
 *
 * Created: 11/21/2025 9:16:57 PM
 *  Author: mahmo
 */ 



#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_register.h"
#include "UART_interface.h"

void UART_voidInit()
{
	// Disable double speed
	CLR_BIT(UCSRA_REG, 1);
	
	// Clear any previous settings
	UCSRB_REG = UCSRB_REG & 0b00011111;
	
	// Configure UCSRC: 8-bit data, 1 stop bit, no parity
	// URSEL=1 to select UCSRC (not UBRRH), UCSZ1=1, UCSZ0=1 for 8-bit
	UCSRC_REG = 0b10000110;  // Binary: 1 0 0 0 0 1 1 0
	                          // Bits:   U R U U U U U U
	                          //         R E C M P B S S
	                          //         S S S S B 1 Z Z
	                          //         E V Z Z S   1 0
	
	// Set baud rate to 9600 at 16MHz (UBRR = 103)
	UBRRH_REG = 0;
	UBRRL_REG = 103;
	
	// Enable transmitter and receiver
	SET_BIT(UCSRB_REG, 4);  // RXEN
	SET_BIT(UCSRB_REG, 3);  // TXEN
}

void UART_voidTxChar(u8 copy_u8Data){

	while (!GET_BIT(UCSRA_REG, 5));
	UDR_REG = copy_u8Data;

}

void UART_voidRxChar(u8* copy_u8ptrData){
	if(copy_u8ptrData != NULL)
	{
		while (!GET_BIT(UCSRA_REG, 7));
		*copy_u8ptrData = UDR_REG;
	}
	else
	{
		// return error statement
	}

}


void UART_voidTxString(u8* copy_u8ptrTxString)
{
	u8 local_u8Counter = 0;
	while (*(copy_u8ptrTxString  + local_u8Counter) != '\0')
	{
		UART_voidTxChar(*(copy_u8ptrTxString  + local_u8Counter));
		local_u8Counter++;
	}
}


void UART_voidRxString(u8* copy_u8ptrRxString)
{
	u8 local_u8Counter = 0;
	u8 local_u8PreviuosChar = 0;
	u8 local_u8CurrentChar = 0;
	while (!((local_u8PreviuosChar == 92) && (local_u8CurrentChar == '0')))
	{
		local_u8PreviuosChar = local_u8CurrentChar;
		UART_voidRxChar(&local_u8CurrentChar);
		*(copy_u8ptrRxString  + local_u8Counter) = local_u8CurrentChar;
		local_u8Counter++;
	}
	*(copy_u8ptrRxString  + local_u8Counter - 2) = '\0';
}

u8 UART_u8RecieveByteNonBlocking(u8* copy_u8ptrData)
{
    if(GET_BIT(UCSRA_REG, 7))
    {
        *copy_u8ptrData = UDR_REG;
        return 1;
    }
    return 0;
}