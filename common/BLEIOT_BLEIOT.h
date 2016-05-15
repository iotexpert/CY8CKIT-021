#ifndef BLEIOT_H
#define BLEIOT_H
#include "cytypes.h"

typedef enum BlueStates {
    OFF=0,
    ON=1,
    BLINK=2,
    BLECONTROL=3
} BlueStates;

typedef enum BleStates {
    BLEOFF,
    BLEON,
    BLESTART,
    BLEADVERTISING,
    BLECONNECTED
} BleStates;

void BLEIOT_Start();
uint32 BLEIOT_getDirtyFlags();


void BLEIOT_sendUpdateBlue(BlueStates);
void BLEIOT_sendUpdateLed0(uint8);
void BLEIOT_sendUpdateLed1(uint8);
void BLEIOT_sendUpdateBleState(BleStates);
void BLEIOT_sendUpdateButton0(uint8);
void BLEIOT_sendUpdateButton1(uint8);
void BLEIOT_sendUpdateTrim(int16);
void BLEIOT_sendUpdateContrast(uint8);
void BLEIOT_sendUpdateDisplay(uint16);
void BLEIOT_sendUpdateTone(uint16);

#define BLEIOT_FLAG_BLUE (1<<0)
#define BLEIOT_FLAG_LED0 (1<<1)
#define BLEIOT_FLAG_LED1 (1<<2)
#define BLEIOT_FLAG_BUTTON0 (1<<3)
#define BLEIOT_FLAG_BUTTON1 (1<<4)
#define BLEIOT_FLAG_TRIM (1<<5)
#define BLEIOT_FLAG_CONTRAST (1<<6)
#define BLEIOT_FLAG_DISPLAY (1<<7)
#define BLEIOT_FLAG_TONE (1<<8)
#define BLEIOT_FLAG_BLESTATE (1<<9)
#define BLEIOT_FLAG_BOOTLOAD (1<<10)


typedef struct BLEIOT_SystemStatus {
    uint32 updatedFlags;
    BlueStates blue;
    uint8 led0;
    uint8 led1;
    uint8 button0;
    uint8 button1;
    int16 trim;
    uint8 contrast;
    uint16 display;
    uint16 tone;
    BleStates bleState;
    uint8 bootload;
} __attribute__((packed)) BLEIOT_SystemStatus;

extern BLEIOT_SystemStatus BLEIOT_local;
extern BLEIOT_SystemStatus BLEIOT_remote;

#endif