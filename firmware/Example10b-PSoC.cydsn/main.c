// Project: Example10b - PSoC
// Kit: CY8CKIT-021 Sheild
// Baseboard: CY8CKit-44 PSoC4M
//
// This project demonstrates the simplest connection to the PRoC and BLE
// It updates the LED0 based on writes from the PRoC side
// It sends out updates to the PRoC based on button processes
#include <project.h>

int main()
{
    CyGlobalIntEnable;
    
    BLEIOT_Start();
    CapSense_Start();
    CapSense_InitializeEnabledBaselines();
    CapSense_ScanEnabledWidgets();
    
    for(;;)
    {
        if(!CapSense_IsBusy())
        {
            uint8 b0=CapSense_CheckIsWidgetActive(CapSense_BUTTON0__BTN);
            if(b0 != BLEIOT_local.button0) // if the state has changed then send an update
                BLEIOT_updateButton0(b0);
            CapSense_UpdateEnabledBaselines();
            CapSense_ScanEnabledWidgets();
        }
        
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_LED0)  // if the PRoC side send an update, write it
        {
            BLEIOT_updateLed0(BLEIOT_remote.led0);
            led0_Write(!BLEIOT_local.led0); // the led is active low
        }
    }
}
