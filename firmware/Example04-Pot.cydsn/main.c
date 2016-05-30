// Project: Example4-POT
// Kit: CY8CKIT-021 Sheild
// Baseboard: CY8CKit-44 PSoC4M
//
// This project reads an analog voltage from the onboard potentiometer
// then prints out that value in milivolts.  The ADC is configured to read up
// to 2048mv
//
// The ADC is configured to average 256 samples to help filter noise.
//
// In order for this to work, the JUMPER NEEDS TO BE SET IN THE POT POSITION ON
// the SHIELD

#include <project.h>

#define POTCHAN (0)
int main()
{
    CyGlobalIntEnable; 
    LCD_Start();
    adc_Start();
    adc_StartConvert();
    
    for(;;)
    {
        if(adc_IsEndConversion(adc_RETURN_STATUS))
        {
            int16 result = adc_GetResult16(POTCHAN);
            int16 mv = adc_CountsTo_mVolts(POTCHAN,result);
            LCD_Write7SegNumber_0(mv,0,1);
        }
    }
}
