#ifndef BLEIOT_H
#define BLEIOT_H
#include "cytypes.h"
   
void BLEIOT_Start();
int BLEIOT_isUpdated();

void BLEIOT_writeBlue(uint8);
uint8 BLEIOT_readBlue();

void BLEIOT_writeLed0(uint8);
uint8 BLEIOT_readLed0();

void BLEIOT_writeLed1(uint8);
uint8 BLEIOT_readLed1();

typedef struct BLEIOT_SystemStatus {
    uint8 blue;
    uint8 led0;
    uint8 led1;
    uint8 button0;
    uint8 button1;
    int16 trim;
    uint8 lcdcontrast;
    uint8 bootload;
    uint16 display;
    uint16 tone;
    uint8 bleConnected;
} __attribute__((packed)) BLEIOT_SystemStatus;

#endif
    