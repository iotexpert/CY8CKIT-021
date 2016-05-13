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

void updateBlueGattDB(uint8 flags)
{
    uint8 val = BLEIOT_readLocalBlue();
    
    //update the GATT Database
    CYBLE_GATTS_HANDLE_VALUE_NTF_T 	tempHandle;
   
    if(CyBle_GetState() != CYBLE_STATE_CONNECTED)
        return;
    
    tempHandle.attrHandle = CYBLE_CY8CKIT021_BLUE_CHAR_HANDLE;
  	tempHandle.value.val = (uint8 *) &val;
    tempHandle.value.len = 1;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,flags);
    // if peer initiated then write response.
    if(flags == CYBLE_GATT_DB_PEER_INITIATED)
        CyBle_GattsWriteRsp(cyBle_connHandle);
    else if(notifyFlags.blue) // If notify & local initiated 
    {
        CyBle_GattsNotification(cyBle_connHandle,&tempHandle);
    }    
}

void updateLed0GattDB(uint8 flags)
{
    uint8 val = BLEIOT_readLocalLed0();
    
    //update the GATT Database
    CYBLE_GATTS_HANDLE_VALUE_NTF_T 	tempHandle;
   
    if(CyBle_GetState() != CYBLE_STATE_CONNECTED)
        return;
    
    tempHandle.attrHandle = CYBLE_CY8CKIT021_LED0_CHAR_HANDLE;
  	tempHandle.value.val = (uint8 *) &val;
    tempHandle.value.len = 1;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,flags);
    // if peer initiated then write response.
    if(flags == CYBLE_GATT_DB_PEER_INITIATED)
        CyBle_GattsWriteRsp(cyBle_connHandle);
    else if(notifyFlags.led0) // If notify & local initiated 
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
            updateBlueGattDB(CYBLE_GATT_DB_LOCALLY_INITIATED);
            BLEIOT_sendUpdateBleState(BLECONNECTED);
            processBlueLed();
		break;

        /* handle a write request */
        case CYBLE_EVT_GATTS_WRITE_REQ:
            wrReqParam = (CYBLE_GATTS_WRITE_REQ_PARAM_T *) eventParam;
			      
            /* request write the LED value */
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_BLUE_CHAR_HANDLE)
            {
                BLEIOT_sendUpdateBlue(wrReqParam->handleValPair.value.val[0]);
                processBlueLed();
                updateBlueGattDB(CYBLE_GATT_DB_PEER_INITIATED);    
            }

            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_LED0_CHAR_HANDLE)
            {
                BLEIOT_sendUpdateLed0(wrReqParam->handleValPair.value.val[0]);
                updateLed0GattDB(CYBLE_GATT_DB_PEER_INITIATED);
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
            updateLed0GattDB(CYBLE_GATT_DB_LOCALLY_INITIATED);
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
            updateBlueGattDB(CYBLE_GATT_DB_LOCALLY_INITIATED);
        }
       
        if(BLEIOT_readLocalBleState() != BLEOFF)
        {
            CyBle_ProcessEvents();
            CyBle_EnterLPM(CYBLE_BLESS_DEEPSLEEP);
        }
     
    }
     
}

/* [] END OF FILE */
