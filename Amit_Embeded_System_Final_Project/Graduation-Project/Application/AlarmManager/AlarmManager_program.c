#include "../../Utils/STD_TYPES.h"
#include "../../MCAL/WDT/WDT_interface.h"
#include "../../HAL/LCD/LCD_interface.h"
#include "AlarmManager_interface.h"

void Alarm_voidInit(void)
{
    WDT_voidDisable();
}

void Alarm_voidTrigger(void)
{
    LCD_voidClear();
    LCD_voidGoToSpecificPosition(LCD_LINE_ONE, 0);
    LCD_voidDisplayString((u8*)"ALARM SYSTEM");
    LCD_voidGoToSpecificPosition(LCD_LINE_TWO, 0);
    LCD_voidDisplayString((u8*)"TRIGGERED!");

    /* Enable WDT to reset the system after 2 seconds causing a reboot */
    WDT_voidEnable(WDT_TIMEOUT_2S);
    while(1);
}

