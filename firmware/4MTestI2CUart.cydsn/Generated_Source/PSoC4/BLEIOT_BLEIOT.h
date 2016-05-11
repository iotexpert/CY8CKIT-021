#ifndef BLEIOT_H
#define BLEIOT_H
#include "cytypes.h"
   
void BLEIOT_Start();

typedef struct SystemStatus {
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
} __attribute__((packed)) SystemStatus;

#endif
    