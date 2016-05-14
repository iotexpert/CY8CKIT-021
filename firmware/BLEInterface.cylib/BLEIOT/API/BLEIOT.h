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
BlueStates BLEIOT_readRemoteBlue();
BlueStates BLEIOT_readLocalBlue();

void BLEIOT_sendUpdateLed0(uint8);
uint8 BLEIOT_readRemoteLed0();
uint8 BLEIOT_readLocalLed0();

void BLEIOT_sendUpdateLed1(uint8);
uint8 BLEIOT_readRemoteLed1();
uint8 BLEIOT_readLocalLed1();

void BLEIOT_sendUpdateBleState(BleStates);
BleStates BLEIOT_readLocalBleState();
BleStates BLEIOT_readRemoteBleState();

void BLEIOT_sendUpdateButton0(uint8);
uint8 BLEIOT_readLocalButton0();
uint8 BLEIOT_readRemoteButton0();

void BLEIOT_sendUpdateButton1(uint8);
uint8 BLEIOT_readLocalButton1();
uint8 BLEIOT_readRemoteButton1();

void BLEIOT_sendUpdateTrim(int16);
int16 BLEIOT_readLocalTrim();
int16 BLEIOT_readRemoteTrim();

void BLEIOT_sendUpdateContrast(uint8);
uint8 BLEIOT_readLocalContrast();
uint8 BLEIOT_readRemoteContrast();

void BLEIOT_sendUpdateDisplay(uint16);
uint16 BLEIOT_readLocalDisplay();
uint16 BLEIOT_readRemoteDisplay();

void BLEIOT_sendUpdateTone(uint16);
uint16 BLEIOT_readLocalTone();
uint16 BLEIOT_readRemoteTone();


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

#endif