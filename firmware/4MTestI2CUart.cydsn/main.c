#include <project.h>

int main()
{
    CyGlobalIntEnable;
    
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
    led0_Write(!blueState);
    led1_Write(!blueState);
    
    P06_Write(1); // turn it off
    
    for(;;)
    {
        if(!CapSense_IsBusy())
        {
            uint8 b1current = CapSense_CheckIsWidgetActive(CapSense_BUTTON1__BTN);
            uint8 b0current = CapSense_CheckIsWidgetActive(CapSense_BUTTON0__BTN);
            
            if( b1current == 1 && b1previous==0)
            {                                
            
                BLEIOT_sendUpdateLed0(led0_Read());
                led0_Write(!led0_Read());
    
            }
            
            if(b0current == 1 && b0previous == 0)
            {
                if(P06_Read())
                {
                    BLEIOT_sendUpdateBleState(BLEON);
                }
                else
                {
                    BLEIOT_sendUpdateBleState(BLEOFF);
                }
                P06_Write(!P06_Read());
            }
          
            
            if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_LED0)
            {
                led0_Write(!BLEIOT_readRemoteLed0());
                BLEIOT_sendUpdateLed0(BLEIOT_readRemoteLed0());
            }
 

            b0previous = b0current;
            b1previous = b1current;
            CapSense_UpdateEnabledBaselines();
            CapSense_ScanEnabledWidgets();
        }
       /*
        switch(BLEIOT_readRemoteBleState())
        {
            case BLEOFF:
            case BLEON:
            case BLESTART:
                led0_Write(1);
                led1_Write(1);
                break;
                
            case BLEADVERTISING:
                led0_Write(1);
                led1_Write(0);
                break;

            case BLECONNECTED:
                led0_Write(0);
                led1_Write(1);
                break;

            
        }
        */
        
        //P06_Write(!BLEIOT_readRemoteBlue());
        //led0_Write(!BLEIOT_readRemoteLed0());
        //led1_Write(!BLEIOT_readRemoteLed1());      
    }
}

/* [] END OF FILE */
