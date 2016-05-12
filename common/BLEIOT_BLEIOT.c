#include "BLEIOT_BLEIOT.h"
#include "project.h"

BLEIOT_SystemStatus BLEIOT_local;
BLEIOT_SystemStatus BLEIOT_remote;

uint8 BLEIOT_dirtyFlags=0;

int count;
int BLEIOT_initVar=0;


void BLEIOT_TriggerSystem(void);
void BLEIOT_Transmit();
void BLEIOT_Receive();

void BLEIOT_sendUpdateBlue(BlueStates val)
{
    // clear or set the dirty flag
    if(BLEIOT_remote.blue == val)
        BLEIOT_dirtyFlags &= (~BLEIOT_FLAG_BLUE);
    else
        BLEIOT_dirtyFlags |= (BLEIOT_FLAG_BLUE);
    
    BLEIOT_local.updatedFlags |= BLEIOT_FLAG_BLUE;
    
    BLEIOT_local.blue = val;
}

BlueStates inline BLEIOT_readRemoteBlue() 
{
    return BLEIOT_remote.blue;
}

void BLEIOT_sendUpdateLed0(uint8 val)
{
    // clear or set the dirty flag
    if(BLEIOT_remote.led0 == val)
        BLEIOT_dirtyFlags &= (~BLEIOT_FLAG_LED0);
    else
        BLEIOT_dirtyFlags |= (BLEIOT_FLAG_LED0);
    
        BLEIOT_local.updatedFlags |= BLEIOT_FLAG_LED0;
    
    BLEIOT_local.led0 = val;
}

uint8 inline BLEIOT_readRemoteLed0() 
{
    return BLEIOT_remote.led0;
}


void BLEIOT_sendUpdateLed1(uint8 val)
{
    // clear or set the dirty flag
    if(BLEIOT_remote.led1 == val)
        BLEIOT_dirtyFlags &= (~BLEIOT_FLAG_LED1);
    else
        BLEIOT_dirtyFlags |= (BLEIOT_FLAG_LED1);
    
        BLEIOT_local.updatedFlags |= BLEIOT_FLAG_LED1;
    
    BLEIOT_local.led1 = val;
}

uint8 inline BLEIOT_readRemoteLed1() 
{
    return BLEIOT_remote.led1;
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
    }
    if(BLEIOT_initVar == 0)
            CYASSERT(1);

    BLEIOT_local.blue = BLECONTROL;

}

void BLEIOT_Transmit()
{
    if(!BLEIOT_local.updatedFlags || BLEIOT_UART_SpiUartGetTxBufferSize())
        return;
    
    BLEIOT_UART_SpiUartPutArray((uint8 *)&BLEIOT_local,sizeof(BLEIOT_SystemStatus));
    BLEIOT_local.updatedFlags = 0;
    BLEIOT_local.bootload=0; 
}

void BLEIOT_Receive()
{
    uint32 i;
    uint8 *buff;
    buff = (uint8 *)&BLEIOT_remote;
    
    
    for(i=0;i<sizeof(BLEIOT_SystemStatus);i++)
    {
        *buff++ = BLEIOT_UART_SpiUartReadRxData();
    }
    if(BLEIOT_local.blue != BLEIOT_remote.blue)
        BLEIOT_dirtyFlags |= BLEIOT_FLAG_BLUE;
    else
        BLEIOT_dirtyFlags &= ~BLEIOT_FLAG_BLUE;
    
    if(BLEIOT_local.bleConnected != BLEIOT_remote.bleConnected)
        BLEIOT_dirtyFlags |= BLEIOT_FLAG_BLECONNECTED;
    else
        BLEIOT_dirtyFlags &= ~BLEIOT_FLAG_BLECONNECTED;
    
    if(BLEIOT_local.button0 != BLEIOT_remote.button0)
        BLEIOT_dirtyFlags |= BLEIOT_FLAG_BUTTON0;
    else
        BLEIOT_dirtyFlags &= ~BLEIOT_FLAG_BUTTON0;
    
    
    if(BLEIOT_local.button1 != BLEIOT_remote.button1)
        BLEIOT_dirtyFlags |= BLEIOT_FLAG_BUTTON1;
    else
        BLEIOT_dirtyFlags &= ~BLEIOT_FLAG_BUTTON1;
    
    if(BLEIOT_local.display != BLEIOT_remote.display)
        BLEIOT_dirtyFlags |= BLEIOT_FLAG_DISPLAY;
    else
        BLEIOT_dirtyFlags &= ~BLEIOT_FLAG_DISPLAY;
    
    if(BLEIOT_local.lcdContrast != BLEIOT_remote.lcdContrast)
        BLEIOT_dirtyFlags |= BLEIOT_FLAG_LCD_CONTRAST;
    else
        BLEIOT_dirtyFlags &= ~BLEIOT_FLAG_LCD_CONTRAST;
    
    if(BLEIOT_local.led0 != BLEIOT_remote.led0)
        BLEIOT_dirtyFlags |= BLEIOT_FLAG_LED0;
    else
         BLEIOT_dirtyFlags &= ~BLEIOT_FLAG_LED0;
 
    if(BLEIOT_local.led1 != BLEIOT_remote.led1)
        BLEIOT_dirtyFlags |= BLEIOT_FLAG_LED1;
    else
        BLEIOT_dirtyFlags &= ~BLEIOT_FLAG_LED1;
    
    if(BLEIOT_local.tone != BLEIOT_remote.tone)
        BLEIOT_dirtyFlags |= BLEIOT_FLAG_TONE;
    else
        BLEIOT_dirtyFlags &= ~BLEIOT_FLAG_TONE;
    
    if(BLEIOT_local.trim != BLEIOT_remote.trim)
        BLEIOT_dirtyFlags |= BLEIOT_FLAG_TRIM;
    else
        BLEIOT_dirtyFlags &= ~BLEIOT_FLAG_TRIM;
    
}

inline uint32 BLEIOT_getDirtyFlags()
{
    return BLEIOT_dirtyFlags;
}
