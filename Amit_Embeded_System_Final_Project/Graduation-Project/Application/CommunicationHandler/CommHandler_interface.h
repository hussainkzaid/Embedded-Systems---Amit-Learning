#ifndef COMMHANDLER_INTERFACE_H
#define COMMHANDLER_INTERFACE_H

void Comm_voidInit(void);
void Comm_voidSendMessage(u8* msg);
void Comm_voidManage(void);

u8 Comm_u8IsKpdUserPermitted(void);
u8 Comm_u8GetTerminalRole(void);
void Comm_voidSetKpdStatus(u8 copy_u8Status);

#endif
