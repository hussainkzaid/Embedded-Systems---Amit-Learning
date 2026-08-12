#include "../../Utils/STD_TYPES.h"
#include "../../MCAL/UART/UART_interface.h"
#include "../DeviceControl/DeviceControl_interface.h"
#include "CommHandler_interface.h"

#include "../Login/Login_interface.h"

#define MAX_CMD_LEN 20
static u8 cmdBuffer[MAX_CMD_LEN];
static u8 cmdIndex = 0;

/* Terminal Login States */
typedef enum {
    TERM_UNAUTHENTICATED,
    TERM_WAITING_ID,
    TERM_WAITING_PASS,
    TERM_AUTHENTICATED,
    TERM_WAITING_ADD_ID,
    TERM_WAITING_ADD_PASS,
    TERM_WAITING_REMOVE_ID
} TerminalState_t;

static TerminalState_t g_TerminalState = TERM_UNAUTHENTICATED;
static u8 g_u8TermUserID = 0;
static u8 g_u8TermUserPass[4];
static u8 g_u8TermRole = LOGIN_NO_ROLE;
static u8 g_u8KpdUserPermitted = 1; 
static u8 g_u8KpdLoggedIn = 0;

static u8 g_u8NewUserID = 0;
static u8 g_u8NewUserPass[4];

static void ShowMenu(void)
{
    UART_voidTxString((u8*)"\r\n--- Terminal Menu ---\r\n");
    UART_voidTxString((u8*)"1. show commands\r\n");
    if (g_u8TermRole == LOGIN_ADMIN_ROLE)
    {
        UART_voidTxString((u8*)"2. add user\r\n");
        UART_voidTxString((u8*)"3. remove user\r\n");
        if (g_u8KpdLoggedIn)
        {
            UART_voidTxString((u8*)"4. permit user\r\n");
            UART_voidTxString((u8*)"5. block user\r\n");
        }
        UART_voidTxString((u8*)"6. list users\r\n");
    }
    UART_voidTxString((u8*)"7. logout\r\n");
    UART_voidTxString((u8*)"CMD> ");
}

void Comm_voidInit(void)
{
    UART_voidInit();
    UART_voidTxString((u8*)"\r\nSmart Home System Ready.\r\n");
    UART_voidTxString((u8*)"Please enter ID: ");
    g_TerminalState = TERM_WAITING_ID;
}

void Comm_voidSendMessage(u8* msg)
{
    UART_voidTxString(msg);
}

static u8 str_cmp(u8* s1, u8* s2)
{
    while(*s1 && (*s1 == *s2))
    {
        s1++; s2++;
    }
    return (*s1 == *s2) ? 0 : 1; 
}

static u8 starts_with(u8* str, u8* prefix)
{
    while(*prefix)
    {
        if(*str != *prefix) return 1;
        str++; prefix++;
    }
    return 0;
}

static void HandleDimmer(void)
{
    u8 val = 0;
    u8 i = 4; /* skip "DIM_" */
    while(cmdBuffer[i] >= '0' && cmdBuffer[i] <= '9')
    {
        val = (val * 10) + (cmdBuffer[i] - '0');
        i++;
    }
    if(val > 100) val = 100;
    Device_voidSetLamp(DIMMER_LAMP, LAMP_ON, val);
}

static void PrintHelp(void)
{
    UART_voidTxString((u8*)"\r\nAvailable Commands:\r\n");
    UART_voidTxString((u8*)"L1_ON, L1_OFF, L2_ON, L2_OFF, L3_ON, L3_OFF\r\n");
    UART_voidTxString((u8*)"L4_ON, L4_OFF, L5_ON, L5_OFF\r\n");
    if (g_u8TermRole == LOGIN_ADMIN_ROLE)
    {
        UART_voidTxString((u8*)"DOOR_OPEN, DOOR_CLOSE (Admin Only)\r\n");
    }
    UART_voidTxString((u8*)"DIM_XXX (0-100)\r\n");
}

static void ParseCommand(void)
{
    if (g_TerminalState == TERM_WAITING_ID)
    {
        g_u8TermUserID = cmdBuffer[0];
        UART_voidTxString((u8*)"\r\nPass: ");
        g_TerminalState = TERM_WAITING_PASS;
    }
    else if (g_TerminalState == TERM_WAITING_PASS)
    {
        for(u8 i=0; i<4; i++) g_u8TermUserPass[i] = cmdBuffer[i];
        
        g_u8TermRole = Login_u8Authenticate(LOGIN_CH_TERMINAL, g_u8TermUserID, g_u8TermUserPass);
        
        if (g_u8TermRole != LOGIN_NO_ROLE)
        {
            UART_voidTxString((u8*)"\r\nLogin Success! ");
            if(g_u8TermRole == LOGIN_ADMIN_ROLE)
            {
                UART_voidTxString((u8*)"Role: Admin\r\n");
                g_u8KpdUserPermitted = 0; 
            }
            else
            {
                UART_voidTxString((u8*)"Role: User\r\n");
            }
            g_TerminalState = TERM_AUTHENTICATED;
            ShowMenu();
        }
        else
        {
            UART_voidTxString((u8*)"\r\nLogin Failed. ID: ");
            g_TerminalState = TERM_WAITING_ID;
        }
    }
    else if (g_TerminalState == TERM_WAITING_ADD_ID)
    {
        g_u8NewUserID = cmdBuffer[0];
        
        if (Login_u8CheckID(g_u8NewUserID))
        {
            UART_voidTxString((u8*)"\r\nError: ID already exists!\r\n");
            g_TerminalState = TERM_AUTHENTICATED;
            ShowMenu();
            return;
        }

        UART_voidTxString((u8*)"\r\nEnter New Password (4 digits): ");
        g_TerminalState = TERM_WAITING_ADD_PASS;
    }
    else if (g_TerminalState == TERM_WAITING_ADD_PASS)
    {
        for(u8 i=0; i<4; i++) g_u8NewUserPass[i] = cmdBuffer[i];
        Login_voidRegisterUser(g_u8NewUserID, g_u8NewUserPass);
        UART_voidTxString((u8*)"\r\nUser Added Successfully.\r\n");
        g_TerminalState = TERM_AUTHENTICATED;
        ShowMenu();
    }
    else if (g_TerminalState == TERM_WAITING_REMOVE_ID)
    {
        u8 local_u8RemID = cmdBuffer[0];
        Login_voidRemoveUser(local_u8RemID);
        UART_voidTxString((u8*)"\r\nUser Removed Successfully.\r\n");
        g_TerminalState = TERM_AUTHENTICATED;
        ShowMenu();
    }
    else if (g_TerminalState == TERM_AUTHENTICATED)
    {
        /* Menu Navigation */
        if (str_cmp(cmdBuffer, (u8*)"show commands") == 0 || str_cmp(cmdBuffer, (u8*)"1") == 0)
        {
            PrintHelp();
        }
        else if (str_cmp(cmdBuffer, (u8*)"logout") == 0 || str_cmp(cmdBuffer, (u8*)"7") == 0)
        {
            g_u8TermRole = LOGIN_NO_ROLE;
            g_TerminalState = TERM_WAITING_ID;
            UART_voidTxString((u8*)"\r\nLogged Out.\r\nID: ");
            return;
        }
        /* Admin specific commands */
        else if (g_u8TermRole == LOGIN_ADMIN_ROLE)
        {
            if(str_cmp(cmdBuffer, (u8*)"add user") == 0 || str_cmp(cmdBuffer, (u8*)"2") == 0)
            {
                UART_voidTxString((u8*)"\r\nEnter New User ID: ");
                g_TerminalState = TERM_WAITING_ADD_ID;
                return;
            }
            else if(str_cmp(cmdBuffer, (u8*)"remove user") == 0 || str_cmp(cmdBuffer, (u8*)"3") == 0)
            {
                UART_voidTxString((u8*)"\r\nEnter User ID to remove: ");
                g_TerminalState = TERM_WAITING_REMOVE_ID;
                return;
            }
            else if((str_cmp(cmdBuffer, (u8*)"permit user") == 0 || str_cmp(cmdBuffer, (u8*)"4") == 0) && g_u8KpdLoggedIn)
            {
                g_u8KpdUserPermitted = 1;
                UART_voidTxString((u8*)"\r\nKeypad user PERMITTED.\r\n");
            }
            else if((str_cmp(cmdBuffer, (u8*)"block user") == 0 || str_cmp(cmdBuffer, (u8*)"5") == 0) && g_u8KpdLoggedIn)
            {
                g_u8KpdUserPermitted = 0;
                UART_voidTxString((u8*)"\r\nKeypad user BLOCKED.\r\n");
            }

            else if(str_cmp(cmdBuffer, (u8*)"list users") == 0 || str_cmp(cmdBuffer, (u8*)"6") == 0)
            {
                UART_voidTxString((u8*)"\r\n--- Registered Users ---\r\n");
                u8 found = 0;
                u8 id;
                for(u8 i=0; i<MAX_USERS; i++)
                {
                    if (Login_u8GetUser(i, &id))
                    {
                        UART_voidTxString((u8*)"User: ");
                        UART_voidTxChar(id);
                        UART_voidTxString((u8*)"\r\n");
                        found = 1;
                    }
                }
                if (!found) UART_voidTxString((u8*)"No users found.\r\n");
                UART_voidTxString((u8*)"------------------------\r\n");
            }
        }

        /* Device control commands */
        if(str_cmp(cmdBuffer, (u8*)"L1_ON") == 0) Device_voidSetLamp(LAMP1, LAMP_ON, 0);
        else if(str_cmp(cmdBuffer, (u8*)"L1_OFF") == 0) Device_voidSetLamp(LAMP1, LAMP_OFF, 0);
        else if(str_cmp(cmdBuffer, (u8*)"L2_ON") == 0) Device_voidSetLamp(LAMP2, LAMP_ON, 0);
        else if(str_cmp(cmdBuffer, (u8*)"L2_OFF") == 0) Device_voidSetLamp(LAMP2, LAMP_OFF, 0);
        else if(str_cmp(cmdBuffer, (u8*)"L3_ON") == 0) Device_voidSetLamp(LAMP3, LAMP_ON, 0);
        else if(str_cmp(cmdBuffer, (u8*)"L3_OFF") == 0) Device_voidSetLamp(LAMP3, LAMP_OFF, 0);	
        else if(str_cmp(cmdBuffer, (u8*)"L4_ON") == 0) Device_voidSetLamp(LAMP4, LAMP_ON, 0);
        else if(str_cmp(cmdBuffer, (u8*)"L4_OFF") == 0) Device_voidSetLamp(LAMP4, LAMP_OFF, 0);
        else if(str_cmp(cmdBuffer, (u8*)"L5_ON") == 0) Device_voidSetLamp(LAMP5, LAMP_ON, 0);
        else if(str_cmp(cmdBuffer, (u8*)"L5_OFF") == 0) Device_voidSetLamp(LAMP5, LAMP_OFF, 0);
        else if(str_cmp(cmdBuffer, (u8*)"DOOR_OPEN") == 0) 
        {
            if (g_u8TermRole == LOGIN_ADMIN_ROLE) Device_voidSetDoor(DOOR_OPEN);
            else UART_voidTxString((u8*)"\r\nAccess Denied: Admin Only.\r\n");
        }
        else if(str_cmp(cmdBuffer, (u8*)"DOOR_CLOSE") == 0) 
        {
            if (g_u8TermRole == LOGIN_ADMIN_ROLE) Device_voidSetDoor(DOOR_CLOSE);
            else UART_voidTxString((u8*)"\r\nAccess Denied: Admin Only.\r\n");
        }
        else if(starts_with(cmdBuffer, (u8*)"DIM_") == 0) HandleDimmer();
        
        if (g_TerminalState == TERM_AUTHENTICATED) ShowMenu();
    }
}

void Comm_voidManage(void)
{
    u8 data;
    while(UART_u8RecieveByteNonBlocking(&data))
    {
		if((data == '\b')&&(cmdIndex > 0))
		{
				cmdIndex--;
		}
        else if(data == '\r' || data == '\n')
        {
            cmdBuffer[cmdIndex] = '\0';
            if(cmdIndex > 0)
            {
                ParseCommand();
            }
            cmdIndex = 0;
        }
        else
        {
            if(cmdIndex < MAX_CMD_LEN - 1)
            {
                cmdBuffer[cmdIndex] = data;
				cmdIndex++;
            }
        }
		UART_voidTxChar(data); 
    }
}

u8 Comm_u8IsKpdUserPermitted(void)
{
    if (g_u8TermRole != LOGIN_ADMIN_ROLE)
    {
        return 1;
    }
    return g_u8KpdUserPermitted;
}

u8 Comm_u8GetTerminalRole(void)
{
    return g_u8TermRole;
}

void Comm_voidSetKpdStatus(u8 copy_u8Status)
{
    g_u8KpdLoggedIn = copy_u8Status;
    /* If admin is logged in, refresh menu to show/hide permit/block options */
    if (g_TerminalState == TERM_AUTHENTICATED)
    {
        ShowMenu();
    }
}
