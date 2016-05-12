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

/***************************************************************
 * Function to update the LED state in the GATT database
 **************************************************************/
void updateBlueLed(BlueStates val)
{
    switch(val)
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
            BLEIOT_sendUpdateBlue(BLEIOT_readRemoteBlue());

    
    //update the GATT Database
    CYBLE_GATTS_HANDLE_VALUE_NTF_T 	tempHandle;
   
   
    if(CyBle_GetState() != CYBLE_STATE_CONNECTED)
        return;
    tempHandle.attrHandle = CYBLE_CY8CKIT021_BLUE_CHAR_HANDLE;
  	tempHandle.value.val = (uint8 *) &val;
    tempHandle.value.len = 1;
    CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,CYBLE_GATT_DB_LOCALLY_INITIATED);  
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
            updateBlueLed(BLEIOT_readLocalBlue());
            BLEIOT_sendUpdateBleState(BLEADVERTISING);
            
        break;
            
        case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
            updateBlueLed(BLEIOT_readLocalBlue());
        break;
        
            
        case CYBLE_EVT_GAP_DEVICE_CONNECTED:
            updateBlueLed(BLEIOT_readLocalBlue());
            BLEIOT_sendUpdateBleState(BLECONNECTED);
 
		break;

        /* handle a write request */
        case CYBLE_EVT_GATTS_WRITE_REQ:
            wrReqParam = (CYBLE_GATTS_WRITE_REQ_PARAM_T *) eventParam;
			      
            /* request write the LED value */
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_BLUE_CHAR_HANDLE)
            {
                updateBlueLed(wrReqParam->handleValPair.value.val[0]);
                CyBle_GattsWriteRsp(cyBle_connHandle);
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
    
    updateBlueLed(BLEIOT_readLocalBlue());
    
    //CyBle_Start(BleCallBack);

    for(;;)
    {
        
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_BLESTATE)
        {
            if(BLEIOT_readRemoteBleState() == BLEOFF)
            {
                CyBle_Stop();
                BLEIOT_sendUpdateBleState(BLEOFF);
                updateBlueLed(BLEIOT_readLocalBlue());
            }
            if(BLEIOT_readRemoteBleState() == BLEON && BLEIOT_readLocalBleState() == BLEOFF)
            {
                CyBle_Start(BleCallBack);
                BLEIOT_sendUpdateBleState(BLESTART);
            }
            
        }
        
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_BOOTLOAD)
        {
            // enter the bootloader
        }
        
        
        if(BLEIOT_readLocalBleState() != BLEOFF)
        {
            CyBle_ProcessEvents();
            CyBle_EnterLPM(CYBLE_BLESS_DEEPSLEEP);
        }
        
       
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_BLUE)
        {
            updateBlueLed(BLEIOT_readRemoteBlue());
        }
       
    }
     
}

/* [] END OF FILE */
