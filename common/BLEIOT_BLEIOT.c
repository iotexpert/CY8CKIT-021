#include "project.h"
#include "BLEIOT_BLEIOT.h"

BLEIOT_SystemStatus BLEIOT_local;
BLEIOT_SystemStatus BLEIOT_remote;
uint8 BLEIOT_localDirty=0;
uint8 BLEIOT_remoteDirty=0;

int count;
int BLEIOT_initVar=0;


void BLEIOT_TriggerSystem(void);
void BLEIOT_Transmit();
void BLEIOT_Receive();

void BLEIOT_writeBlue(uint8 val)
{
    if(BLEIOT_local.blue != val)
    {
        BLEIOT_local.blue = val;
        BLEIOT_localDirty = 1;
    }
}

uint8 inline BLEIOT_readBlue() 
{
    return BLEIOT_remote.blue;
}

void BLEIOT_writeLed0(uint8 val)
{
    if(BLEIOT_local.led0 != val)
    {
        BLEIOT_local.led0 = val;
        BLEIOT_localDirty = 1;
    }
}

uint8 inline BLEIOT_readLed0() 
{
    return BLEIOT_remote.led0;
}

void BLEIOT_writeLed1(uint8 val)
{
    if(BLEIOT_local.led1 != val)
    {
        BLEIOT_local.led1 = val;
        BLEIOT_localDirty = 1;
    }
}

uint8 inline BLEIOT_readLed1() 
{
    return BLEIOT_remote.led1;
}


inline int BLEIOT_isUpdated()
{
    if(BLEIOT_remoteDirty)
    {
        BLEIOT_remoteDirty = 0; // clear on read
        return 1;
    }
    return 0;
}

void BLEIOT_TriggerSystem()
{
    if(BLEIOT_UART_SpiUartGetRxBufferSize() == sizeof(BLEIOT_SystemStatus))
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
    if(!BLEIOT_localDirty || BLEIOT_UART_SpiUartGetTxBufferSize())
        return;
    BLEIOT_localDirty = 0;
    BLEIOT_UART_SpiUartPutArray((uint8 *)&BLEIOT_local,sizeof(BLEIOT_SystemStatus));
}

void BLEIOT_Receive()
{
    int i;
    uint8 *buff;
    buff = (uint8 *)&BLEIOT_remote;
    BLEIOT_remoteDirty = 1;
    for(i=0;i<sizeof(BLEIOT_SystemStatus);i++)
    {
        *buff++ = BLEIOT_UART_SpiUartReadRxData();
    }
}
