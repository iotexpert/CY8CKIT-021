#include "project.h"

BLEIOT_SystemStatus BLEIOT_local;
BLEIOT_SystemStatus BLEIOT_remote;
uint8 BLEIOT_localDirty=0;
uint8 BLEIOT_remoteDirty=0;

int count;
int BLEIOT_initVar=0;


void BLEIOT_TriggerSystem(void);
void BLEIOT_Transmit();
void BLEIOT_Receive();

void BLEIOT_sendUpdateBlue(uint8 val)
{
    if(BLEIOT_local.blue != val)
    {
        BLEIOT_local.blue = val;
        BLEIOT_localDirty |= BLEIOT_FLAG_BLUE;
    }
}

uint8 inline BLEIOT_readRemoteBlue() 
{
    return BLEIOT_remote.blue;
}

void BLEIOT_sendUpdateLed0(uint8 val)
{
    if(BLEIOT_local.led0 != val)
    {
        BLEIOT_local.led0 = val;
        BLEIOT_localDirty |= BLEIOT_FLAG_LED0;
    }
}

uint8 inline BLEIOT_readRemoteLed0() 
{
    return BLEIOT_remote.led0;
}

void BLEIOT_sendUpdateLed1(uint8 val)
{
    if(BLEIOT_local.led1 != val)
    {
        BLEIOT_local.led1 = val;
        BLEIOT_localDirty |= BLEIOT_FLAG_LED1;
    }
}

uint8 inline BLEIOT_readRemoteLed1() 
{
    return BLEIOT_remote.led1;
}

void BLEIOT_sendUpdateButton0(uint8 val)
{
    if(BLEIOT_local.button0 != val)
    {
        BLEIOT_local.button0 = val;
        BLEIOT_localDirty |= BLEIOT_FLAG_BUTTON0;
    }
}

uint8 inline BLEIOT_readRemotebutton0() 
{
    return BLEIOT_remote.button0;
}

void BLEIOT_sendUpdateButton1(uint8 val)
{
    if(BLEIOT_local.button1 != val)
    {
        BLEIOT_local.button1 = val;
        BLEIOT_localDirty |= BLEIOT_FLAG_BUTTON1;
    }
}

uint8 inline BLEIOT_readRemoteButton1() 
{
    return BLEIOT_remote.button1;
}

void BLEIOT_TriggerSystem()
{

    if(BLEIOT_UART_SpiUartGetRxBufferSize() == sizeof(BLEIOT_SystemStatus))
    {
        BLEIOT_Receive();
        count = 10;
     }
    
    // Update every 20ms
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
    BLEIOT_local.flags = BLEIOT_localDirty;
    BLEIOT_localDirty = 0;
    BLEIOT_UART_SpiUartPutArray((uint8 *)&BLEIOT_local,sizeof(BLEIOT_SystemStatus));
    BLEIOT_local.bootload=0; 
}

void BLEIOT_Receive()
{
    uint32 i;
    uint8 *buff;
    buff = (uint8 *)&BLEIOT_remote;
    BLEIOT_remoteDirty = 0;
    for(i=0;i<sizeof(BLEIOT_SystemStatus);i++)
    {
        *buff++ = BLEIOT_UART_SpiUartReadRxData();
    }
    if(BLEIOT_local.blue != BLEIOT_remote.blue)
        BLEIOT_remoteDirty |= BLEIOT_FLAG_BLUE;
    if(BLEIOT_local.bleConnected != BLEIOT_remote.bleConnected)
        BLEIOT_remoteDirty |= BLEIOT_FLAG_BLECONNECTED;
    if(BLEIOT_local.button0 != BLEIOT_remote.button0)
        BLEIOT_remoteDirty |= BLEIOT_FLAG_BUTTON0;
    if(BLEIOT_local.button1 != BLEIOT_remote.button1)
        BLEIOT_remoteDirty |= BLEIOT_FLAG_BUTTON1;
    
    if(BLEIOT_local.display != BLEIOT_remote.display)
        BLEIOT_remoteDirty |= BLEIOT_FLAG_DISPLAY;
 
    if(BLEIOT_local.lcdContrast != BLEIOT_remote.lcdContrast)
        BLEIOT_remoteDirty |= BLEIOT_FLAG_LCD_CONTRAST;
    
    if(BLEIOT_local.led0 != BLEIOT_remote.led0)
        BLEIOT_remoteDirty |= BLEIOT_FLAG_LED0;
 
    if(BLEIOT_local.led1 != BLEIOT_remote.led1)
        BLEIOT_remoteDirty |= BLEIOT_FLAG_LED1;
    
    if(BLEIOT_local.tone != BLEIOT_remote.tone)
        BLEIOT_remoteDirty |= BLEIOT_FLAG_TONE;
    
    if(BLEIOT_local.trim != BLEIOT_remote.trim)
        BLEIOT_remoteDirty |= BLEIOT_FLAG_TRIM;
    
}

inline uint32 BLEIOT_getRemoteFlags()
{
    return BLEIOT_remoteDirty;
}

inline uint32 BLEIOT_clearRemoteFlags(uint32 mask)
{
    BLEIOT_remoteDirty ^= mask;
    return BLEIOT_remoteDirty;
}