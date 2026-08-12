#ifndef DEVICECONTROL_INTERFACE_H
#define DEVICECONTROL_INTERFACE_H

#define LAMP1  1
#define LAMP2  2
#define LAMP3  3
#define LAMP4  4
#define LAMP5  5
#define DIMMER_LAMP 6

#define LAMP_ON  1
#define LAMP_OFF 0

#define DOOR_OPEN  1
#define DOOR_CLOSE 0

#define AC_ON  1
#define AC_OFF 0

void Device_voidInit(void);
void Device_voidSetLamp(u8 copy_u8LampID, u8 copy_u8State, u8 copy_u8Brightness);
void Device_voidSetDoor(u8 copy_u8State);
void Device_voidSetAC(u8 copy_u8State);
u8 Device_u8GetACStatus(void);

#endif
