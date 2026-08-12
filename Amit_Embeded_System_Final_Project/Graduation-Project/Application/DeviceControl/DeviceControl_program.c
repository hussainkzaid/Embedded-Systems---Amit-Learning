#include "../../Utils/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/PWM/TMR0PWM_interface.h"
#include "../../HAL/LED/LED_interface.h"
#include "../../HAL/SRV/SRV_interface.h"
#include "../../HAL/DCM/DCM_interface.h"
#include "DeviceControl_interface.h"

// Lamp Config
#define L1_PORT DIO_PORTB
#define L1_PIN  DIO_PIN0

#define L2_PORT DIO_PORTB
#define L2_PIN  DIO_PIN4

#define L3_PORT DIO_PORTB
#define L3_PIN  DIO_PIN5

#define L4_PORT DIO_PORTB
#define L4_PIN  DIO_PIN6

#define L5_PORT DIO_PORTB
#define L5_PIN  DIO_PIN7


void Device_voidInit(void)
{
    // Init Lamps
    LED_voidInit(L1_PORT, L1_PIN);
    LED_voidInit(L2_PORT, L2_PIN);
    LED_voidInit(L3_PORT, L3_PIN);
    LED_voidInit(L4_PORT, L4_PIN);
    LED_voidInit(L5_PORT, L5_PIN);

    // Init Dimmer (PWM TMR0)
    DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN3, DIO_PIN_OUTPUT); // OC0
    TMR0PWM_voidInit();

    // Init Door (Servo)
    SRV_voidInit();

    // Init AC (DCM)
    DCM_voidInit(DCM_CHANNEL_A); 
}

void Device_voidSetLamp(u8 copy_u8LampID, u8 copy_u8State, u8 copy_u8Brightness)
{
    if(copy_u8LampID == DIMMER_LAMP)
    {
         if(copy_u8State == LAMP_ON)
             TMR0PWM_voidGenerate(copy_u8Brightness, _64FROM_PRESCALER);
         else
             TMR0PWM_voidGenerate(0, _64FROM_PRESCALER);
         return;
    }
    
    u8 port = 0, pin = 0;
    switch(copy_u8LampID)
    {
        case LAMP1: port = L1_PORT; pin = L1_PIN; break;
        case LAMP2: port = L2_PORT; pin = L2_PIN; break;
        case LAMP3: port = L3_PORT; pin = L3_PIN; break;
        case LAMP4: port = L4_PORT; pin = L4_PIN; break;
        case LAMP5: port = L5_PORT; pin = L5_PIN; break;
        default: return; 
    }
    
    if(copy_u8State == LAMP_ON)
		LED_voidOn(port, pin, LED_FORWARD_CONNECTION);
    else
		LED_voidOff(port, pin, LED_FORWARD_CONNECTION);
}

void Device_voidSetDoor(u8 copy_u8State)
{
    if(copy_u8State == DOOR_OPEN) 
		SRV_voidOn(180); 
    else 
		SRV_voidOn(90);
}

static u8 g_u8ACState = AC_OFF;

void Device_voidSetAC(u8 copy_u8State)
{
    g_u8ACState = copy_u8State;
    if(copy_u8State == AC_ON) 
		DCM_voidOn(DCM_CW, DCM_CHANNEL_A);
    else
		DCM_voidOff(DCM_CHANNEL_A);
}

u8 Device_u8GetACStatus(void)
{
    return g_u8ACState;
}

