#include "project.h"

SystemStatus current;
uint8 dirty=0;
int count;
int BLEIOT_initVar=0;


void BLEIOT_TriggerSystem(void);
void BLEIOT_Transmit();
void BLEIOT_Receive();

void BLEIOT_TriggerSystem()
{
    if(BLEIOT_UART_SpiUartGetRxBufferSize() == sizeof(current)
    {
        BLEIOT_Receive();
    }
    
    if(count++ > 20)
    {
        BLEIOT_Transmit();
        count = 0;
    }
    
}

void BLEIOT_Start()
{
    int i;
    BLEIOT_UART_Start();
    CySysTickStart();
    count = 0;
    for(i=4;i>-1;i--)
    {
        if( CySysTickGetCallback(i) == NULL)
        {
            CySysTickSetCallback(i,&BLEIOT_TriggerSystem);
            BLEIOT_initVar = 0;
        }
        if(BLEIOT_initVar == 0)
            CYASSERT(1);
    }

}

void BLEIOT_Transmit()
{
    if(!dirty || BLEIOT_UART_SpiUartGetTxBufferSize())
        return;
    dirty = 0;
    BLEIOT_UART_SpiUartPutArray((uint8 *)&current,sizeof(current));
}

void BLEIOT_Receive()
{
}
