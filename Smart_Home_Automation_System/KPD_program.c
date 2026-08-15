/*
 * KPD_program.c
 *
 * Created: 10/2/2025 6:52:21 PM
 *  Author: hussain zaid
 */ 

//UTLES_LIB
#include "BIT_MATH.h"
#include "STD_TYPES.h"

//MCAL
#include "DIO_interface.h"

//HAL
#include "KPD_interface.h"
#include "KPD_config.h"


void KPD_voidInit(void){
	//Set KPD Rows As Input Pins
	DIO_voidSetPinDirection(KPD_ROW0_PORT, KPD_ROW0_PIN, DIO_PIN_INPUT);
	DIO_voidSetPinDirection(KPD_ROW1_PORT, KPD_ROW1_PIN, DIO_PIN_INPUT);
	DIO_voidSetPinDirection(KPD_ROW2_PORT, KPD_ROW2_PIN, DIO_PIN_INPUT);
	DIO_voidSetPinDirection(KPD_ROW3_PORT, KPD_ROW3_PIN, DIO_PIN_INPUT);
	
	//Set KPD Cols As Output Pins
	DIO_voidSetPinDirection(KPD_COL0_PORT, KPD_COL0_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(KPD_COL1_PORT, KPD_COL1_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(KPD_COL2_PORT, KPD_COL2_PIN, DIO_PIN_OUTPUT);
	
	//Active Internal PullUp 
	DIO_voidActivePinInternalPUR(KPD_ROW0_PORT, KPD_ROW0_PIN);
	DIO_voidActivePinInternalPUR(KPD_ROW1_PORT, KPD_ROW1_PIN);
	DIO_voidActivePinInternalPUR(KPD_ROW2_PORT, KPD_ROW2_PIN);
	DIO_voidActivePinInternalPUR(KPD_ROW3_PORT, KPD_ROW3_PIN);
	
	//Set Cols Initially High
	DIO_voidSetPinValue(KPD_COL0_PORT, KPD_COL0_PIN, DIO_PIN_HIGH);
	DIO_voidSetPinValue(KPD_COL1_PORT, KPD_COL1_PIN, DIO_PIN_HIGH);
	DIO_voidSetPinValue(KPD_COL2_PORT, KPD_COL2_PIN, DIO_PIN_HIGH);
}


void KPD_voidGetValue(u8* copy_pu8PressedValue){
	if(copy_pu8PressedValue != NULL)
    {
		u8 local_au8KPD_Chars[KPD_NUMBER_OF_ROWS][KPD_NUMBER_OF_COLS] = KPD_KEYS; //Keypad Mapping
		
		*copy_pu8PressedValue = KPD_NOT_PRESSED; //If Not Pressed Don't Print Garbage Value
		
		u8 local_u8ColsCounter, local_u8RowsCounter;
		
		u8 local_u8PinValue; //To Check If Switch Is Pressed(=0) 
		
		for(local_u8ColsCounter = 0 ; local_u8ColsCounter<KPD_NUMBER_OF_COLS ; local_u8ColsCounter++)
        {
			//Active Low Of Current Columns
			switch(local_u8ColsCounter)
			{
				case 0: DIO_voidSetPinValue(KPD_COL0_PORT, KPD_COL0_PIN, DIO_PIN_LOW); break;
				case 1: DIO_voidSetPinValue(KPD_COL1_PORT, KPD_COL1_PIN, DIO_PIN_LOW); break;
				case 2: DIO_voidSetPinValue(KPD_COL2_PORT, KPD_COL2_PIN, DIO_PIN_LOW); break;
			}
			
			//Check Each Row
			for(local_u8RowsCounter = 0 ; local_u8RowsCounter<KPD_NUMBER_OF_ROWS ; local_u8RowsCounter++)
			{
				switch(local_u8RowsCounter)
				{
					case 0: DIO_voidGetPinValue(KPD_ROW0_PORT, KPD_ROW0_PIN, &local_u8PinValue); break;
					case 1: DIO_voidGetPinValue(KPD_ROW1_PORT, KPD_ROW1_PIN, &local_u8PinValue); break;
					case 2: DIO_voidGetPinValue(KPD_ROW2_PORT, KPD_ROW2_PIN, &local_u8PinValue); break;
					case 3: DIO_voidGetPinValue(KPD_ROW3_PORT, KPD_ROW3_PIN, &local_u8PinValue); break;
				}
				
				//Is Pressed (if == 0?)
				if(local_u8PinValue == 0)
				{
					while(local_u8PinValue == 0)  // Wait until release
					{
						switch(local_u8RowsCounter) 
						{
							case 0: DIO_voidGetPinValue(KPD_ROW0_PORT, KPD_ROW0_PIN, &local_u8PinValue); break;
							case 1: DIO_voidGetPinValue(KPD_ROW1_PORT, KPD_ROW1_PIN, &local_u8PinValue); break;
							case 2: DIO_voidGetPinValue(KPD_ROW2_PORT, KPD_ROW2_PIN, &local_u8PinValue); break;
							case 3: DIO_voidGetPinValue(KPD_ROW3_PORT, KPD_ROW3_PIN, &local_u8PinValue); break;
						}
					}
					
					*copy_pu8PressedValue = local_au8KPD_Chars[local_u8RowsCounter][local_u8ColsCounter];
					
					return;
				}
			}
			
			//DeActivate The Current Column
			switch(local_u8ColsCounter)
			{
				case 0: DIO_voidSetPinValue(KPD_COL0_PORT, KPD_COL0_PIN, DIO_PIN_HIGH); break;
				case 1: DIO_voidSetPinValue(KPD_COL1_PORT, KPD_COL1_PIN, DIO_PIN_HIGH); break;
				case 2: DIO_voidSetPinValue(KPD_COL2_PORT, KPD_COL2_PIN, DIO_PIN_HIGH); break;
			}
        }	
    }
    else
	{
		//Return Error State
	}
	 
}