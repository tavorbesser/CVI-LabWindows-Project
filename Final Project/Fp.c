/*
  	########################################
	########################################
	######          Project 	  ######
	######  Tavor Besser  		  ######
	########################################
        ########################################
*/
//#include <cviauto.h>
#include <analysis.h>
#include <utility.h>
#include <tcpsupp.h>
#include <cvintwrk.h>
#include <rs232.h>
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "Fp.h"


#define GRAPH_TEMPERATURE 20
#define GRAPH_HUMIDITY 20
#define MAX_DATA_SIZE 35 // Maximum size of the received data from the arduino
#define MAX_ARRAY_SIZE 20 // Maximum size of the arrays - How Many Time To Read From The Arduino
static float temperatureArray[MAX_ARRAY_SIZE]; // Array to store temperature values
static float humidityArray[MAX_ARRAY_SIZE];    // Array to store humidity values
static int index = 0;                          // Index for storing values in the arrays
static char buffer[MAX_DATA_SIZE];   // Buffer to store received data
static int connect= 1;
static int panelHandle,panelHandle2,panelHandle3;
static int COM_PORT;
static int Hot_Temp,Cold_Temp;
double timeArray[MAX_ARRAY_SIZE];



int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "Fp.uir", PANEL)) < 0)
		return -1;
	if ((panelHandle2 = LoadPanel (0, "Fp.uir", PANEL_2)) < 0)
		return -1;
	if ((panelHandle3 = LoadPanel (0, "Fp.uir", PANEL_3)) < 0)
		return -1;
	
	
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	//Close the open COM port before exiting//
	CloseCom (COM_PORT);
	return 0;
}

int CVICALLBACK QuitFunc (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface (0);
			break;
	}
	return 0;
}
 int CVICALLBACK QuitCallback2 (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			HidePanel (panelHandle2);
			break;
	}
	return 0;
}
int CVICALLBACK QuitCallback3 (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			HidePanel (panelHandle3);
			break;
	}
	return 0;
}

int CVICALLBACK ConnectFunc (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
			int Error;
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_COM, &COM_PORT); 				// Get The Com Port
			GetCtrlVal (panelHandle, PANEL_Hot_NUMERIC, &Hot_Temp); 		// Get The Hot Temp
			GetCtrlVal (panelHandle, PANEL_Cold_NUMERIC, &Cold_Temp); 		// Get The Cold Temp

			Error = OpenComConfig (COM_PORT, "", 9600, 0, 8, 1, 512, 512);
			if (Error < 0) //error occurred 
            {  
				MessagePopup ("RS232 Error Message",GetRS232ErrorString (Error));   //RS232 Error message
				SetCtrlAttribute (panelHandle, PANEL_LED_OFF, ATTR_VISIBLE, 1);	    //Enable black led
				SetCtrlAttribute (panelHandle, PANEL_LED_ON, ATTR_VISIBLE, 0); 		//Disable red led
				
				return 0;
            }
			else //connection succeed
			{
				SetCtrlAttribute (panelHandle, PANEL_LED_ON, ATTR_VISIBLE, 1);  //Enable Green led
				SetCtrlAttribute (panelHandle, PANEL_LED_OFF, ATTR_VISIBLE, 0); //Disable Red led
				FlushInQ (COM_PORT); 											//Removes all characters from the input COM port queue
				InstallComCallback (COM_PORT, LWRS_RXFLAG, 0, 0, 0, 0);
				MessagePopup ("RS232 succsess Message", "Connection Succeed");  //Connection Pop-up Message
				SetCtrlAttribute (panelHandle, PANEL_Load, ATTR_DIMMED, 0); 	//Enable Load data
				SetCtrlAttribute (panelHandle, PANEL_CONNECT, ATTR_DIMMED, 1);  //Disable connect
			}
			break;
	}
	return 0;
}

int CVICALLBACK Load_Data (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
 		while (1)
    {
        int bytesRead = ComRd(COM_PORT, (char*)buffer, sizeof(buffer) -1);
        buffer[bytesRead] = '\0';  // Add null termination

        if (bytesRead > 0 && index<MAX_ARRAY_SIZE)
        {
            printf("Received:%s\n", buffer);

            float temperature, humidity;
            sscanf(buffer,"Temperature:%f Humidity:%f", &temperature, &humidity);
            temperatureArray[index] = temperature;
            humidityArray[index] = humidity;
			
			
			
//********************* Plot Settings *********************************
			double tempDoubleArray[MAX_ARRAY_SIZE];
            double humidityDoubleArray[MAX_ARRAY_SIZE];
			
            int numPoints = index < MAX_ARRAY_SIZE ? index : MAX_ARRAY_SIZE;

			for (int i = 0; i < numPoints; i++) {
                tempDoubleArray[i] = (double)temperatureArray[i];
                humidityDoubleArray[i] = (double)humidityArray[i];
            }
			
			if (numPoints > 0) {
			PlotY (panelHandle3, PANEL_3_GRAPH_TEMP, tempDoubleArray, numPoints, VAL_DOUBLE, VAL_FAT_LINE, VAL_DOUBLE, VAL_AUTOSCALE, VAL_AUTOSCALE, VAL_BLUE);
            PlotY(panelHandle3, PANEL_3_GRAPH_Humi, humidityDoubleArray, numPoints, VAL_DOUBLE, VAL_FAT_LINE, VAL_DOUBLE, VAL_AUTOSCALE, VAL_AUTOSCALE, VAL_RED);
			}
			
//********************* Plot Settings *********************************
		
//********************* Control The Temp Leds**************************
			 if(temperature>Hot_Temp)
			 {
			 SetCtrlAttribute (panelHandle2, PANEL_2_Hot_Led, ATTR_VISIBLE, 1);
			 SetCtrlAttribute (panelHandle2, PANEL_2_Comfort_Led, ATTR_VISIBLE, 0);
			 SetCtrlAttribute (panelHandle2, PANEL_2_Cold_Led, ATTR_VISIBLE, 0);
			 }
			 else if(Cold_Temp<temperature<Hot_Temp)
			 {
			 SetCtrlAttribute (panelHandle2, PANEL_2_Hot_Led, ATTR_VISIBLE, 0);
			 SetCtrlAttribute (panelHandle2, PANEL_2_Comfort_Led, ATTR_VISIBLE, 1);
			 SetCtrlAttribute (panelHandle2, PANEL_2_Cold_Led, ATTR_VISIBLE, 0);
			 }
			 else if(temperature<Cold_Temp)
			 {
			 SetCtrlAttribute (panelHandle2, PANEL_2_Hot_Led, ATTR_VISIBLE, 0);
			 SetCtrlAttribute (panelHandle2, PANEL_2_Comfort_Led, ATTR_VISIBLE, 0);
			 SetCtrlAttribute (panelHandle2, PANEL_2_Cold_Led, ATTR_VISIBLE, 1);
			 }
//********************* Control The Temp Leds**************************
			SetCtrlVal (panelHandle2, PANEL_2_Temprature, temperature); //Update temp_Bar
			SetCtrlVal (panelHandle2, PANEL_2_Humidity, humidity); 	    //Update Humidity_Bar
			index++;
            if (index >= MAX_ARRAY_SIZE)
            {
                
			 index ==0;
			 break;
				
            }
			
        }//Close The if
		
    }//Close The While

}//Close The Switch
    return 0;
}

void CVICALLBACK Open_Data_Bars (int menuBar, int menuItem, void *callbackData,
								 int panel)
{
  		DisplayPanel (panelHandle2);
}

void CVICALLBACK Open_Graph_Panel (int menuBar, int menuItem, void *callbackData,
								   int panel)
{
		DisplayPanel (panelHandle3);
}

int CVICALLBACK DisconnectFunc (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		int RS232CloseError;
		case EVENT_COMMIT:
			if(connect==1)
			{
				//flagthread=1;
				Delay(1);
				//CmtReleaseThreadPoolFunctionID (DEFAULT_THREAD_POOL_HANDLE, threadId1); //relese thread
				FlushInQ (COM_PORT); //Removes all characters from the input COM port queue
				RS232CloseError=CloseCom (COM_PORT); //Closes the COM port
				SetCtrlAttribute (panelHandle, PANEL_CONNECT, ATTR_DIMMED, 0); //Enable connect

				if (RS232CloseError < 0) //error occurred 
	            {  
					MessagePopup ("RS232 Error Message",GetRS232ErrorString (RS232CloseError)); //RS232 Error message
					return 0;
	            }
				else //End connection succeed
				{
					
					SetCtrlVal (panelHandle2, PANEL_2_Temprature, 0.00); //Reset temp_Bar
					SetCtrlVal (panelHandle2, PANEL_2_Humidity, 0.00); //Reset Humidity_Bar
					MessagePopup ("", "Connection Ended");


				}
			}
			break;
	}
	return 0;
}

int CVICALLBACK Save_Temp_GraphFunc (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
			int Bitmap;
		case EVENT_COMMIT:
			GetCtrlDisplayBitmap (panelHandle3, PANEL_3_GRAPH_TEMP, 1, &Bitmap);
			SaveBitmapToPNGFile (Bitmap, "Temp_Graph.PNG");//save photo of temp the graph
			DiscardBitmap (Bitmap);
			break;
	}
	return 0;
}

int CVICALLBACK Save_Humi_GraphFunc (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
			int Bitmap;
		case EVENT_COMMIT:
			GetCtrlDisplayBitmap (panelHandle3, PANEL_3_GRAPH_Humi, 1, &Bitmap);
			SaveBitmapToPNGFile (Bitmap, "Humi_Graph.PNG");//save photo of temp the graph
			DiscardBitmap (Bitmap);
			break;
	}
	return 0;
}

////******************************************************************//////////









