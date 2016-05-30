// Project: Example5-Thermistor
// Kit: CY8CKIT-021 Sheild
// Baseboard: CY8CKit-44 PSoC4M
//
// This project demonstrates the reading of temperature using a thermistor
// the analog-to-digital convertor and the Thermistor component.
//
// The thermistor is in a stack with a 10k 1% reference resistor.
// 
// This measurement depends on the VDDA of the chip to exactly what you set it to
// if not the temperature will read high or low
//
// The output will be in degrees celcius * 100
//
// I used the LUT so that I wouldnt have to include the math library

#include <project.h>

#define THERMISTOR_CHAN (0)

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
            int16 result = adc_GetResult16(THERMISTOR_CHAN); // counts of thermistor
            int16 mv = adc_CountsTo_mVolts(THERMISTOR_CHAN,result); // voltage of thermistor
            // you calculate the voltage of the reference resistor by subtracting from
            // vdda (its high node)
            uint32 res = Thermistor_GetResistance(CYDEV_VDDA_MV-mv,mv);
            int16 degrees = Thermistor_GetTemperature(res);
            LCD_Write7SegNumber_0(degrees,0,1);
        }
        
    }
}
