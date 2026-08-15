/*
 * smartHomeAutomationSystem
 *
 * Created: 12/12/2025 9:16:54 PM
 * Author : hussain zaid
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>

//UTLES_LIB
#include "BIT_MATH.h"
#include "STD_TYPES.h"

//MCAL
#include "DIO_interface.h"
#include "PWM1_interface.h"

//HAL
#include "LED_interface.h"
#include "KPD_interface.h"
#include "LCD_interface.h"
#include "SRVM_interface.h"

#define PASSWORD_SIZE		4
#define ADMIN_PASSWORD		{'7', '0', '8', '6'}
#define PRE_PASSWORD		{'7', '0', '8', '5'}
#define NUMBER_OF_TRIALS	3

typedef struct login
{
	u8 User_id[40];
}LoginInfo;

int main(void)
{
    /* Replace with your application code */
	KPD_voidInit();
	LCD_voidInit();
	SRVM_voidInit();
	LED_voidInit(DIO_PORTC, DIO_PIN0);//Red Led
	LED_voidInit(DIO_PORTC, DIO_PIN1);//Green Led
	
	u8 prePass[PASSWORD_SIZE] = PRE_PASSWORD;
	
	u8 password[PASSWORD_SIZE];
	
	LoginInfo user;
	u8 log_index = 0;
	u8 key;
	
	LCD_voidClear();
	LCD_voidGoToSpecificPosition(LCD_LINE_ONE, 0);
	LCD_voidDisplayString((u8*)"Enter Username: ");
	LCD_voidGoToSpecificPosition(LCD_LINE_TWO, 0);
	
	while (1)
	{
		KPD_voidGetValue(&key);
		if (key != KPD_NOT_PRESSED)
		{
			if (key == '#') break;  //End input

			LCD_voidDisplayChar(key);
			user.User_id[log_index++] = key;

			if (log_index >= 39) break; //prevent overflow
		}
		_delay_ms(50);
	}

	user.User_id[log_index] = '\0';  //Null terminate
	
    while (1) 
    {
		//To Try Again After 15s
		u8 trial = 0;
		u8 Pass_index = 0;
		
		LCD_voidClear();
		LCD_voidGoToSpecificPosition(LCD_LINE_ONE, 0);
		LCD_voidDisplayString((u8*)"Enter Password:");
		LCD_voidGoToSpecificPosition(LCD_LINE_TWO, 0);
		
		//3 trials
		while(trial <= NUMBER_OF_TRIALS)
		{
			//Enter password by keypad
			while(Pass_index < PASSWORD_SIZE)
			{
				KPD_voidGetValue(&password[Pass_index]);
				if(password[Pass_index] != KPD_NOT_PRESSED)
				{
					LCD_voidDisplayChar('*');
					Pass_index++;
				}
				_delay_ms(200);
			}
			
			//Compare The Entered Password And The PrePassword
			u8 isMatch = 1;
			for(u8 i =0; i<PASSWORD_SIZE; i++)
			{
				if(password[i] != prePass[i])
				{
					isMatch = 0;
					break;
				}
			}
			
			//True Pass
			if (isMatch)
			{
				LCD_voidClear();
				LCD_voidGoToSpecificPosition(LCD_LINE_ONE,0);
				LCD_voidDisplayString((u8*)" Access Granted");
				
				LED_voidOn(DIO_PORTC, DIO_PIN1, LED_FORWARD_CONNECTION);//Green Led
				
				SRVM_voidOn(180); //Open Door
				
				_delay_ms(5000);
				
				LED_voidOff(DIO_PORTC, DIO_PIN1, LED_FORWARD_CONNECTION);
				
				SRVM_voidOn(90);
				
				Pass_index = 0;
				break;
			}
			
			//False Pass
			else
			{
				LCD_voidClear();
				LCD_voidGoToSpecificPosition(LCD_LINE_ONE,0);
				LCD_voidDisplayNumber(NUMBER_OF_TRIALS - trial);
				LCD_voidDisplayString((u8*)" Trials Left");
				
				LCD_voidGoToSpecificPosition(LCD_LINE_TWO, 0);
				
				Pass_index = 0;
				for(u8 reset = 0; reset<PASSWORD_SIZE; reset++)
				{
					password[reset] = KPD_NOT_PRESSED;
				}
			}
			
			trial++;
		}
		
		//Security Alert
		if(trial > NUMBER_OF_TRIALS)
		{
			LCD_voidClear();
			LCD_voidGoToSpecificPosition(LCD_LINE_ONE,0);
			LCD_voidDisplayString((u8*)" SECURITY ALERT!");
			
			LED_voidOn(DIO_PORTC, DIO_PIN0, LED_FORWARD_CONNECTION);//Red Led
			
			_delay_ms(5000);
			
			LED_voidOff(DIO_PORTC, DIO_PIN0, LED_FORWARD_CONNECTION);//Red Led
		}
		
		_delay_ms(10000);
    }
}

