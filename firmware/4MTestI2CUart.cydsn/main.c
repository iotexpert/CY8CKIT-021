#include <project.h>



int main()
{
    
    CyDelay(200);

    CyGlobalIntEnable;
    
    int buttonPrevious = 1;
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
    
    LCD_Start();
    LCD_SetContrast(20);
    BLEIOT_sendUpdateContrast(20);
    LCD_Write7SegNumber_0(1234,0,0);
    
    
    for(;;)
    {
        
        if(buttonPrevious && (button_Read() == 0))
        {          
            if(BLEIOT_remote.bleState == BLEOFF)
            {
                BLEIOT_sendUpdateBleState(BLEON);
            }
            else
            {
                BLEIOT_sendUpdateBleState(BLEOFF);        
            }
        }
        buttonPrevious = button_Read();
        
        if(!CapSense_IsBusy())
        {
            uint8 b0current = CapSense_CheckIsWidgetActive(CapSense_BUTTON0__BTN);
            uint8 b1current = CapSense_CheckIsWidgetActive(CapSense_BUTTON1__BTN);
            
            if(BLEIOT_local.button0 != b0current)
                BLEIOT_sendUpdateButton0(b0current);
            if(BLEIOT_local.button1 != b1current)
                BLEIOT_sendUpdateButton1(b1current);
            
            if(b0current == 1 && b0previous == 0)
            {
                BLEIOT_sendUpdateLed0(!BLEIOT_local.led0);  
                led0_Write(!BLEIOT_local.led0);
            }
            if( b1current == 1 && b1previous==0)
            {   
                BLEIOT_sendUpdateLed1(!BLEIOT_local.led1);
                led1_Write(!BLEIOT_local.led1);
            }
      
            b0previous = b0current;
            b1previous = b1current;
                
            CapSense_UpdateEnabledBaselines();
            CapSense_ScanEnabledWidgets();
        }
        
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_LED0)
        {
            BLEIOT_sendUpdateLed0(BLEIOT_remote.led0);
            led0_Write(!BLEIOT_local.led0);
        }
        
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_LED1)
        {
            BLEIOT_sendUpdateLed1(BLEIOT_remote.led1);
            led1_Write(!BLEIOT_local.led1);
        }
        
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_CONTRAST)
        {
            BLEIOT_sendUpdateContrast(BLEIOT_remote.contrast);
            LCD_SetContrast(BLEIOT_remote.contrast);
            LCD_Write7SegNumber_0(BLEIOT_remote.contrast,0,0);
        }
        
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_DISPLAY)
        {
            BLEIOT_sendUpdateDisplay(BLEIOT_remote.display);
            LCD_Write7SegNumber_0(BLEIOT_local.display,0,0);
        }
        
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_TONE)
        {
            BLEIOT_sendUpdateTone(BLEIOT_remote.tone);
            
            if(BLEIOT_remote.tone)
            {
                int period = 3000000/BLEIOT_remote.tone;
               
                PWM_Start();
                PWM_WritePeriod(period);
                PWM_WriteCompare(period>>1);
            }
            else
                PWM_Stop();
        }
        
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_BLUE)
        {
            BLEIOT_sendUpdateBlue(BLEIOT_remote.blue);
        }
        
    }
}