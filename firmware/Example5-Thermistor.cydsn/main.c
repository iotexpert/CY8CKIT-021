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
    
    LCD_Start();
    adc_Start();
    adc_StartConvert();
    
    for(;;)
    {
        if(adc_IsEndConversion(adc_RETURN_STATUS))
        {
            
            int16 result = adc_GetResult16(0);
            int16 mv = adc_CountsTo_mVolts(0,result);
            uint32 res = Thermistor_GetResistance(CYDEV_VDDA_MV-mv,mv);
            int16 degrees = Thermistor_GetTemperature(res);
            LCD_Write7SegNumber_0(degrees,0,1);
        }
        
    }
}

/* [] END OF FILE */
