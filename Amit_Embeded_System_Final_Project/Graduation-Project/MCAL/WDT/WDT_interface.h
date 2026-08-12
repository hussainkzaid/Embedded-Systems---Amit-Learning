/*
 * WDT_interface.h
 *
 * Created: 11/14/2025 7:04:57 PM
 *  Author: mahmo
 */ 


#ifndef WDT_INTERFACE_H_
#define WDT_INTERFACE_H_

#include "STD_TYPES.h"

typedef enum
{
	WDT_TIMEOUT_16MS = 0,     // 0 0 0 ? 16K	cycles ? 16.3ms		
	WDT_TIMEOUT_32MS,         // 0 0 1 ? 32K	cycles ? 32.5ms		
	WDT_TIMEOUT_64MS,         // 0 1 0 ? 64K	cycles ? 0.065s	
	WDT_TIMEOUT_128MS,        // 0 1 1 ? 128K	cycles ? 0.13s 
	WDT_TIMEOUT_256MS,        // 1 0 0 ? 256K	cycles ? 0.26s 
	WDT_TIMEOUT_512MS,        // 1 0 1 ? 512K	cycles ? 0.52s 
	WDT_TIMEOUT_1S,           // 1 1 0 ? 1024K	cycles ? 1.0s
	WDT_TIMEOUT_2S            // 1 1 1 ? 2048K	cycles ? 2.1s

} WDT_Prescaler_t;


void WDT_voidEnable(u8 copy_u8PrescaleValue);
void WDT_voidDisable(void);


#endif /* WDT_INTERFACE_H_ */