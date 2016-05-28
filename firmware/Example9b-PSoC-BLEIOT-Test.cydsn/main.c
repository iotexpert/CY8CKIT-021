// Project: Example9b-PSoC-BLEIOT-Test
// Kit: CY8CKIT-021 Sheild
// Baseboard: CY8CKit-44 PSoC4M
//
// This project demonstrates using the BLEIOT component
// If the other side writes the LED then update it
// If the user presses button 0 then send an bootload command
// If the user presses button 1 then send an update to the button

#include <project.h>

int main()
{
    CyGlobalIntEnable; 
    CapSense_Start();
    CapSense_InitializeEnabledBaselines();
    CapSense_ScanEnabledWidgets();
    
    BLEIOT_Start();
    
    for(;;)
    {
        
        if(!CapSense_IsBusy())
        {
            uint8 b0 = CapSense_CheckIsWidgetActive(CapSense_BUTTON0__BTN);
            uint8 b1 = CapSense_CheckIsWidgetActive(CapSense_BUTTON1__BTN);
            
            if(b0) BLEIOT_updateBootload(1); // send the bootload command
            
            if(b1 != BLEIOT_local.button1) // if the button state has changed send it
                BLEIOT_updateButton1(b1);
            
            CapSense_UpdateEnabledBaselines();
            CapSense_ScanEnabledWidgets();
        }
        
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_LED0) // other side wrote LED0, update state
        {
            BLEIOT_updateLed0(BLEIOT_remote.led0); // update local state
            led0_Write(!BLEIOT_local.led0); // the LED is active low
        }
    }
}
