/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
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
