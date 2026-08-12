/*
 * DCM_interface.h
 *
 * Created: 10/31/2025 8:42:15 PM
 *  Author: mahmo
 */ 


#ifndef DCM_INTERFACE_H_
#define DCM_INTERFACE_H_




// macros for DCM channels
#define DCM_CHANNEL_A			0
#define DCM_CHANNEL_B			1

// Direction macro
typedef enum
{
	DCM_CW,
	DCM_CCW
} DCM_direction_t;

void DCM_voidInit(u8 copy_u8ChannelID);
void DCM_voidOn(u8 copy_u8Direction, u8 copy_u8ChannelID);
void DCM_voidOff(u8 copy_u8ChannelID);

void DCM_voidInitWithCtrlSpeed(u8 copy_u8ChannelID);
void DCM_voidOnWithCtrlSpeed(u8 copy_u8tDirection, u8 copy_u8Speed, u8 copy_u8ChannelID);
void DCM_voidOffWithCtrlSpeed(u8 copy_u8ChannelID);

#endif /* DCM_INTERFACE_H_ */