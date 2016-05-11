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
       blue_Write(!BLEIOT_readRemoteBlue());
        
       BLEIOT_sendUpdateLed0(BLEIOT_readRemoteBlue());
       BLEIOT_sendUpdateLed1(BLEIOT_readRemoteBlue());
      
          
    }
     
}

/* [] END OF FILE */
