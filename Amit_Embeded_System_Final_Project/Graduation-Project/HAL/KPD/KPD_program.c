/*
 * KPD_program.c
 *
 * Created: 9/27/2025 6:57:25 PM
 *  Author: mahmo
 */

// Utils Lib
#include "STD_TYPES.h"
#include "BIT_MATH.h"

// MCAL
#include "DIO_interface.h"
#include "DIO_register.h"

// HAL
#include "KPD_config.h"
#include "KPD_interface.h"

#define F_CPU 16000000UL
#include <util/delay.h>

u8 local_au8KeypadValues[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS] = KPD_KEYS;

void KPD_voidInit(void)
{
	// set columns pins
	DIO_voidSetPinDirection(KPD_COLUMN_ZERO_PORT, DIO_PIN2, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(KPD_COLUMN_ONE_PORT, DIO_PIN3, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(KPD_COLUMN_TWO_PORT, DIO_PIN7, DIO_PIN_OUTPUT);

	// set rows pins
	DIO_voidSetPinDirection(KPD_ROW_ZERO_PORT, DIO_PIN1, DIO_PIN_INPUT);
	DIO_voidSetPinDirection(KPD_ROW_ONE_PORT, DIO_PIN2, DIO_PIN_INPUT);
	DIO_voidSetPinDirection(KPD_ROW_TWO_PORT, DIO_PIN3, DIO_PIN_INPUT);
	// active rows internal pull up resistance
	DIO_voidSetPinValue(KPD_ROW_ZERO_PORT, DIO_PIN1, DIO_PIN_HIGH);
	DIO_voidSetPinValue(KPD_ROW_ONE_PORT, DIO_PIN2, DIO_PIN_HIGH);
	DIO_voidSetPinValue(KPD_ROW_TWO_PORT, DIO_PIN3, DIO_PIN_HIGH);
}

void KPD_voidGetValue(u8 *pu8PressedValue)
{
	if (pu8PressedValue != NULL)
	{
		*pu8PressedValue = KPD_NOT_PRESSED;
		u8 local_u8ColumnsCounter;
		for (local_u8ColumnsCounter = 0; local_u8ColumnsCounter < NUMBER_OF_COLUMNS; local_u8ColumnsCounter++)
		{
			DIO_voidSetPinValue(KPD_COLUMN_ZERO_PORT, KPD_COLUMN_ZERO_PIN, DIO_PIN_HIGH);
			DIO_voidSetPinValue(KPD_COLUMN_ONE_PORT, KPD_COLUMN_ONE_PIN, DIO_PIN_HIGH);
			DIO_voidSetPinValue(KPD_COLUMN_TWO_PORT, KPD_COLUMN_TWO_PIN, DIO_PIN_HIGH);

			switch (local_u8ColumnsCounter)
			{
			case 0:
				DIO_voidSetPinValue(KPD_COLUMN_ZERO_PORT, KPD_COLUMN_ZERO_PIN, DIO_PIN_LOW);
				break;
			case 1:
				DIO_voidSetPinValue(KPD_COLUMN_ONE_PORT, KPD_COLUMN_ONE_PIN, DIO_PIN_LOW);
				break;
			case 2:
				DIO_voidSetPinValue(KPD_COLUMN_TWO_PORT, KPD_COLUMN_TWO_PIN, DIO_PIN_LOW);
				break;
			}

			u8 local_u8RowsCounter;
			for (local_u8RowsCounter = 0; local_u8RowsCounter < NUMBER_OF_ROWS; local_u8RowsCounter++)
			{
				u8 local_u8RowPinValue = 1;
				switch (local_u8RowsCounter)
				{
				case 0:
					DIO_voidGetPinValue(KPD_ROW_ZERO_PORT, KPD_ROW_ZERO_PIN, &local_u8RowPinValue);
					break;
				case 1:
					DIO_voidGetPinValue(KPD_ROW_ONE_PORT, KPD_ROW_ONE_PIN, &local_u8RowPinValue);
					break;
				case 2:
					DIO_voidGetPinValue(KPD_ROW_TWO_PORT, KPD_ROW_TWO_PIN, &local_u8RowPinValue);
					break;
				}

				if (local_u8RowPinValue == 0)
				{
					_delay_ms(30); // Debounce
					switch (local_u8RowsCounter)
					{
						case 0: DIO_voidGetPinValue(KPD_ROW_ZERO_PORT, KPD_ROW_ZERO_PIN, &local_u8RowPinValue); break;
						case 1: DIO_voidGetPinValue(KPD_ROW_ONE_PORT, KPD_ROW_ONE_PIN, &local_u8RowPinValue); break;
						case 2: DIO_voidGetPinValue(KPD_ROW_TWO_PORT, KPD_ROW_TWO_PIN, &local_u8RowPinValue); break;
					}
					
					if(local_u8RowPinValue == 0)
					{
						*pu8PressedValue = local_au8KeypadValues[local_u8RowsCounter][local_u8ColumnsCounter];
						return;
					}
				}
			}
		}
	}
	else
	{
		// return error state
	}
}
