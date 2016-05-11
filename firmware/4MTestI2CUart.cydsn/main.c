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
    
    uint8 buff[] = {1,2,3,4};
    
    CapSense_Start();
    CapSense_InitializeEnabledBaselines();
    CapSense_ScanEnabledWidgets();

    BLEIOT_Start();
    EZI2C_Start();
    EZI2C_EzI2CSetBuffer1(sizeof(buff),0,buff);
    
    uint8 b1previous = 0;
    uint8 b0previous = 0;
    uint8 blueState = 0;
    
    for(;;)
    {
        if(!CapSense_IsBusy())
        {
            uint8 b1current = CapSense_CheckIsWidgetActive(CapSense_BUTTON1__BTN);
            uint8 b0current = CapSense_CheckIsWidgetActive(CapSense_BUTTON0__BTN);
            
            if( b1current == 1 && b1previous==0)
            {
                /*
                if(blueState)
                    BLEIOT_SendCommand(CMD_BLE_BLUE_LED_OFF);
                else
                    BLEIOT_SendCommand(CMD_BLE_BLUE_LED_ON);
                */
                
                blueState = !blueState;
                led1_Write(blueState);
            }
            
            if( b0current == 1 && b0previous==0)
            {
                //BLE_SendCommand(CMD_BLE_BLUE_LED_ON);
                //BLE_SendCommand(CMD_BLE_BOOTLOAD);         
                led0_Write(!led0_Read());
            }
            
            
            b0previous = b0current;
            b1previous = b1current;
            CapSense_UpdateEnabledBaselines();
            CapSense_ScanEnabledWidgets();
        }
        
    }
}

/* [] END OF FILE */
