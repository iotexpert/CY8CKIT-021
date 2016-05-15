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

uint8 abc[] = {01,02,03,04};

int main()
{
    
    
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    LCD_Start();
    
    int i=10;
    LCD_SetContrast(10);
    
    int b0previous=0;
    int b1previous=0;
    
    int contrast = 10;
    capsense_Start();
    capsense_InitializeEnabledBaselines();
    capsense_ScanEnabledWidgets();
    

    uint16 *v1;

    v1 = &abc[1];
    LCD_Write7SegNumber_0(*v1,0,0);
    
    
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    LCD_ClearDisplay();
    for(;;)
    {
        if(!capsense_IsBusy())
        {
        
            uint8 b1current = capsense_CheckIsWidgetActive(capsense_BUTTON1__BTN);
            uint8 b0current = capsense_CheckIsWidgetActive(capsense_BUTTON0__BTN);
            
            if(b0current == 1 && b0previous == 0)
            {
                led0_Write(!led0_Read());
                contrast += 10;
                if(contrast > 100)
                    contrast = 10;
                LCD_SetContrast(contrast);
            }
            
            if(b1current == 1 && b1previous == 0)
            {
                led1_Write(!led1_Read());
                contrast -= 10;
                if(contrast < 10)
                    contrast = 100;
                LCD_SetContrast(contrast);
            }
            b0previous = b0current;
            b1previous = b1current;
            
        capsense_UpdateEnabledBaselines();
        capsense_ScanEnabledWidgets();
        }
    }
}

/* [] END OF FILE */
