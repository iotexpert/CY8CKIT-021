// Project: Example7- Capsense
// Kit: CY8CKIT-021 Sheild
// Baseboard: CY8CKit-44 PSoC4M
//
// This project demonstrated using the CapSense Buttons.  It uses
// the V3.0 component.
//
// This project will turn on the LED coresponding to the CapSense
// button that is being touched.  I use the "!" operator to invert
// the result of the button because the LEDs are active LOW (meaning
// that a 0 results in them lighting up)

#include <project.h>

int main()
{
    CyGlobalIntEnable;
    
    EZI2C_Start();
    // Set the I2C to read from the CapSense Registers. Settings from the Component Datasheet
    EZI2C_EzI2CSetBuffer1(sizeof(CapSense_dsRam),sizeof(CapSense_dsRam),(uint8 *)&CapSense_dsRam);
    CapSense_Start();
    CapSense_InitializeAllBaselines();
    CapSense_ScanAllWidgets();
    
    for(;;)
    {
        if(!CapSense_IsBusy())
        {
            CapSense_ProcessAllWidgets();
            CapSense_RunTuner();
            
            LED0_Write(!CapSense_IsWidgetActive(CapSense_BUTTON0_WDGT_ID));
            LED1_Write(!CapSense_IsWidgetActive(CapSense_BUTTON1_WDGT_ID));
            CapSense_UpdateAllBaselines();
            CapSense_ScanAllWidgets();
        }
    }
}

/* [] END OF FILE */
