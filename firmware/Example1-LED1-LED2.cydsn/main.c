// Project: Example1-LED
// Kit: CY8CKIT-021 Sheild
// Baseboard: CY8CKit-44 PSoC4M
//
// This project uses one TCPWM to flash the two LEDs alternating @1hz.
// using the line and linen (aka complement) output.
// The CPU doesnt do anything so I put it to sleep.

#include <project.h>

int main()
{
    PWM_Start();
    for(;;)
    {
        CySysPmSleep();
    }
}
