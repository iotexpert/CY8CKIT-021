#ifndef BLEIOT_H
#define BLEIOT_H
#include "cytypes.h"

typedef enum BlueStates {
    OFF,
    ON,
    BLINK,
    BLECONTROL
} BlueStates;

void BLEIOT_Start();
uint32 BLEIOT_getDirtyFlags();


void BLEIOT_sendUpdateBlue(BlueStates);
BlueStates BLEIOT_readRemoteBlue();

void BLEIOT_sendUpdateLed0(uint8);
uint8 BLEIOT_readRemoteLed0();

void BLEIOT_sendUpdateLed1(uint8);
uint8 BLEIOT_readRemoteLed1();


#define BLEIOT_FLAG_BLUE (0x01)
#define BLEIOT_FLAG_LED0 (0x01<<1)
#define BLEIOT_FLAG_LED1 (0x01<<2)
#define BLEIOT_FLAG_BUTTON0 (0x01<<3)
#define BLEIOT_FLAG_BUTTON1 (0x01<<4)
#define BLEIOT_FLAG_TRIM (0x01<<5)
#define BLEIOT_FLAG_LCD_CONTRAST (0x01<<6)
#define BLEIOT_FLAG_DISPLAY (0x01<<7)
#define BLEIOT_FLAG_TONE (0x01<<8)
#define BLEIOT_FLAG_BLECONNECTED (0x01<<9)
#define BLEIOT_FLAG_BOOTLOAD (0x01<<10)


typedef struct BLEIOT_SystemStatus {
    uint32 updatedFlags;
    BlueStates blue;
    uint8 led0;
    uint8 led1;
    uint8 button0;
    uint8 button1;
    int16 trim;
    uint8 lcdContrast;
    uint16 display;
    uint16 tone;
    uint8 bleConnected;
    uint8 bootload;
} __attribute__((packed)) BLEIOT_SystemStatus;

#endif
    