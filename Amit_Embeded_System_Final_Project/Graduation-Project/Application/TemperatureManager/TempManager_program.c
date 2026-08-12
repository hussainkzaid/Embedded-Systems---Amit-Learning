#include "../../Utils/STD_TYPES.h"
#include "../../MCAL/ADC/ADC_interface.h"
#include "../DeviceControl/DeviceControl_interface.h"
#include "TempManager_interface.h"

#define TEMP_THRESHOLD_ON  28
#define TEMP_THRESHOLD_OFF 21

void Temp_voidInit(void)
{
    ADC_voidInit(ADC_REFERENCE_AVCC);
}

u16 Temp_u16GetCurrentTemp(void)
{
    u16 analogVal = 0;
    ADC_voidGetDigitalValue(ADC_CHANNEL_0, &analogVal); // Ch0 for LM35
    
    /* 
       V_ref = 5000 mV
       Resolution = 1024
       LM35 Scale = 10 mV/C
       Temp = (Analog * 5000 / 1024) / 10
            = (Analog * 500) / 1024
    */
    
    u32 tempCalc = (u32)analogVal * 500;
    u16 temp = tempCalc / 1024;
    return temp;
}

void Temp_voidManage(void)
{
    u16 temp = Temp_u16GetCurrentTemp();
    if(temp > TEMP_THRESHOLD_ON)
    {
        Device_voidSetAC(AC_ON);
    }
    else if(temp < TEMP_THRESHOLD_OFF)
    {
        Device_voidSetAC(AC_OFF);
    }
}
