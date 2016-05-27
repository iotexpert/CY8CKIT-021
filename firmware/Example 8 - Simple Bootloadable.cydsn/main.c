// Project: Example8- Simple Bootloadable
// Kit: CY8CKIT-021 Sheild
// Baseboard: CY8CKit-44 PSoC4M
//
// This project demonstrates a very simple bootloadable application.  It is linked
// to the bootloader project "I2C_Bootloader"
//
// The project jusdt sits there and blinks the blue LED until something other than
// 0 is written into the I2C register.  When that happens it starts the bootloader
// 

#include <project.h>

int main()
{
    CyGlobalIntEnable; 

    uint8 buff[] = {0};
    
    PWM_Start();

    EZI2C_Start();
    EZI2C_EzI2CSetBuffer1(sizeof(buff),1,buff);

    for(;;)
    {
        if(buff[0] !=0) //if they write something other than 0 then start the Bootloader
        {
            Bootloadable_Load();
        }
    }
}
