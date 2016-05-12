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
#include "BLEIOT_BLEIOT.h"

#define LED_ON 0
#define LED_OFF 1
int main()
{

    CyGlobalIntEnable;
    BLEIOT_Start();
    //blue_Write(LED_OFF);
    
    PWM_Start();
    
    for(;;)
    {
       
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_BLUE)
        {
            switch(BLEIOT_readRemoteBlue())
            {
                case ON:
                    PWM_Stop();
                    blue_Write(1); // in HW mode sw reg is OE.. output enable=on to drive active low
                    break;
                case OFF:
                    PWM_Stop();
                    blue_Write(0); // in HW mode sw reg is OE.. output enable=off to drive tristate output
                break;
                break;
                case BLECONTROL:
                case BLINK:
                    blue_Write(1); // turn the OE back on
                    PWM_Start();
                break;

                BLEIOT_sendUpdateBlue(BLEIOT_readRemoteBlue());
                
            }
           
        } 
    }
     
}

/* [] END OF FILE */
