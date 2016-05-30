// Project: Example3-LCD
// Kit: CY8CKIT-021 Sheild
// Baseboard: CY8CKit-44 PSoC4M
//
// This project demonstrates that the LCD is working by printing
// (0000-1111-2222-3333-4444-5555-6666-7777-8888-9999) onto the display
// one number every 400ms

#include <project.h>

int main()
{
    LCD_Start();
    for(;;)
    {
        int i;
        for(i=0;i<10;i++) // Loop through the digits 0-9 and print them on the screen
        {
            LCD_Write7SegDigit_0(i,0);
            LCD_Write7SegDigit_0(i,1);
            LCD_Write7SegDigit_0(i,2);
            LCD_Write7SegDigit_0(i,3);
            
            // i%2 will alternate 0 (if i is event) and 1 (if i is odd)
            LCD_WritePixel(LCD_COLON,i%2);
            LCD_WritePixel(LCD_DP1,i%2);
            LCD_WritePixel(LCD_DP2,i%2);
            LCD_WritePixel(LCD_DP3,i%2);
            
            CyDelay(1000);
        }
    }
}
