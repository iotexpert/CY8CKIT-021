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

    private BLEQueue queue = new BLEQueue();

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
    //private final static String CCCDUUID =            "00002902-0000-1000-8000-00805f9b34fb";
    private final static UUID CCCDUUID = UUID.fromString("00002902-0000-1000-8000-00805f9b34fb");

    // Variables to keep track of the LED switch state and CapSense Value
    private boolean mLed0SwitchState = false; // assume false
    private boolean mButton0SwitchState = false; // assume false
    private boolean mConnected = false; // start false

    public boolean isLed0SwitchState() {
        return mLed0SwitchState;
    }

    public void setLed0SwitchState(boolean mLed0SwitchState) {
        this.mLed0SwitchState = mLed0SwitchState;
    }

    public boolean isButton0SwitchState() {
        return mButton0SwitchState;
    }

    public void setButton0SwitchState(boolean mButton0SwitchState) {
        this.mButton0SwitchState = mButton0SwitchState;
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

        scan();

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
        mBluetoothGatt.discoverServices();
    }

    public void disconnect() {
        mBluetoothGatt.disconnect();
    }

    public void close() {
        if (mBluetoothGatt == null) {
            return;
        }
        mBluetoothGatt.close();
        mBluetoothGatt = null;
    }

    public void readLed0Characteristic() {
        queue.readCharacteristic(mLed0Characterisitc);
    }

    public void readButton0Characteristic() {
        queue.readCharacteristic(mButton0Characteristic);
    }

    public void writeLed0Characteristic(boolean value)
    {
        queue.writeBoolean(mLed0Characterisitc,new Boolean(value));
    }

    public void writeBootloadCharacteristic()
    {
        queue.writeBoolean(mBootloadCharacteristic,new Boolean(true)); // it doesnt matter what you write it always starts
    }
    /*
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
    */

    /**
     * This method enables or disables notifications for the CapSense slider
     *
     * @param value Turns notifications on (1) or off (0)
     */
    public void writeButton0Notification(boolean value) {

        if(value)
            queue.enableNotification(mButton0Characteristic);
        else
            queue.disableNotification(mButton0Characteristic);
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
            connect();
        }
    };

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
            mLed0Characterisitc = mService.getCharacteristic(UUID.fromString(led0CharacteristicUUID));
            mButton0Characteristic = mService.getCharacteristic(UUID.fromString(button0CharacteristicUUID));
            mBootloadCharacteristic = mService.getCharacteristic(UUID.fromString(bootloadCharacteristicUUID));

            // Read the current state of the LED from the device
            readLed0Characteristic();
            readButton0Characteristic();

            writeButton0Notification(true); // turn on notifications for the capsense button
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

            queue.clearEvent();
            String uuid = characteristic.getUuid().toString();

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

        @Override
        public void onCharacteristicWrite(BluetoothGatt gatt, BluetoothGattCharacteristic characteristic, int status)
        {
            queue.clearEvent();
        }

        @Override
        public  void onDescriptorWrite(BluetoothGatt gatt, BluetoothGattDescriptor descriptor, int status)
        {
            queue.clearEvent();
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

            if(uuid.equals(button0CharacteristicUUID)) {
                Integer buttonState = characteristic.getIntValue(BluetoothGattCharacteristic.FORMAT_UINT8,0);
                if(buttonState == 0) {
                    mButton0SwitchState = false;
                }
                else {
                    mButton0SwitchState = true;
                }
                broadcastUpdate(ACTION_UPDATED_BUTTON0);
            }
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

    static class BLEQueue {
        private Queue<BLEActivity> actitvityQueue = new LinkedList<>();
        private boolean idle = true;


        private enum BLEActivities {
            WRITE,
            READ,
            ENABLE_NOTIFICATION,
            DISABLE_NOTIFICATION
        }

        private class BLEActivity {
            private boolean launched = false;
            private BLEActivities BLEActivity;
            private BluetoothGattCharacteristic characteristic;
            private BluetoothGattDescriptor descriptor;
            private BLEWriteType writeType;
            private java.lang.Object value;

        }

        private enum BLEWriteType {
            UINT8,
            BOOLEAN
        }
        private void addBleActivity(BLEActivity activity)
        {
            actitvityQueue.add(activity);
            launchNextEvent();
        }

        public void readCharacteristic(BluetoothGattCharacteristic characteristic)
        {
            BLEActivity activity = new BLEActivity();
            activity.characteristic = characteristic;
            activity.BLEActivity = BLEActivities.READ;
            addBleActivity(activity);
        }

        public void disableNotification(BluetoothGattCharacteristic characteristic)
        {
            BLEActivity activity = new BLEActivity();
            activity.characteristic = characteristic;
            //UUID uuid = UUID.fromString("00002902-0000-1000-8000-00805f9b34fb");
            activity.descriptor = characteristic.getDescriptor(CCCDUUID);
            activity.BLEActivity = BLEActivities.DISABLE_NOTIFICATION;
            addBleActivity(activity);

        }

        public void enableNotification(BluetoothGattCharacteristic characteristic)
        {

            BLEActivity activity = new BLEActivity();
            activity.characteristic = characteristic;
            //UUID uuid = UUID.fromString("00002902-0000-1000-8000-00805f9b34fb");
            activity.descriptor = characteristic.getDescriptor(CCCDUUID);
            activity.BLEActivity = BLEActivities.ENABLE_NOTIFICATION;
            addBleActivity(activity);

        }

        public void enableNotification(BluetoothGattDescriptor descriptor)
        {
            BLEActivity activity = new BLEActivity();
            activity.descriptor = descriptor;
            activity.BLEActivity = BLEActivities.ENABLE_NOTIFICATION;
            addBleActivity(activity);

        }

        public void disableNotification(BluetoothGattDescriptor descriptor)
        {
            BLEActivity activity = new BLEActivity();
            activity.descriptor = descriptor;
            activity.BLEActivity = BLEActivities.DISABLE_NOTIFICATION;
            addBleActivity(activity);
        }

        public void clearEvent()
        {
            idle = true;
            actitvityQueue.remove();
            launchNextEvent();
        }

        public void launchNextEvent()
        {

            if(actitvityQueue.size() == 0)
                return;

            if(!idle) // if it is already busy then come back later
                return;

            idle = false; // now busy

            BLEActivity top = actitvityQueue.element(); // look at the first element in the queue

            if(top.launched)
            {
                actitvityQueue.remove();
                if(actitvityQueue.size() == 0) {
                    return;
                }

                top = actitvityQueue.element();
            }


            switch(top.BLEActivity)
            {
                case WRITE:
                    writeActivity(top);
                    break;
                case READ:
                    mBluetoothGatt.readCharacteristic(top.characteristic);
                    break;
                case ENABLE_NOTIFICATION:
                    mBluetoothGatt.setCharacteristicNotification(top.characteristic,true);
                    top.descriptor.setValue(BluetoothGattDescriptor.ENABLE_NOTIFICATION_VALUE);
                    mBluetoothGatt.writeDescriptor(top.descriptor);
                    break;
                case DISABLE_NOTIFICATION:
                    mBluetoothGatt.setCharacteristicNotification(top.characteristic,false);
                    top.descriptor.setValue(BluetoothGattDescriptor.DISABLE_NOTIFICATION_VALUE);
                    mBluetoothGatt.writeDescriptor(top.descriptor);
                    break;
            }
        }

        private void writeActivity(BLEActivity activity)
        {
            byte[] bytes  = new byte[1]; // initialized just to make error go away
            switch (activity.writeType)
            {
                case BOOLEAN:
                    bytes = new byte[1];
                    if((Boolean)activity.value)
                        bytes[0] = 1;
                    else
                        bytes[0] = 0;
                    break;
            }
            activity.characteristic.setValue(bytes);
            mBluetoothGatt.writeCharacteristic(activity.characteristic);
        }

        public void writeBoolean(BluetoothGattCharacteristic characteristic,Object value)
        {
            BLEActivity activity = new BLEActivity();
            activity.characteristic = characteristic;
            activity.BLEActivity = BLEActivities.WRITE;
            activity.writeType = BLEWriteType.BOOLEAN;
            activity.value = value;
            addBleActivity(activity);
        }
    }

}
