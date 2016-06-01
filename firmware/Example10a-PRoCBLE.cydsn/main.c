#include <project.h>
#include "BLEIOT_BLEIOT.h"

// This structure contains a flag for the state of the notify request of the CCCD
// when the CCCD is written I store the written byte into this structure so I will know
// to send out notify's when the values change
typedef struct NotifyFlags {
    uint8 led0;
    uint8 button0;    
} NotifyFlags;

NotifyFlags notifyFlags;

// This union is used to unwind the BLE written byte data into the right type
typedef union Types {
    uint8 bytes[2];
    int16 integer16;
    uint16 uinteger16;
} __attribute__((packed)) Types;

// updateGattDB() -  
//
// Arguments: 
//  uint8* val  - a pointer to the bytes that need to be writted into the GATTDB
//  int size - the number of bytes that need to be written into the GATTDB
//  uint8 notify - if the NOTIFY is on then send a notification
//  CYBLE_GATT_DB_ATTR_HANDLE_T handle - a handle to the entry in the gatt table
//  uint8 flags - a request 
//   
// This is a helper function that will update the GATT database with a value.  It update the field of
// the "CYBLE_GATT_DB_ATTR_HANDLE_T"

void updateGattDB(uint8 *val,int size,uint8 notify, CYBLE_GATT_DB_ATTR_HANDLE_T handle,uint8 flags)
{
    
    // this little block of code doesnt make me happy... 
   
    switch(CyBle_GetState())
    {
        case CYBLE_STATE_ADVERTISING:
            return;
        case CYBLE_STATE_DISCONNECTED:
            return;
        case CYBLE_STATE_STOPPED:
            return;
        case CYBLE_STATE_CONNECTED:
            break;
        case CYBLE_STATE_INITIALIZING:
            return;
    }
        
    //update the GATT Database
    CYBLE_GATTS_HANDLE_VALUE_NTF_T 	tempHandle;
    tempHandle.attrHandle = handle;
  	tempHandle.value.val = val;
    tempHandle.value.len = size;
    CYBLE_GATT_ERR_CODE_T ret = CyBle_GattsWriteAttributeValue(&tempHandle,0,&cyBle_connHandle,flags);
    if(ret != CYBLE_GATT_ERR_NONE) // this is really not a good place to be.
    {
        return;
        
        CYASSERT(0);
        while(1);
    }
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
    switch(event)
    {
        /* if there is a disconnect or the stack just turned on from a reset then start the advertising and turn on the LED blinking */
        case CYBLE_EVT_STACK_ON:
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            PWM_Start();
            memset(&notifyFlags,0,sizeof(notifyFlags));
        break;       
            
        case CYBLE_EVT_GAP_DEVICE_CONNECTED:           
            PWM_Stop();
            updateGattDB(&BLEIOT_local.led0,sizeof(BLEIOT_local.led0),notifyFlags.led0,CYBLE_CY8CKIT021_LED0_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
            updateGattDB(&BLEIOT_local.button0,sizeof(BLEIOT_local.button0),notifyFlags.button0,CYBLE_CY8CKIT021_BUTTON0_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
        break;
            
        case CYBLE_EVT_GATTS_WRITE_REQ:
            wrReqParam = (CYBLE_GATTS_WRITE_REQ_PARAM_T *) eventParam;
           // Bootload
            #ifndef BootLoadable__DISABLED
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_BOOTLOAD_CHAR_HANDLE)
            {
                Bootloadable_Load();
            
            }
            #endif
             
            // LED0
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_LED0_CHAR_HANDLE)
            {
                BLEIOT_updateLed0(wrReqParam->handleValPair.value.val[0]);
                updateGattDB(wrReqParam->handleValPair.value.val,1,notifyFlags.led0,CYBLE_CY8CKIT021_LED0_CHAR_HANDLE,CYBLE_GATT_DB_PEER_INITIATED);
            }
            
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_LED0_CCCD_DESC_HANDLE)
            {
                notifyFlags.led0 = wrReqParam->handleValPair.value.val[0];
                CyBle_GattsWriteRsp(cyBle_connHandle);
            }

            // BUTTON 0
            if(wrReqParam->handleValPair.attrHandle == CYBLE_CY8CKIT021_BUTTON0_CCCD_DESC_HANDLE)
            {
                notifyFlags.button0 = wrReqParam->handleValPair.value.val[0];
                CyBle_GattsWriteRsp(cyBle_connHandle);
            }
        break;  
        
        default:
        break;
    }
} 

int main()
{
    CyGlobalIntEnable;
    BLEIOT_Start();
    
    EZI2C_Start();
    EZI2C_EzI2CSetBuffer1(sizeof(BLEIOT_local),1,(uint8 *)&BLEIOT_local);

    CyBle_Start(BleCallBack);
    
    for(;;)
    {

        #ifndef BootLoadable__DISABLED
        // if they write into the BLEIOT_local.bootload (from EzI2C)
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_BOOTLOAD || BLEIOT_local.bootload)
        {
            // enter the bootloader
            Bootloadable_Load();
        }
        
        #endif
               
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_LED0)
        {
            BLEIOT_updateLed0(BLEIOT_remote.led0);
            updateGattDB(&BLEIOT_local.led0,sizeof(BLEIOT_local.led0),notifyFlags.led0,CYBLE_CY8CKIT021_LED0_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
        }
      
        if(BLEIOT_getDirtyFlags() & BLEIOT_FLAG_BUTTON0)
        {
            BLEIOT_updateButton0(BLEIOT_remote.button0);
            updateGattDB(&BLEIOT_local.button0,sizeof(BLEIOT_local.button0),notifyFlags.button0,CYBLE_CY8CKIT021_BUTTON0_CHAR_HANDLE,CYBLE_GATT_DB_LOCALLY_INITIATED);
        }

        CyBle_ProcessEvents();
        CyBle_EnterLPM(CYBLE_BLESS_DEEPSLEEP);
    }
}
