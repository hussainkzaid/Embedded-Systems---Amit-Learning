#ifndef LOGIN_INTERFACE_H
#define LOGIN_INTERFACE_H

#define LOGIN_ADMIN_ROLE    1
#define LOGIN_USER_ROLE     2
#define LOGIN_NO_ROLE       0
#define MAX_USERS           5

#define LOGIN_CH_KPD        0
#define LOGIN_CH_TERMINAL   1

void Login_voidInit(void);
u8 Login_u8Authenticate(u8 copy_u8Channel, u8 copy_u8UserID, u8* copy_pu8Password);
void Login_voidRegisterUser(u8 copy_u8UserID, u8* copy_pu8Password);
void Login_voidRemoveUser(u8 copy_u8UserID);
u8 Login_u8GetUser(u8 copy_u8Index, u8* copy_pu8ID);
u8 Login_u8GetFailedAttempts(void);
u8 Login_u8CheckID(u8 copy_u8ID);

#endif
