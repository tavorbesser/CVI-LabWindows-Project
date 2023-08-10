/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1
#define  PANEL_QUITBUTTON                 2       /* control type: command, callback function: QuitFunc */
#define  PANEL_COM                        3       /* control type: numeric, callback function: (none) */
#define  PANEL_DCONNECT                   4       /* control type: command, callback function: DisconnectFunc */
#define  PANEL_CONNECT                    5       /* control type: command, callback function: ConnectFunc */
#define  PANEL_LED_OFF                    6       /* control type: LED, callback function: (none) */
#define  PANEL_LED_ON                     7       /* control type: LED, callback function: (none) */
#define  PANEL_Load                       8       /* control type: command, callback function: Load_Data */
#define  PANEL_PICTURE_2                  9       /* control type: picture, callback function: (none) */
#define  PANEL_PICTURE                    10      /* control type: picture, callback function: (none) */
#define  PANEL_Hot_NUMERIC                11      /* control type: numeric, callback function: (none) */
#define  PANEL_Cold_NUMERIC               12      /* control type: numeric, callback function: (none) */
#define  PANEL_Text                       13      /* control type: textMsg, callback function: (none) */
#define  PANEL_Text_2                     14      /* control type: textMsg, callback function: (none) */

#define  PANEL_2                          2
#define  PANEL_2_Temprature               2       /* control type: scale, callback function: (none) */
#define  PANEL_2_QUITBUTTON_2             3       /* control type: command, callback function: QuitCallback2 */
#define  PANEL_2_STRING_2                 4       /* control type: string, callback function: (none) */
#define  PANEL_2_Humidity                 5       /* control type: scale, callback function: (none) */
#define  PANEL_2_STRING                   6       /* control type: string, callback function: (none) */
#define  PANEL_2_Comfort_Led              7       /* control type: LED, callback function: (none) */
#define  PANEL_2_Cold_Led                 8       /* control type: LED, callback function: (none) */
#define  PANEL_2_Hot_Led                  9       /* control type: LED, callback function: (none) */

#define  PANEL_3                          3
#define  PANEL_3_GRAPH_TEMP               2       /* control type: graph, callback function: (none) */
#define  PANEL_3_GRAPH_Humi               3       /* control type: graph, callback function: (none) */
#define  PANEL_3_QUITBUTTON_2             4       /* control type: command, callback function: QuitCallback3 */
#define  PANEL_3_COMMANDBUTTON_2          5       /* control type: command, callback function: Save_Humi_GraphFunc */
#define  PANEL_3_COMMANDBUTTON            6       /* control type: command, callback function: Save_Temp_GraphFunc */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_MENU1                    2
#define  MENUBAR_MENU1_MENU1_2            3       /* callback function: Open_Data_Bars */
#define  MENUBAR_MENU1_ITEM1              4       /* callback function: Open_Graph_Panel */


     /* Callback Prototypes: */

int  CVICALLBACK ConnectFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DisconnectFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Load_Data(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Open_Data_Bars(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK Open_Graph_Panel(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK QuitCallback2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Save_Humi_GraphFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Save_Temp_GraphFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
