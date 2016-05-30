// Project: Example6- Capsense
// Kit: CY8CKIT-021 Sheild
// Baseboard: CY8CKit-44 PSoC4M
//
// This project demonstrated using the CapSense Buttons.  It uses
// the V2.x component which has now been superseeded by the V3.0
//
// This project will turn on the LED coresponding to the CapSense
// button that is being touched.  I use the "!" operator to invert
// the result of the button because the LEDs are active LOW (meaning
// that a 0 results in them lighting up)
#include <project.h>

int main()
{
    CyGlobalIntEnable;
    CapSense_Start();
    CapSense_InitializeEnabledBaselines();
    CapSense_ScanEnabledWidgets();

    for(;;)
    {
        if(!CapSense_IsBusy())
        {
            LED0_Write(!CapSense_CheckIsWidgetActive(CapSense_BUTTON0__BTN));
            LED1_Write(!CapSense_CheckIsWidgetActive(CapSense_BUTTON1__BTN));
            CapSense_UpdateEnabledBaselines();
            CapSense_ScanEnabledWidgets();
        }
    }
}

/* [] END OF FILE */
