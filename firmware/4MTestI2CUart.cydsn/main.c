#include <project.h>


void buzzerPlay(int16 val)
{
     if(val == 0)
     {
        PWM_Stop();
     }
            
     int period = (155 * val)/10;
           
     PWM_Start();
     PWM_WritePeriod(period);
     PWM_WriteCompare(period>>1);
}

CY_ISR(StartBootload_ISR)
{
    BLEIOT_updateBootload(1);
    ResetTimer_ClearInterrupt(ResetTimer_INTR_MASK_TC);
    sendBootload_ClearPending();
}

int main()
{
    
    CyDelay(200);

    CyGlobalIntEnable;
    
    ResetTimer_Start();
    sendBootload_StartEx(StartBootload_ISR);
    
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
    BLEIOT_updateContrast(20);
    BLEIOT_updateTemperature(123);
    
    LCD_Write7SegNumber_0(1234,0,0);
    
    int16 temperature = 10;
    
    adc_Start();
    adc_StartConvert();
    
    for(;;)
    {
        
        if(buttonPrevious && (button_Read() == 0))
        {          
            if(BLEIOT_remote.bleState == BLEIOT_BLEOFF)
            {
                BLEIOT_updateBleState(BLEIOT_BLEON);
                
            }
            else
            {
                BLEIOT_updateBleState(BLEIOT_BLEOFF);        
            }
        }
        buttonPrevious = button_Read();
        
        if(!CapSense_IsBusy())
        {
            uint8 b0current = CapSense_CheckIsWidgetActive(CapSense_BUTTON0__BTN);
            uint8 b1current = CapSense_CheckIsWidgetActive(CapSense_BUTTON1__BTN);
            
            if(BLEIOT_local.button0 != b0current)
                BLEIOT_updateButton0(b0current);
            if(BLEIOT_local.button1 != b1current)
                BLEIOT_updateButton1(b1current);
            
            if(b0current == 1 && b0previous == 0)
            {
                BLEIOT_updateLed0(!BLEIOT_local.led0);  
                
                led0_Write(!BLEIOT_local.led0);
                temperature = temperature + 10;
                
                BLEIOT_updateTemperature(temperature);
                LCD_Write7SegNumber_0(temperature,0,1);
                BLEIOT_updateDisplay(temperature);
                
                LCD_SetContrast(temperature);
                BLEIOT_updateContrast(temperature);
                
                BLEIOT_updateTrim(temperature);
                
                BLEIOT_updatePot(0x0102);
                
            }
            if( b1current == 1 && b1previous==0)
            {   
                BLEIOT_updateLed1(!BLEIOT_local.led1);
                led1_Write(!BLEIOT_local.led1);
                
                temperature = temperature - 10;
                BLEIOT_updateTemperature(temperature);
                
                
                LCD_Write7SegNumber_0(temperature,0,1);
                BLEIOT_updateDisplay(temperature);
                
                LCD_SetContrast(temperature);
                BLEIOT_updateContrast(temperature);
                
                BLEIOT_updateTrim(temperature);
                
                if(BLEIOT_local.led1)
                {
                    
                    BLEIOT_updateTone(440);
                    buzzerPlay(BLEIOT_local.tone);
                }
                else
                {
                    
                    BLEIOT_updateTone(0);
                    buzzerPlay(BLEIOT_local.tone);
                }   
            }
      
            b0previous = b0current;
            b1previous = b1current;
                
            CapSense_UpdateEnabledBaselines();
            CapSense_ScanEnabledWidgets();
        }

        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_BLUE)
        {
            BLEIOT_updateBlue(BLEIOT_remote.blue);
        }
        
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_LED0)
        {
            BLEIOT_updateLed0(BLEIOT_remote.led0);
            led0_Write(!BLEIOT_local.led0);
        }
        
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_LED1)
        {
            BLEIOT_updateLed1(BLEIOT_remote.led1);
            led1_Write(!BLEIOT_local.led1);
        }
        
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_CONTRAST)
        {
            BLEIOT_updateContrast(BLEIOT_remote.contrast);
            LCD_SetContrast(BLEIOT_remote.contrast);
            LCD_Write7SegNumber_0(BLEIOT_remote.contrast,0,0);
        }
        
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_DISPLAY)
        {
            BLEIOT_updateDisplay(BLEIOT_remote.display);
            LCD_Write7SegNumber_0(BLEIOT_local.display,0,1);
        }
        
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_TONE)
        {
            BLEIOT_updateTone(BLEIOT_remote.tone);
           buzzerPlay(BLEIOT_local.tone);
        }
        
             
        if(adc_IsEndConversion(adc_RETURN_STATUS))
        {
            int16 result = adc_GetResult16(0);
            int16 mv = adc_CountsTo_mVolts(0,result);            
            BLEIOT_updatePot(mv);
            BLEIOT_updateDisplay(mv);
            LCD_Write7SegNumber_0(mv,0,1);
        }
        
        
        
    }
}