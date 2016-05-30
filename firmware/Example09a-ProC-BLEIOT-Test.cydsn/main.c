// Project: Example9b-PRoC-BLEIOT-Test
// Kit: CY8CKIT-021 Sheild
// Baseboard: CY8CKit-44 PSoC4M
//
// This project should be bootloaded into the PRoC.  It demonstrates using the BLEIOT
// component.
//
// Using the systick, send an update to led0 every 500ms
// If the other side writes to Bootload... then start the bootloader
// If the other side writes to the button1... then display that on the blue led
#include <project.h>
#include "BLEIOT_BLEIOT.h"

int countMs =0;

// This is the ISR for the systick
void sendLedUpdate()
{
    if(countMs++<500) // count 500ms
        return;
    countMs = 0;
    BLEIOT_updateLed0(!BLEIOT_local.led0);
}

int main()
{

    CyGlobalIntEnable; 
    CyDelay(100);
    BLEIOT_Start();
    
    CySysTickStart(); // start the systick and register our call back
    CySysTickSetCallback(0,sendLedUpdate);
    
    for(;;)
    {
        
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_BOOTLOAD)
            Bootloadable_Load();
        
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_BUTTON1)
        {
            BLEIOT_updateButton1(BLEIOT_remote.button1);
            blue_Write(!BLEIOT_local.button1);
        }
    }
}
