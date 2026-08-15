/*
 * KPD_interface.h
 *
 * Created: 10/2/2025 6:52:33 PM
 *  Author: hussain zaid
 */ 


#ifndef KPD_INTERFACE_H_
#define KPD_INTERFACE_H_

#define KPD_NOT_PRESSED		0xFF

/************************************** APIs Prototypes **************************************/
void KPD_voidInit(void);
void KPD_voidGetValue(u8* copy_pu8PressedValue);

#endif /* KPD_INTERFACE_H_ */