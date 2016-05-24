// Project: Example2-Buzzer
// Kit: CY8CKIT-021 Sheild
// Baseboard: CY8CKit-44 PSoC4M
//
// The TCPWM is used to generate a 440hz tone.  The input
// clock is set to 440 kHz and the TCPWM divdes by 1000 to acheive 440hz
// The TCPWM is turned on and off every 500 ms.  You will get beep... beep....beep.
// It uses CyDelay to pause between the beeps.  I hate using a busy wait loop
// but there it is.

#include <project.h>

int main()
{
    for(;;)
    {
        PWM_Start();
        CyDelay(500);
        PWM_Stop();
        CyDelay(500);
    }
}
