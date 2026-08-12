/*
 * WDT_program.c
 *
 * Created: 11/14/2025 7:05:27 PM
 *  Author: mahmo
 */ 

#include "WDT_interface.h"
#include "WDT_register.h"

#include "BIT_MATH.h"
#include "STD_TYPES.h"



void WDT_voidEnable(u8 copy_u8PrescaleValue)
{
	CLR_BIT(WDTCR_REG, 4);
	SET_BIT(WDTCR_REG, 3);
	WDTCR_REG = (WDTCR_REG & 0b11111000) | copy_u8PrescaleValue;
}
void WDT_voidDisable(void)
{
	WDTCR_REG = WDTCR_REG | 0b00011000;
	WDTCR_REG = 0x00;
}