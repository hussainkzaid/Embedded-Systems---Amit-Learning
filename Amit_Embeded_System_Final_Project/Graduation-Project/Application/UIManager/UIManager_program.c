#define F_CPU 16000000UL
#include <util/delay.h>

#include "../../Utils/STD_TYPES.h"
#include "../../HAL/LCD/LCD_interface.h"
#include "../TemperatureManager/TempManager_interface.h"
#include "../DeviceControl/DeviceControl_interface.h"
#include "UIManager_interface.h"

#define MAX_OPTIONS  6u

static const char* const g_cpOptions[MAX_OPTIONS] = {"L1", "L2", "L3", "L4", "L5", "Dim"};


static u16 g_u16LastTemp   = 0xFFFFu;
static u8  g_u8LastACState = 0xFFu;

void UI_voidDisplayMainMenu(void)
{
    LCD_voidClear();
    LCD_voidDisplayString((u8*)"1-Status");
    LCD_voidGoToSpecificPosition(LCD_LINE_TWO, 0);
    LCD_voidDisplayString((u8*)"2-Opt   3-Logout");
}

void UI_voidDisplayStatus(void)
{
    LCD_voidClear();

    /* Cache current values */
    g_u16LastTemp   = Temp_u16GetCurrentTemp();
    g_u8LastACState = Device_u8GetACStatus();

    /* Line 1: Temp:XXC  AC:ON */
    LCD_voidDisplayString((u8*)"Temp:");
    LCD_voidDisplayNumber(g_u16LastTemp);
    LCD_voidDisplayString((u8*)"C  AC:");
    if (g_u8LastACState == AC_ON)
        LCD_voidDisplayString((u8*)"ON ");
    else
        LCD_voidDisplayString((u8*)"OFF");

    /* Line 2: navigation hint */
    LCD_voidGoToSpecificPosition(LCD_LINE_TWO, 0);
    LCD_voidDisplayString((u8*)"          3-Back");
}

void UI_voidRefreshStatus(void)
{
    u16 currentTemp  = Temp_u16GetCurrentTemp();
    u8  currentAC    = Device_u8GetACStatus();

    if (currentTemp != g_u16LastTemp || currentAC != g_u8LastACState)
    {
        /* Update only changed digits in-place — no full clear */
        LCD_voidGoToSpecificPosition(LCD_LINE_ONE, 5);
        LCD_voidDisplayNumber(currentTemp);
        LCD_voidDisplayString((u8*)"C ");   /* trailing space clears old digit */

        LCD_voidGoToSpecificPosition(LCD_LINE_ONE, 13);
        if (currentAC == AC_ON)
            LCD_voidDisplayString((u8*)"ON ");
        else
            LCD_voidDisplayString((u8*)"OFF");

        g_u16LastTemp   = currentTemp;
        g_u8LastACState = currentAC;
    }
}

void UI_voidDisplayOptions(u8 copy_u8OptionIdx)
{
    LCD_voidClear();

    /* Line 1: device name and action hint */
    LCD_voidDisplayString((u8*)g_cpOptions[copy_u8OptionIdx]);
    if (copy_u8OptionIdx == (MAX_OPTIONS - 1u))   /* Dimmer */
        LCD_voidDisplayString((u8*)": 2-Set");
    else
        LCD_voidDisplayString((u8*)": 2-On  3-Off");

    /* Line 2: back key + navigation arrows */
    LCD_voidGoToSpecificPosition(LCD_LINE_TWO, 0);
    LCD_voidDisplayString((u8*)"1-Back  ");

    if (copy_u8OptionIdx > 0u)
    {
        LCD_voidGoToSpecificPosition(LCD_LINE_TWO, 14);
        LCD_voidDisplayChar('<');
    }
    if (copy_u8OptionIdx < (MAX_OPTIONS - 1u))
    {
        LCD_voidGoToSpecificPosition(LCD_LINE_TWO, 15);
        LCD_voidDisplayChar('>');
    }
}

void UI_voidDisplayDimmerCtrl(void)
{
    LCD_voidClear();
    LCD_voidDisplayString((u8*)"2:0 3:25 4:50");
    LCD_voidGoToSpecificPosition(LCD_LINE_TWO, 0);
    LCD_voidDisplayString((u8*)"5:75 6:100 1-Ret");
}

void UI_voidShowMessage(const u8* copy_pu8Msg, u16 copy_u16DelayMs)
{
    LCD_voidClear();
    LCD_voidDisplayString((u8*)copy_pu8Msg);
    /* Simple delay loop — avoids exposing _delay_ms to callers */
    for (u16 i = 0u; i < copy_u16DelayMs; i++)
        _delay_ms(1);
}
