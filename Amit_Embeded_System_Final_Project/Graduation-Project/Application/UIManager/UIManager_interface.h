#ifndef UIMANAGER_INTERFACE_H_
#define UIMANAGER_INTERFACE_H_

#include "../../Utils/STD_TYPES.h"


void UI_voidDisplayMainMenu(void);
void UI_voidDisplayStatus(void);
void UI_voidRefreshStatus(void);
void UI_voidDisplayOptions(u8 copy_u8OptionIdx);
void UI_voidDisplayDimmerCtrl(void);
void UI_voidShowMessage(const u8* copy_pu8Msg, u16 copy_u16DelayMs);

#endif
