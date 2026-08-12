#include "../../Utils/STD_TYPES.h"
#include "../../Utils/BIT_MATH.h"
#include "../../MCAL/EEPROM/EEPROM_interface.h"
#include "../../MCAL/TWI/TWI_interface.h"
#include "../../HAL/LCD/LCD_interface.h"
#include "../AlarmManager/AlarmManager_interface.h"
#include "Login_interface.h"
#define ADMIN_START_ADDR 0x00
#define USERS_START_ADDR 0x10
#define USER_ENTRY_SIZE  6 // 1 Status + 1 ID + 4 Pass

static u8 Login_u8FailedAttempts = 0;

void Login_voidInit(void)
{
	TWI_voidInitMaster();
    /* Check if Admin exists (Status byte at 0x00 is 0xFF usually on fresh EEPROM, or 0x01 if set) */
    u8 local_u8AdminStatus;
    EEPROM_voidReadByte(ADMIN_START_ADDR, &local_u8AdminStatus);
    
    if (local_u8AdminStatus != 1)
    {
        /* Create Default Admin: ID '1', Pass "1234" */
        EEPROM_voidWriteByte(ADMIN_START_ADDR, 1); // Status Active
        EEPROM_voidWriteByte(ADMIN_START_ADDR + 1, '1'); // ID
        EEPROM_voidWriteByte(ADMIN_START_ADDR + 2, '1');
        EEPROM_voidWriteByte(ADMIN_START_ADDR + 3, '2');
        EEPROM_voidWriteByte(ADMIN_START_ADDR + 4, '3');
        EEPROM_voidWriteByte(ADMIN_START_ADDR + 5, '4');
    }
}

u8 Login_u8Authenticate(u8 copy_u8Channel, u8 copy_u8UserID, u8* copy_pu8Password)
{
    u8 local_u8Status, local_u8ID, local_u8Pass[4];
    u8 i, match;

    /* Check Admin - Only allowed from Terminal */
    if (copy_u8Channel == LOGIN_CH_TERMINAL)
    {
        EEPROM_voidReadByte(ADMIN_START_ADDR, &local_u8Status);
        if(local_u8Status == 1)
        {
            EEPROM_voidReadByte(ADMIN_START_ADDR + 1, &local_u8ID);
            if(local_u8ID == copy_u8UserID)
            {
                match = 1;
                for(i=0; i<4; i++)
                {
                    EEPROM_voidReadByte(ADMIN_START_ADDR + 2 + i, &local_u8Pass[i]);
                    if(local_u8Pass[i] != copy_pu8Password[i])
                    {
                        match = 0;
                        break;
                    }
                }
                if(match)
                {
                    Login_u8FailedAttempts = 0;
                    return LOGIN_ADMIN_ROLE;
                }
            }
        }
    }

    /* Check Users - Allowed from both channels */
    for(u8 u=0; u<MAX_USERS; u++)
    {
        u16 addr = USERS_START_ADDR + (u * USER_ENTRY_SIZE);
        EEPROM_voidReadByte(addr, &local_u8Status);
        if(local_u8Status == 1)
        {
            EEPROM_voidReadByte(addr + 1, &local_u8ID);
            if(local_u8ID == copy_u8UserID)
            {
                match = 1;
                for(i=0; i<4; i++)
                {
                    EEPROM_voidReadByte(addr + 2 + i, &local_u8Pass[i]);
                    if(local_u8Pass[i] != copy_pu8Password[i])
                    {
                        match = 0;
                        break;
                    }
                }
                if(match)
                {
                    Login_u8FailedAttempts = 0;
                    return LOGIN_USER_ROLE;
                }
            }
        }
    }

    /* Authentication Failed */
    Login_u8FailedAttempts++;
    if(Login_u8FailedAttempts >= 3)
    {
        Alarm_voidTrigger();
    }
    return LOGIN_NO_ROLE;
}

void Login_voidRegisterUser(u8 copy_u8UserID, u8* copy_pu8Password)
{
    /* Find empty slot */
    u8 local_u8Status;
    for(u8 u=0; u<MAX_USERS; u++)
    {
        u16 addr = USERS_START_ADDR + (u * USER_ENTRY_SIZE);
        EEPROM_voidReadByte(addr, &local_u8Status);
        if(local_u8Status != 1) // Empty
        {
            EEPROM_voidWriteByte(addr, 1); // Active
            EEPROM_voidWriteByte(addr + 1, copy_u8UserID);
            for(int i=0; i<4; i++)
                EEPROM_voidWriteByte(addr + 2 + i, copy_pu8Password[i]);
            return;
        }
    }
}

void Login_voidRemoveUser(u8 copy_u8UserID)
{
    u8 local_u8Status, local_u8ID;
    for(u8 u=0; u<MAX_USERS; u++)
    {
        u16 addr = USERS_START_ADDR + (u * USER_ENTRY_SIZE);
        EEPROM_voidReadByte(addr, &local_u8Status);
        if(local_u8Status == 1)
        {
            EEPROM_voidReadByte(addr + 1, &local_u8ID);
            if(local_u8ID == copy_u8UserID)
            {
                EEPROM_voidWriteByte(addr, 0); // Deactivate
                return;
            }
        }
    }
}

u8 Login_u8GetFailedAttempts(void)
{
    return Login_u8FailedAttempts;
}

u8 Login_u8GetUser(u8 copy_u8Index, u8* copy_pu8ID)
{
    u8 local_u8Status;
    if (copy_u8Index >= MAX_USERS) return 0;
    
    u16 addr = USERS_START_ADDR + (copy_u8Index * USER_ENTRY_SIZE);
    EEPROM_voidReadByte(addr, &local_u8Status);
    
    if (local_u8Status == 1)
    {
        EEPROM_voidReadByte(addr + 1, copy_pu8ID);
        return 1;
    }
    return 0;
}
u8 Login_u8CheckID(u8 copy_u8ID)
{
    u8 local_u8Status, local_u8ID;
    
    // Check Admin ID
    EEPROM_voidReadByte(ADMIN_START_ADDR, &local_u8Status);
    if(local_u8Status == 1)
    {
        EEPROM_voidReadByte(ADMIN_START_ADDR + 1, &local_u8ID);
        if(local_u8ID == copy_u8ID) return 1;
    }

    // Check Users
    for(u8 u=0; u<MAX_USERS; u++)
    {
        u16 addr = USERS_START_ADDR + (u * USER_ENTRY_SIZE);
        EEPROM_voidReadByte(addr, &local_u8Status);
        if(local_u8Status == 1)
        {
            EEPROM_voidReadByte(addr + 1, &local_u8ID);
            if(local_u8ID == copy_u8ID) return 1;
        }
    }
    return 0;
}
