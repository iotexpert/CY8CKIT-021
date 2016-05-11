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
#include "commands.h"

#define LED_ON 0
#define LED_OFF 1
int main()
{

    CyGlobalIntEnable;
    UART_Start();
    blue_Write(LED_OFF);
    uint8 c;
    
    for(;;)
    {
        c = UART_UartGetByte();
      
        switch(c)
        {
            case CMD_BLE_BLUE_LED_ON:
                blue_Write(LED_ON);
            break;
            case CMD_BLE_BLUE_LED_OFF:
                blue_Write(LED_OFF);
            break;
            case CMD_BLE_BOOTLOAD:
                Bootloadable_Load();
            break;
                
           
        }
      
    }
}

/* [] END OF FILE */
