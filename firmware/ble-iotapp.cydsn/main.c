/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include "BLEIOT_BLEIOT.h"

typedef struct NotifyFlags {
    uint8 blue;
    uint8 led0;
    uint8 led1;
    uint8 button0;
    uint8 button1;
    uint8 contrast;
    uint8 trim;
    uint8 display;
    uint8 tone;
    
} NotifyFlags;

NotifyFlags notifyFlags;

/***************************************************************
 * Function to update the LED state in the GATT database
 **************************************************************/
void processBlueLed()
{
    switch(BLEIOT_readLocalBlue())
            {
                case ON:
                    PWM_Stop();
                    blue_Write(1); // in HW mode sw reg is OE.. output enable=on to drive active low
                    break;
                case OFF:
                    PWM_Stop();
                    blue_Write(0); // in HW mode sw reg is OE.. output enable=off to drive tristate output
                break;
                case BLECONTROL:
                    if(CyBle_GetState() == CYBLE_STATE_CONNECTED)
                    {
                        PWM_Stop();
                        blue_Write(1); // in HW mode sw reg is OE.. output enable=on to drive active low
                    }
                    else
                    if(CyBle_GetState() == CYBLE_STATE_ADVERTISING)
                    {
                        blue_Write(1); // turn the OE back on
                        PWM_Start();
                    }
                    else
                    {
                        blue_Write(0);
                        PWM_Stop();
                        //blue_Write(0); // in HW mode sw reg is OE.. output enable=off to drive tristate output
                    }
                break;
                case BLINK:
                    blue_Write(1); // turn the OE back on
                    PWM_Start();
                break;
            }
}

void updateGattDB(uint8 *val,int size,uint8 notify, CYBLE_GATT_DB_ATTR_HANDLE_T handle,uint8 flags)
{
    
    //update the GATT Database
    CYBLE_GATTS_HANDLE_VALUE_NTF_T 	tempHandle;
   
    if(CyBle_GetState() != CYBLE_STATE_CONNECTED)
        return;
     
    tempHandle.attrHandle = handle;
  	tempHandle.value.val = val;
    tempHandle.value.len = size;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,flags);
    // if peer initiated then write response.
    if(flags == CYBLE_GATT_DB_PEER_INITIATED)
        CyBle_GattsWriteRsp(cyBle_connHandle);
    else if(notify) // If notify & local initiated 
    {
        CyBle_GattsNotification(cyBle_connHandle,&tempHandle);
    }    
}


/***************************************************************
 * Function to handle the BLE stack
 **************************************************************/
void BleCallBack(uint32 event, void* eventParam)
{
    CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReqParam;
    uint8 val8;

    switch(event)
    {
        /* if there is a disconnect or the stack just turned on from a reset then start the advertising and turn on the LED blinking */
        case CYBLE_EVT_STACK_ON:
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            BLEIOT_sendUpdateBleState(BLEADVERTISING);
            processBlueLed();
        break;
            
        case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
            processBlueLed();
        break;
        
            
        case CYBLE_EVT_GAP_DEVICE_CONNECTED:
            val8 = BLEIOT_readLocalBlue();
            updateGattDB(&val8,1,notifyFlags.blue,CYBLE_CY8CKIT021_BLUE_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
            BLEIOT_sendUpdateBleState(BLECONNECTED);
            processBlueLed();
		break;

        /* handle a write request */
    //uint16 display;
    //uint16 tone;
            
        case CYBLE_EVT_GATTS_WRITE_REQ:
            wrReqParam = (CYBLE_GATTS_WRITE_REQ_PARAM_T *) eventParam;
			      
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_BLUE_CHAR_HANDLE)
            {
                BLEIOT_sendUpdateBlue(wrReqParam->handleValPair.value.val[0]);
                processBlueLed();
                updateGattDB(wrReqParam->handleValPair.value.val,1,notifyFlags.blue,CYBLE_CY8CKIT021_BLUE_CHAR_HANDLE,CYBLE_GATT_DB_PEER_INITIATED);
            }

            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_LED0_CHAR_HANDLE)
            {
                BLEIOT_sendUpdateLed0(wrReqParam->handleValPair.value.val[0]);
                updateGattDB(wrReqParam->handleValPair.value.val,1,notifyFlags.led0,CYBLE_CY8CKIT021_LED0_CHAR_HANDLE,CYBLE_GATT_DB_PEER_INITIATED);
            }

            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_LED1_CHAR_HANDLE)
            {
                BLEIOT_sendUpdateLed1(wrReqParam->handleValPair.value.val[0]);
                updateGattDB(wrReqParam->handleValPair.value.val,1,notifyFlags.led0,CYBLE_CY8CKIT021_LED1_CHAR_HANDLE,CYBLE_GATT_DB_PEER_INITIATED);
            }
            
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_BUTTON0_CHAR_HANDLE)
            {
                BLEIOT_sendUpdateButton0(wrReqParam->handleValPair.value.val[0]);
                updateGattDB(wrReqParam->handleValPair.value.val,1,notifyFlags.button0,CYBLE_CY8CKIT021_BUTTON0_CHAR_HANDLE,CYBLE_GATT_DB_PEER_INITIATED);
            }
 
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_BUTTON1_CHAR_HANDLE)
            {
                BLEIOT_sendUpdateButton1(wrReqParam->handleValPair.value.val[0]);
                updateGattDB(wrReqParam->handleValPair.value.val,1,notifyFlags.button1,CYBLE_CY8CKIT021_BUTTON1_CHAR_HANDLE,CYBLE_GATT_DB_PEER_INITIATED);
            }
            
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_CONTRAST_CHAR_HANDLE)
            {
                BLEIOT_sendUpdateContrast(wrReqParam->handleValPair.value.val[0]);
                updateGattDB(wrReqParam->handleValPair.value.val,1,notifyFlags.contrast,CYBLE_CY8CKIT021_CONTRAST_CHAR_HANDLE,CYBLE_GATT_DB_PEER_INITIATED);
            }
            #ifndef BootLoadable__DISABLED
      
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_BOOTLOAD_CHAR_HANDLE)
            {
                if(wrReqParam->handleValPair.value.val[0])
                    Bootloadble_start();
              
            }
            #endif
            
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_TRIM_CHAR_HANDLE)
            {
                BLEIOT_sendUpdateTrim(*(int16 *)wrReqParam->handleValPair.value.val);
                updateGattDB(wrReqParam->handleValPair.value.val,2,notifyFlags.trim,CYBLE_CY8CKIT021_TRIM_CHAR_HANDLE,CYBLE_GATT_DB_PEER_INITIATED);
            }
    
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_DISPLAY_CHAR_HANDLE)
            {
                BLEIOT_sendUpdateDisplay(*(uint16 *)wrReqParam->handleValPair.value.val);
                updateGattDB(wrReqParam->handleValPair.value.val,2,notifyFlags.display,CYBLE_CY8CKIT021_DISPLAY_CHAR_HANDLE,CYBLE_GATT_DB_PEER_INITIATED);
            }
    
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_TONE_CHAR_HANDLE)
            {
                BLEIOT_sendUpdateTone(*(uint16 *)wrReqParam->handleValPair.value.val);
                updateGattDB(wrReqParam->handleValPair.value.val,2,notifyFlags.tone,CYBLE_CY8CKIT021_TONE_CHAR_HANDLE,CYBLE_GATT_DB_PEER_INITIATED);
            }
    
    
  	    break;  
        
        default:
            break;
    }
} 

#define LED_ON 0
#define LED_OFF 1
int main()
{

    CyGlobalIntEnable;
    BLEIOT_Start();
    processBlueLed();
    
    for(;;)
    {
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_BLESTATE)
        {
            if(BLEIOT_readRemoteBleState() == BLEOFF)
            {
                CyBle_Stop();
                BLEIOT_sendUpdateBleState(BLEOFF);
                processBlueLed();
            }
            if(BLEIOT_readRemoteBleState() == BLEON && BLEIOT_readLocalBleState() == BLEOFF)
            {
                CyBle_Start(BleCallBack);
                BLEIOT_sendUpdateBleState(BLESTART);
            }
        }
        
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_LED0)
        {
            BLEIOT_sendUpdateLed0(BLEIOT_readRemoteLed0());
            uint8 val = BLEIOT_readLocalLed0();
            updateGattDB(&val,sizeof(val),notifyFlags.led0,CYBLE_CY8CKIT021_LED0_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
        }
        
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_LED1)
        {
            BLEIOT_sendUpdateLed0(BLEIOT_readRemoteLed1());
            uint8 val = BLEIOT_readLocalLed1();
            updateGattDB(&val,sizeof(val),notifyFlags.led1,CYBLE_CY8CKIT021_LED1_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
        }

        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_BUTTON0)
        {
            BLEIOT_sendUpdateButton0(BLEIOT_readRemoteButton0());
            uint8 val = BLEIOT_readLocalButton0();
            updateGattDB(&val,sizeof(val),notifyFlags.button0,CYBLE_CY8CKIT021_BUTTON0_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
        }

        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_BUTTON1)
        {
            BLEIOT_sendUpdateButton1(BLEIOT_readRemoteButton1());
            uint8 val = BLEIOT_readLocalButton1();
            updateGattDB(&val,sizeof(val),notifyFlags.button1,CYBLE_CY8CKIT021_BUTTON1_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
        }
        
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_CONTRAST)
        {
            BLEIOT_sendUpdateContrast(BLEIOT_readRemoteContrast());
            uint8 val = BLEIOT_readLocalContrast();
            updateGattDB(&val,sizeof(val),notifyFlags.contrast,CYBLE_CY8CKIT021_CONTRAST_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
        }
        
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_TRIM)
        {
            BLEIOT_sendUpdateTrim(BLEIOT_readRemoteTrim());
            int16 val = BLEIOT_readLocalTrim();
            updateGattDB((uint8 *)&val,sizeof(val),notifyFlags.trim,CYBLE_CY8CKIT021_TRIM_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
        }

        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_DISPLAY)
        {
            BLEIOT_sendUpdateDisplay(BLEIOT_readRemoteDisplay());
            uint16 val = BLEIOT_readLocalDisplay();
            updateGattDB((uint8 *)&val,sizeof(val),notifyFlags.display,CYBLE_CY8CKIT021_DISPLAY_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
        }

        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_TONE)
        {
            BLEIOT_sendUpdateTone(BLEIOT_readRemoteTone());
            uint16 val = BLEIOT_readLocalTone();
            updateGattDB((uint8 *)&val,sizeof(val),notifyFlags.tone,CYBLE_CY8CKIT021_TONE_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
        }
   
        #ifndef BootLoadable__DISABLED
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_BOOTLOAD)
        {
            // enter the bootloader
            Bootloable_load();
        }
        #endif
        
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_BLUE)
        {
            BLEIOT_sendUpdateBlue(BLEIOT_readRemoteBlue());
            processBlueLed();
            uint8 val = BLEIOT_readLocalBlue();
            updateGattDB(&val,sizeof(val),notifyFlags.blue,CYBLE_CY8CKIT021_BLUE_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
        }
       
        if(BLEIOT_readLocalBleState() != BLEOFF)
        {
            CyBle_ProcessEvents();
            CyBle_EnterLPM(CYBLE_BLESS_DEEPSLEEP);
        }
    }
}
