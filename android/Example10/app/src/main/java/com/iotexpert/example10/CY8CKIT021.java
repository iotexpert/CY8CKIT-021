package com.iotexpert.example10;

import android.app.Service;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothGatt;
import android.bluetooth.BluetoothGattCallback;
import android.bluetooth.BluetoothGattCharacteristic;
import android.bluetooth.BluetoothGattDescriptor;
import android.bluetooth.BluetoothGattService;
import android.bluetooth.BluetoothManager;
import android.bluetooth.BluetoothProfile;
import android.bluetooth.le.BluetoothLeScanner;
import android.bluetooth.le.ScanCallback;
import android.bluetooth.le.ScanFilter;
import android.bluetooth.le.ScanResult;
import android.bluetooth.le.ScanSettings;
import android.content.Context;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;
import android.os.ParcelUuid;
import android.util.Log;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.UUID;

public class CY8CKIT021 extends Service {
    public CY8CKIT021() {
    }

    private final static String TAG = CY8CKIT021.class.getSimpleName();

    // Bluetooth objects that we need to interact with
    private static BluetoothManager mBluetoothManager;
    private static BluetoothAdapter mBluetoothAdapter;
    private static BluetoothLeScanner mLEScanner;
    private static BluetoothDevice mLeDevice;
    private static BluetoothGatt mBluetoothGatt;

    // Bluetooth characteristics that we need to read/write
    private static BluetoothGattCharacteristic mLed0Characterisitc;
    private static BluetoothGattCharacteristic mButton0Characteristic;
    private static BluetoothGattCharacteristic mBootloadCharacteristic;
    private static BluetoothGattDescriptor mButton0Cccd;

    // UUIDs for the service and characteristics that the custom CapSenseLED service uses
    private final static String baseUUID =                   "00000000-0000-1000-8000-00805f9b340";
    private final static String CY8CKIT021ServiceUUID =      baseUUID + "0";
    private final static String bootloadCharacteristicUUID =      baseUUID + "1";
    private final static String led0CharacteristicUUID =       baseUUID + "2";
    private final static String button0CharacteristicUUID =  baseUUID + "4";
    private final static String button0CccdUUID =            "00002902-0000-1000-8000-00805f9b34fb";

    // Variables to keep track of the LED switch state and CapSense Value
    private boolean mLed0SwitchState = false; // assume false
    private boolean mButton0SwitchState = false; // assume false
    private boolean mConnected = false; // start false

    public boolean isLed0SwitchState() {
        return mLed0SwitchState;
    }

    public void setLed0SwitchState(boolean mLed0SwitchState) {
        mLed0SwitchState = mLed0SwitchState;
    }

    public boolean isButton0SwitchState() {
        return mButton0SwitchState;
    }

    public void setButton0SwitchState(boolean mButton0SwitchState) {
        mButton0SwitchState = mButton0SwitchState;
    }

    public boolean isConnected() {
        return mConnected;
    }


    // Actions used during broadcasts to the main activity
    public final static String ACTION_CONNECTED =
            "com.cypress.academy.cy8ckit021example10.ACTION_CONNECTED";
    public final static String ACTION_DISCONNECTED =
            "com.cypress.academy.cy8ckit021example10.ACTION_DISCONNECTED";
    public final static String ACTION_UPDATED_LED0 =
            "com.cypress.academy.cy8ckit021example10.ACTION_UPDATED_LED0";
    public final static String ACTION_UPDATED_BUTTON0 =
            "com.cypress.academy.cy8ckit021example10.ACTION_UPDATED_BUTTON0";


    public class LocalBinder extends Binder {
        CY8CKIT021 getService() {
            return CY8CKIT021.this;
        }
    }

    @Override
    public IBinder onBind(Intent intent) {
        return mBinder;
    }

    @Override
    public boolean onUnbind(Intent intent) {
        // The BLE close method is called when we unbind the service to free up the resources.
        close();
        return super.onUnbind(intent);
    }

    private final IBinder mBinder = new LocalBinder();

    /**
     * Initializes a reference to the local Bluetooth adapter.
     *
     * @return Return true if the initialization is successful.
     */
    public boolean initialize() {

        Log.d(TAG,"In initialize function");
        // For API level 18 and above, get a reference to BluetoothAdapter through
        // BluetoothManager.
        if (mBluetoothManager == null) {
            mBluetoothManager = (BluetoothManager) getSystemService(Context.BLUETOOTH_SERVICE);
            if (mBluetoothManager == null) {
                Log.e(TAG, "Unable to initialize BluetoothManager.");
                return false;
            }
        }

        mBluetoothAdapter = mBluetoothManager.getAdapter();
        if (mBluetoothAdapter == null) {
            Log.e(TAG, "Unable to obtain a BluetoothAdapter.");
            return false;
        }

        Log.d(TAG,"got bluetooth adaptor");
        broadcastUpdate("Got BlueTooth Adaptor");
        //scan();

        return true;
    }


    /**
     * Scans for BLE devices that support the service we are looking for
     */
    public void scan() {

        Log.d(TAG,"Started bluetooth scan " + CY8CKIT021ServiceUUID);
        /* Scan for devices and look for the one with the service that we want */
        UUID CY8CKIT021Service =       UUID.fromString(CY8CKIT021ServiceUUID);
        UUID[] CY8CKIT021ServiceArray = {CY8CKIT021Service};

            ScanSettings settings;
            List<ScanFilter> filters;
            mLEScanner = mBluetoothAdapter.getBluetoothLeScanner();
            settings = new ScanSettings.Builder()
                    .setScanMode(ScanSettings.SCAN_MODE_LOW_LATENCY)
                    .build();
            filters = new ArrayList<>();
            // We will scan just for the CAR's UUID
            ParcelUuid PUuid = new ParcelUuid(CY8CKIT021Service);
            ScanFilter filter = new ScanFilter.Builder().setServiceUuid(PUuid).build();
            filters.add(filter);
            mLEScanner.startScan(filters, settings, mScanCallback);
    }

    /**
     * Connects to the GATT server hosted on the Bluetooth LE device.
     *
     * @return Return true if the connection is initiated successfully. The connection result
     * is reported asynchronously through the
     * {@code BluetoothGattCallback#onConnectionStateChange(android.bluetooth.BluetoothGatt, int, int)}
     * callback.
     */
    public boolean connect() {
        if (mBluetoothAdapter == null) {
            Log.w(TAG, "BluetoothAdapter not initialized");
            return false;
        }

        // Previously connected device.  Try to reconnect.
        if (mBluetoothGatt != null) {
            Log.d(TAG, "Trying to use an existing mBluetoothGatt for connection.");
            return mBluetoothGatt.connect();
        }

        // We want to directly connect to the device, so we are setting the autoConnect
        // parameter to false.
        mBluetoothGatt = mLeDevice.connectGatt(this, false, mGattCallback);
        Log.d(TAG, "Trying to create a new connection.");
        return true;
    }

    /**
     * Runs service discovery on the connected device.
     */
    public void discoverServices() {
        if (mBluetoothAdapter == null || mBluetoothGatt == null) {
            Log.w(TAG, "BluetoothAdapter not initialized");
            return;
        }
        mBluetoothGatt.discoverServices();
    }

    /**
     * Disconnects an existing connection or cancel a pending connection. The disconnection result
     * is reported asynchronously through the
     * {@code BluetoothGattCallback#onConnectionStateChange(android.bluetooth.BluetoothGatt, int, int)}
     * callback.
     */
    public void disconnect() {
        if (mBluetoothAdapter == null || mBluetoothGatt == null) {
            Log.w(TAG, "BluetoothAdapter not initialized");
            return;
        }
        mBluetoothGatt.disconnect();
    }

    /**
     * After using a given BLE device, the app must call this method to ensure resources are
     * released properly.
     */
    public void close() {
        if (mBluetoothGatt == null) {
            return;
        }
        mBluetoothGatt.close();
        mBluetoothGatt = null;
    }

    /**
     * This method is used to read the state of the LED from the device
     */
    public void readLed0Characteristic() {
        if (mBluetoothAdapter == null || mBluetoothGatt == null) {
            Log.w(TAG, "BluetoothAdapter not initialized");
            return;
        }
        mBluetoothGatt.readCharacteristic(mLed0Characterisitc);
    }

    /**
     * This method is used to read the state of the LED from the device
     */
    public void readButton0Characteristic() {
        if (mBluetoothAdapter == null || mBluetoothGatt == null) {
            Log.w(TAG, "BluetoothAdapter not initialized");
            return;
        }
        mBluetoothGatt.readCharacteristic(mButton0Characteristic);
    }

    /**
     * This method is used to turn the LED on or off
     *
     * @param value Turns the LED on (1) or off (0)
     */
    public void writeLed0Characteristic(boolean value) {
        byte[] byteVal = new byte[1];
        if (value) {
            byteVal[0] = (byte) (1);
        } else {
            byteVal[0] = (byte) (0);
        }
        Log.i(TAG, "LED " + value);
        mLed0SwitchState = value;
        mLed0Characterisitc.setValue(byteVal);
        mBluetoothGatt.writeCharacteristic(mLed0Characterisitc);
    }

    /**
     * This method enables or disables notifications for the CapSense slider
     *
     * @param value Turns notifications on (1) or off (0)
     */
    public void writeButton0Notification(boolean value) {
        // Set notifications locally in the CCCD
        Log.d(TAG,"Set Local = " + mButton0Characteristic.getUuid().toString());
        mBluetoothGatt.setCharacteristicNotification(mButton0Characteristic, value);
        byte[] byteVal = new byte[1];
        if (value) {
            byteVal[0] = 1;
        } else {
            byteVal[0] = 0;
        }
        // Write Notification value to the device
        Log.i(TAG, "Button0 Notification " + value);
        mButton0Cccd.setValue(byteVal);
        mBluetoothGatt.writeDescriptor(mButton0Cccd);
    }

    public void setNotify()
    {
        Log.d(TAG,"Turned on notification");
        // 0x2902 org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml
        UUID uuid = UUID.fromString("00002902-0000-1000-8000-00805f9b34fb");
        BluetoothGattDescriptor descriptor = mButton0Characteristic.getDescriptor(uuid);
        descriptor.setValue(BluetoothGattDescriptor.ENABLE_NOTIFICATION_VALUE);
        mBluetoothGatt.writeDescriptor(descriptor);
    }

    /**
     * Implements the callback for when scanning for devices has found a device with
     * the service we are looking for.
     *
     * This is the callback for BLE scanning for LOLLIPOP and later
     */
    private final ScanCallback mScanCallback = new ScanCallback() {
        @Override
        public void onScanResult(int callbackType, ScanResult result) {
            mLeDevice = result.getDevice();
            mLEScanner.stopScan(mScanCallback); // Stop scanning after the first device is found
            //broadcastUpdate(ACTION_BLESCAN_CALLBACK); // Tell the main activity that a device has been found
            connect();
            Log.d(TAG,"Found service");

        }
    };


    /**
     * Implements the callback for when scanning for devices has found a device with
     * the service we are looking for.
     *
     * This is the callback for BLE scanning on versions prior to Lollipop
     */
    /*
    private BluetoothAdapter.LeScanCallback mLeScanCallback =
            new BluetoothAdapter.LeScanCallback() {
                @Override
                public void onLeScan(final BluetoothDevice device, int rssi, byte[] scanRecord) {
                    mLeDevice = device;
                    //noinspection deprecation
                    mBluetoothAdapter.stopLeScan(mLeScanCallback); // Stop scanning after the first device is found
                    Log.d(TAG,"found device");
                    discoverServices();
                    //broadcastUpdate(ACTION_BLESCAN_CALLBACK); // Tell the main activity that a device has been found
                }
            };

*/

    //http://stackoverflow.com/questions/17910322/android-ble-api-gatt-notification-not-received
    // http://www.brendanwhelan.net/2015/bluetooth-command-queuing-for-android

    private Queue<BluetoothGattDescriptor> descriptorWriteQueue = new LinkedList<BluetoothGattDescriptor>();
    private Queue<BluetoothGattCharacteristic> characteristicReadQueue = new LinkedList<BluetoothGattCharacteristic>();

    public void writeGattDescriptor(BluetoothGattDescriptor d){
        //put the descriptor into the write queue
        descriptorWriteQueue.add(d);
        //if there is only 1 item in the queue, then write it.  If more than 1, we handle asynchronously in the callback above
        if(descriptorWriteQueue.size() == 1){
            mBluetoothGatt.writeDescriptor(d);
        }
    }

    public void onDescriptorWrite(BluetoothGatt gatt, BluetoothGattDescriptor descriptor, int status) {
        if (status == BluetoothGatt.GATT_SUCCESS) {
            Log.d(TAG, "Callback: Wrote GATT Descriptor successfully.");
        }
        else{
            Log.d(TAG, "Callback: Error writing GATT Descriptor: "+ status);
        }
        descriptorWriteQueue.remove();  //pop the item that we just finishing writing
        //if there is more to write, do it!
        if(descriptorWriteQueue.size() > 0)
            mBluetoothGatt.writeDescriptor(descriptorWriteQueue.element());
        else if(characteristicReadQueue.size() > 0)
            mBluetoothGatt.readCharacteristic(characteristicReadQueue.element());
    }

    public void readCharacteristic(BluetoothGattCharacteristic c) {
        if (mBluetoothAdapter == null || mBluetoothGatt == null) {
            Log.w(TAG, "BluetoothAdapter not initialized");
            return;
        }
        //put the characteristic into the read queue
        characteristicReadQueue.add(c);
        //if there is only 1 item in the queue, then read it.  If more than 1, we handle asynchronously in the callback above
        //GIVE PRECEDENCE to descriptor writes.  They must all finish first.
        if((characteristicReadQueue.size() == 1) && (descriptorWriteQueue.size() == 0))
            mBluetoothGatt.readCharacteristic(c);
    }

    public void onCharacteristicRead(BluetoothGatt gatt,
                                     BluetoothGattCharacteristic characteristic,
                                     int status) {
        characteristicReadQueue.remove();
        if (status == BluetoothGatt.GATT_SUCCESS) {
            broadcastUpdate(ACTION_DATA_AVAILABLE, characteristic);
        }
        else{
            Log.d(TAG, "onCharacteristicRead error: " + status);
        }

        if(characteristicReadQueue.size() > 0)
            mBluetoothGatt.readCharacteristic(characteristicReadQueue.element());
    }

    /**
     * Implements callback methods for GATT events that the app cares about.  For example,
     * connection change and services discovered.
     */
    private final BluetoothGattCallback mGattCallback = new BluetoothGattCallback() {
        @Override
        public void onConnectionStateChange(BluetoothGatt gatt, int status, int newState) {
            if (newState == BluetoothProfile.STATE_CONNECTED) {
                //broadcastUpdate(ACTION_CONNECTED);
                discoverServices();
                Log.i(TAG, "Connected to GATT server.");
            } else if (newState == BluetoothProfile.STATE_DISCONNECTED) {
                Log.i(TAG, "Disconnected from GATT server.");
                disconnect(); // ARH not sure about this
                broadcastUpdate(ACTION_DISCONNECTED);
            }
        }

        /**
         * This is called when a service discovery has completed.
         *
         * It gets the characteristics we are interested in and then
         * broadcasts an update to the main activity.
         *
         * @param gatt The GATT database object
         * @param status Status of whether the write was successful.
         */
        @Override
        public void onServicesDiscovered(BluetoothGatt gatt, int status) {
            Log.d(TAG,"On Services Discovered");
            // Get just the service that we are looking for
            BluetoothGattService mService = gatt.getService(UUID.fromString(CY8CKIT021ServiceUUID));
            /* Get characteristics from our desired service */
            mLed0Characterisitc = mService.getCharacteristic(UUID.fromString(led0CharacteristicUUID));
            mButton0Characteristic = mService.getCharacteristic(UUID.fromString(button0CharacteristicUUID));
            /* Get the CapSense CCCD */
            mButton0Cccd = mButton0Characteristic.getDescriptor(UUID.fromString(button0CccdUUID));

            // Read the current state of the LED from the device
            //readLed0Characteristic();
            //readButton0Characteristic();
            //writeButton0Notification(true);
            setNotify();
            // Broadcast that service/characteristic/descriptor discovery is done
            broadcastUpdate(ACTION_CONNECTED);
        }

        /**
         * This is called when a read completes
         *
         * @param gatt the GATT database object
         * @param characteristic the GATT characteristic that was read
         * @param status the status of the transaction
         */
        @Override
        public void onCharacteristicRead(BluetoothGatt gatt,
                                         BluetoothGattCharacteristic characteristic,
                                         int status) {

            Log.d(TAG,"Got read from device : "+characteristic.getUuid().toString());

            if (status == BluetoothGatt.GATT_SUCCESS) {
                // Verify that the read was the LED state
                String uuid = characteristic.getUuid().toString();
                // In this case, the only read the app does is the LED state.
                // If the application had additional characteristics to read we could
                // use a switch statement here to operate on each one separately.
                if(uuid.equals(led0CharacteristicUUID)) {
                    final byte[] data = characteristic.getValue();
                    // Set the LED switch state variable based on the characteristic value ttat was read
                    mLed0SwitchState = ((data[0] & 0xff) != 0x00);
                    broadcastUpdate(ACTION_UPDATED_LED0);
                }

                if(uuid.equals(button0CharacteristicUUID)) {
                    final byte[] data = characteristic.getValue();
                    // Set the LED switch state variable based on the characteristic value ttat was read
                    mButton0SwitchState = ((data[0] & 0xff) != 0x00);
                    broadcastUpdate(ACTION_UPDATED_BUTTON0);
                }
            }
        }

        /**
         * This is called when a characteristic with notify set changes.
         * It broadcasts an update to the main activity with the changed data.
         *
         * @param gatt The GATT database object
         * @param characteristic The characteristic that was changed
         */
        @Override
        public void onCharacteristicChanged(BluetoothGatt gatt,
                                            BluetoothGattCharacteristic characteristic) {

            String uuid = characteristic.getUuid().toString();

            Log.d(TAG,"Characteristic changed = "+uuid);

            if(uuid.equals(button0CharacteristicUUID)) {
                Integer buttonState = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_UINT8,0);
                if(buttonState == 0) {
                    mButton0SwitchState = false;
                }
                else {
                    mButton0SwitchState = true;
                }

            }

            // Notify the main activity that new data is available
            broadcastUpdate(ACTION_UPDATED_BUTTON0);
        }
    }; // End of GATT event callback methods

    /**
     * Sends a broadcast to the listener in the main activity.
     *
     * @param action The type of action that occurred.
     */
    private void broadcastUpdate(final String action) {
        final Intent intent = new Intent(action);
        sendBroadcast(intent);
    }

}
