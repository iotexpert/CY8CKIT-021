#include "project.h"

BLEIOT_SystemStatus BLEIOT_local;
BLEIOT_SystemStatus BLEIOT_remote;

uint32 BLEIOT_dirtyFlags=0;

int count;
int BLEIOT_initVar=0;

void BLEIOT_TriggerSystem(void);
void BLEIOT_Transmit();
void BLEIOT_Receive();

void BLEIOT_sendUpdate(uint32 mask,void *local,void *remote,void *newVal,int size)
{
    if(!memcmp(remote,newVal,size))
    {
        BLEIOT_dirtyFlags &= ~mask;
    }
    BLEIOT_local.updatedFlags |= mask;

    memcpy(local,newVal,size);
}

inline void BLEIOT_sendUpdateBlue(BlueStates val)
{
    BLEIOT_sendUpdate(BLEIOT_FLAG_BLUE,&BLEIOT_local.blue,&BLEIOT_remote.blue,&val,sizeof(BLEIOT_local.blue));
}

inline void BLEIOT_sendUpdateLed0(uint8 val)
{
    BLEIOT_sendUpdate(BLEIOT_FLAG_LED0,&BLEIOT_local.led0,&BLEIOT_remote.led0,&val,sizeof(BLEIOT_local.led0));
}

inline void BLEIOT_sendUpdateLed1(uint8 val)
{
    BLEIOT_sendUpdate(BLEIOT_FLAG_LED1,&BLEIOT_local.led1,&BLEIOT_remote.led1,&val,sizeof(BLEIOT_local.led1));
}
inline void BLEIOT_sendUpdateBleState(BleStates val)
{
    BLEIOT_sendUpdate(BLEIOT_FLAG_BLESTATE,&BLEIOT_local.bleState,&BLEIOT_remote.bleState,&val,sizeof(BLEIOT_remote.bleState));
}
inline void BLEIOT_sendUpdateButton0(uint8 val)
{
    BLEIOT_sendUpdate(BLEIOT_FLAG_BUTTON0,&BLEIOT_local.button0,&BLEIOT_remote.button0,&val,sizeof(BLEIOT_remote.button0));
}

inline void BLEIOT_sendUpdateButton1(uint8 val)
{
    BLEIOT_sendUpdate(BLEIOT_FLAG_BUTTON1,&BLEIOT_local.button1,&BLEIOT_remote.button1,&val,sizeof(BLEIOT_remote.button1));
}

inline void BLEIOT_sendUpdateTrim(int16 val)
{
    BLEIOT_sendUpdate(BLEIOT_FLAG_TRIM,&BLEIOT_local.trim,&BLEIOT_remote.trim,&val,sizeof(BLEIOT_remote.trim));
}


inline void BLEIOT_sendUpdateTemperature(int16 val)
{
    BLEIOT_sendUpdate(BLEIOT_FLAG_TEMPERATURE,&BLEIOT_local.temperature,&BLEIOT_remote.temperature,&val,sizeof(BLEIOT_remote.temperature));
}

inline void BLEIOT_sendUpdateContrast(uint8 val)
{
    BLEIOT_sendUpdate(BLEIOT_FLAG_CONTRAST,&BLEIOT_local.contrast,&BLEIOT_remote.contrast,&val,sizeof(BLEIOT_remote.contrast));
}

inline void BLEIOT_sendUpdateDisplay(uint16 val)
{
    BLEIOT_sendUpdate(BLEIOT_FLAG_DISPLAY,&BLEIOT_local.display,&BLEIOT_remote.display,&val,sizeof(BLEIOT_remote.display));
}

inline void BLEIOT_sendUpdateTone(uint16 val)
{
    BLEIOT_sendUpdate(BLEIOT_FLAG_TONE,&BLEIOT_local.tone,&BLEIOT_remote.tone,&val,sizeof(BLEIOT_remote.tone));
}

////////////////////////////////////////////////////////////////

void BLEIOT_TriggerSystem()
{
    if(BLEIOT_UART_SpiUartGetRxBufferSize() == sizeof(BLEIOT_SystemStatus))
    {
        BLEIOT_Receive();
        count = 10; // schedule your transmit to happen 10ms after the receive
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
    if(BLEIOT_initVar == 0) // this can only happen if all of the systick vectors are taken
            CYASSERT(1);

    BLEIOT_local.blue = BLECONTROL;
    BLEIOT_remote.blue = BLECONTROL;
    BLEIOT_local.bleState = BLEOFF;
    BLEIOT_remote.bleState = BLEOFF;
}

void BLEIOT_Transmit()
{
    if(!BLEIOT_local.updatedFlags || BLEIOT_UART_SpiUartGetTxBufferSize())
        return;
    
    BLEIOT_UART_SpiUartPutArray((uint8 *)&BLEIOT_local,sizeof(BLEIOT_SystemStatus));
    BLEIOT_local.updatedFlags = 0;
    BLEIOT_local.bootload=0; 
}

void BLEIOT_updateDirtyFlags(void *local,void *remote,uint32 mask,int size)
{
    if(BLEIOT_remote.updatedFlags & mask)
    {
        if(memcmp(local,remote,size))
            BLEIOT_dirtyFlags |= mask;
        else
            BLEIOT_dirtyFlags &= ~mask;
        
        
    }
}

void BLEIOT_Receive()
{
    uint32 i;
    uint8 *buff;
    buff = (uint8 *)&BLEIOT_remote;

    // read the data from the UART buffer
    for(i=0;i<sizeof(BLEIOT_SystemStatus);i++)
    {
        *buff++ = BLEIOT_UART_SpiUartReadRxData();
    }
      
    BLEIOT_updateDirtyFlags(&BLEIOT_local.blue,&BLEIOT_remote.blue,BLEIOT_FLAG_BLUE,sizeof(BLEIOT_remote.blue));
    BLEIOT_updateDirtyFlags(&BLEIOT_local.bleState,&BLEIOT_remote.bleState,BLEIOT_FLAG_BLESTATE,sizeof(BLEIOT_remote.bleState));
    BLEIOT_updateDirtyFlags(&BLEIOT_local.led0,&BLEIOT_remote.led0,BLEIOT_FLAG_LED0,sizeof(BLEIOT_remote.led0));
    BLEIOT_updateDirtyFlags(&BLEIOT_local.led1,&BLEIOT_remote.led1,BLEIOT_FLAG_LED1,sizeof(BLEIOT_remote.led1));
    BLEIOT_updateDirtyFlags(&BLEIOT_local.button0,&BLEIOT_remote.button0,BLEIOT_FLAG_BUTTON0,sizeof(BLEIOT_remote.button0));
    BLEIOT_updateDirtyFlags(&BLEIOT_local.button1,&BLEIOT_remote.button1,BLEIOT_FLAG_BUTTON1,sizeof(BLEIOT_remote.button1));
    BLEIOT_updateDirtyFlags(&BLEIOT_local.display,&BLEIOT_remote.display,BLEIOT_FLAG_DISPLAY,sizeof(BLEIOT_remote.display));
    BLEIOT_updateDirtyFlags(&BLEIOT_local.contrast,&BLEIOT_remote.contrast,BLEIOT_FLAG_CONTRAST,sizeof(BLEIOT_remote.contrast));
    BLEIOT_updateDirtyFlags(&BLEIOT_local.tone,&BLEIOT_remote.tone,BLEIOT_FLAG_TONE,sizeof(BLEIOT_remote.tone));
    BLEIOT_updateDirtyFlags(&BLEIOT_local.trim,&BLEIOT_remote.trim,BLEIOT_FLAG_TRIM,sizeof(BLEIOT_remote.trim));
    BLEIOT_updateDirtyFlags(&BLEIOT_local.temperature,&BLEIOT_remote.temperature,BLEIOT_FLAG_TEMPERATURE,sizeof(BLEIOT_remote.temperature));
}