#include "My_GUI_CB.h"
#include "GUI.h"
#include "DIALOG.h"

extern WM_HWIN My_Menu_hWin;
extern WM_HWIN My_Data_hWin;
extern WM_HWIN My_Uart_hWin;

extern const GUI_WIDGET_CREATE_INFO My_Data_aDialogCreate[];
extern const GUI_WIDGET_CREATE_INFO My_Uart_aDialogCreate[];
extern const GUI_WIDGET_CREATE_INFO My_Menu_aDialogCreate[];

void My_Data_cbDialog(WM_MESSAGE * pMsg);
void My_Uart_cbDialog(WM_MESSAGE * pMsg);
void My_Menu_cbDialog(WM_MESSAGE * pMsg);

//WM_HWIN My_Menu_ID_BUTTON_0_CLICKED_CB( void )
