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
    blue_Write(LED_OFF);    
    for(;;)
    {
        if(BLEIOT_isUpdated())
        {
            blue_Write(!BLEIOT_readBlue());
        }
        
        BLEIOT_writeLed0(BLEIOT_readBlue());
        BLEIOT_writeLed1(BLEIOT_readBlue());

          
    }
     
}

/* [] END OF FILE */
