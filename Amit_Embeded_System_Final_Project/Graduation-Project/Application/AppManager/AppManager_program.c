#define F_CPU 16000000UL
#include <util/delay.h>

#include "../../Utils/STD_TYPES.h"
#include "../../HAL/LCD/LCD_interface.h"
#include "../../HAL/KPD/KPD_interface.h"

#include "../Login/Login_interface.h"
#include "../DeviceControl/DeviceControl_interface.h"
#include "../TemperatureManager/TempManager_interface.h"
#include "../CommunicationHandler/CommHandler_interface.h"
#include "../AlarmManager/AlarmManager_interface.h"
#include "../UIManager/UIManager_interface.h"
#include "AppManager_interface.h"

typedef enum
{
    APP_STATE_IDLE,         /* Transient: startup only              */
    APP_STATE_WAIT_ID,      /* Waiting for user to press ID key     */
    APP_STATE_WAIT_PASS,    /* Collecting 4-digit password          */
    APP_STATE_MAIN_MENU,    /* Main menu displayed                  */
    APP_STATE_STATUS,       /* Live temp & AC screen                */
    APP_STATE_OPTIONS,      /* Device selection carousel            */
    APP_STATE_DIMMER_CTRL   /* Dimmer brightness selection          */
} AppState_t;


#define MAX_OPTIONS         6u
#define PASSWORD_LENGTH     4u
#define DEBOUNCE_MS         250u
#define STARTUP_BANNER_MS   500u
#define MSG_SHORT_MS        500u
#define MSG_LONG_MS         1000u

static AppState_t g_eAppState        = APP_STATE_IDLE;
static u8         g_u8KpdRole        = LOGIN_NO_ROLE;
static u8         g_u8CurrentOptIdx  = 0u;

static u8 g_u8PassBuffer[PASSWORD_LENGTH];
static u8 g_u8PassIdx = 0u;

static u8 g_u8EnteredID = 0u;


static void App_HandleWaitID(u8 copy_u8Key);
static void App_HandleWaitPass(u8 copy_u8Key);
static void App_HandleMainMenu(u8 copy_u8Key);
static void App_HandleStatus(u8 copy_u8Key);
static void App_HandleOptions(u8 copy_u8Key);
static void App_HandleDimmerCtrl(u8 copy_u8Key);
static void App_DispatchKeypad(u8 copy_u8Key);


void App_voidInit(void)
{
    // Hardware init
    LCD_voidInit();
    KPD_voidInit();

    // Application module init
    Login_voidInit();       // TWI + EEPROM + default admin 
    Device_voidInit();      // LEDs + PWM + Servo + DCM     
    Temp_voidInit();        // ADC                          
    Comm_voidInit();        // UART + terminal prompt       
    Alarm_voidInit();       // WDT disable                  

    /* Notify CommHandler: no keypad user is logged in yet */
    Comm_voidSetKpdStatus(0);

    /* Startup banner */
    LCD_voidDisplayString((u8*)"Smart Home System");
    _delay_ms(STARTUP_BANNER_MS);
    LCD_voidClear();

    /* Transition to first real state */
    g_eAppState = APP_STATE_WAIT_ID;
    LCD_voidDisplayString((u8*)"ID: ");
}

void App_voidRun(void)
{
    Temp_voidManage();
    Comm_voidManage();


    if (g_eAppState == APP_STATE_STATUS)
    {
        UI_voidRefreshStatus();
    }

    u8 local_u8Key = KPD_NOT_PRESSED;
    KPD_voidGetValue(&local_u8Key);

    if (local_u8Key != KPD_NOT_PRESSED)
    {
        App_DispatchKeypad(local_u8Key);
        _delay_ms(DEBOUNCE_MS);  // Software debounce
    }
}

static void App_DispatchKeypad(u8 copy_u8Key)
{
    switch (g_eAppState)
    {
        case APP_STATE_WAIT_ID:      App_HandleWaitID(copy_u8Key);      break;
        case APP_STATE_WAIT_PASS:    App_HandleWaitPass(copy_u8Key);    break;
        case APP_STATE_MAIN_MENU:    App_HandleMainMenu(copy_u8Key);    break;
        case APP_STATE_STATUS:       App_HandleStatus(copy_u8Key);      break;
        case APP_STATE_OPTIONS:      App_HandleOptions(copy_u8Key);     break;
        case APP_STATE_DIMMER_CTRL:  App_HandleDimmerCtrl(copy_u8Key);  break;
        default:                                                         break;
    }
}

static void App_HandleWaitID(u8 copy_u8Key)
{
    g_u8EnteredID = copy_u8Key;
    LCD_voidDisplayChar(copy_u8Key);
    _delay_ms(300);

    LCD_voidGoToSpecificPosition(LCD_LINE_TWO, 0);
    LCD_voidDisplayString((u8*)"Pass: ");

    g_u8PassIdx = 0u;
    g_eAppState = APP_STATE_WAIT_PASS;
}

static void App_HandleWaitPass(u8 copy_u8Key)
{
    g_u8PassBuffer[g_u8PassIdx++] = copy_u8Key;
    LCD_voidDisplayChar('*');
    _delay_ms(300);

    if (g_u8PassIdx == PASSWORD_LENGTH)
    {
        g_u8KpdRole = Login_u8Authenticate(
            LOGIN_CH_KPD, g_u8EnteredID, g_u8PassBuffer);

        if (g_u8KpdRole != LOGIN_NO_ROLE)
        {
            Comm_voidSetKpdStatus(1);
            UI_voidShowMessage((u8*)"Login Success!", MSG_SHORT_MS);
            g_eAppState = APP_STATE_MAIN_MENU;
            UI_voidDisplayMainMenu();
        }
        else
        {
            UI_voidShowMessage((u8*)"Login Failed!", MSG_LONG_MS);
            LCD_voidClear();
            LCD_voidDisplayString((u8*)"ID: ");
            g_eAppState = APP_STATE_WAIT_ID;
        }
    }
}

static void App_HandleMainMenu(u8 copy_u8Key)
{
    if (copy_u8Key == '1')
    {
        g_eAppState = APP_STATE_STATUS;
        UI_voidDisplayStatus();
    }
    else if (copy_u8Key == '2')
    {
        g_u8CurrentOptIdx = 0u;
        g_eAppState = APP_STATE_OPTIONS;
        UI_voidDisplayOptions(g_u8CurrentOptIdx);
    }
    else if (copy_u8Key == '3')   /* Logout */
    {
        Comm_voidSetKpdStatus(0);
        UI_voidShowMessage((u8*)"Logged Out", MSG_SHORT_MS);
        LCD_voidClear();
        LCD_voidDisplayString((u8*)"ID: ");
        g_eAppState = APP_STATE_WAIT_ID;
    }
}

static void App_HandleStatus(u8 copy_u8Key)
{
    if (copy_u8Key == '3')
    {
        g_eAppState = APP_STATE_MAIN_MENU;
        UI_voidDisplayMainMenu();
    }
    else if (copy_u8Key == '1')
    {
        UI_voidDisplayStatus();
    }
}

/*
 * OPTIONS: Device carousel.
 *   '4' = prev item, '6' = next item
 *   '2' = On  (or enter dimmer sub-menu)
 *   '3' = Off
 *   '1' = back to main menu
 */
static void App_HandleOptions(u8 copy_u8Key)
{
    if (copy_u8Key == '1')
    {
        g_eAppState = APP_STATE_MAIN_MENU;
        UI_voidDisplayMainMenu();
        return;
    }

    if (copy_u8Key == '4' && g_u8CurrentOptIdx > 0u)
    {
        g_u8CurrentOptIdx--;
        UI_voidDisplayOptions(g_u8CurrentOptIdx);
        return;
    }
    if (copy_u8Key == '6' && g_u8CurrentOptIdx < (MAX_OPTIONS - 1u))
    {
        g_u8CurrentOptIdx++;
        UI_voidDisplayOptions(g_u8CurrentOptIdx);
        return;
    }

    if (g_u8CurrentOptIdx == (MAX_OPTIONS - 1u) && copy_u8Key == '2')
    {
        g_eAppState = APP_STATE_DIMMER_CTRL;
        UI_voidDisplayDimmerCtrl();
        return;
    }

    if (copy_u8Key == '2' || copy_u8Key == '3')
    {
        if (Comm_u8IsKpdUserPermitted() == 0u)
        {
            UI_voidShowMessage((u8*)"Blocked By Admin", MSG_LONG_MS);
            UI_voidDisplayOptions(g_u8CurrentOptIdx);
            return;
        }

        u8 lampState = (copy_u8Key == '2') ? LAMP_ON : LAMP_OFF;
        Device_voidSetLamp((u8)(g_u8CurrentOptIdx + 1u), lampState, 0u);
    }
}

static void App_HandleDimmerCtrl(u8 copy_u8Key)
{
    if (copy_u8Key == '1')
    {
        g_eAppState = APP_STATE_OPTIONS;
        UI_voidDisplayOptions(g_u8CurrentOptIdx);
        return;
    }

    u8 brightness = 0xFFu; // invalid key
    switch (copy_u8Key)
    {
        case '2': brightness = 0u;   break;   // 0%
        case '3': brightness = 64u;  break;   // 25%
        case '4': brightness = 128u; break;   // 50%
        case '5': brightness = 192u; break;   // 75%
        case '6': brightness = 255u; break;   // 100%
        default:                     break;
    }

    if (brightness == 0xFFu) return;  // ignore unrecognised key

    if (Comm_u8IsKpdUserPermitted() == 0u)
    {
        UI_voidShowMessage((u8*)"Blocked By Admin", MSG_LONG_MS);
        UI_voidDisplayDimmerCtrl();
        return;
    }

    Device_voidSetLamp(DIMMER_LAMP, LAMP_ON, brightness);
    UI_voidDisplayDimmerCtrl();   // Redisplay after applying brightness
}
