package com.iotexpert.example10;

import android.Manifest;
import android.app.AlertDialog;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.IBinder;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.Switch;
import android.widget.ToggleButton;

public class MainActivity extends AppCompatActivity {

    private final static String TAG = CY8CKIT021.class.getSimpleName();


    private Button mBootLoad;
    private ToggleButton mButton0;
    private Switch mLed0Switch;
    private Button mScan;

    CY8CKIT021 mCY8CKIT021Model;

    private final ServiceConnection mServiceConnection = new ServiceConnection() {

        /**
         * This is called when the PSoCCapSenseLedService is connected
         *
         * @param componentName the component name of the service that has been connected
         * @param service service being bound
         */
        @Override
        public void onServiceConnected(ComponentName componentName, IBinder service) {
            Log.i(TAG, "onServiceConnected");
            mCY8CKIT021Model = ((CY8CKIT021.LocalBinder) service).getService();
            mCY8CKIT021Model.initialize();
        }

        /**
         * This is called when the PSoCCapSenseService is disconnected.
         *
         * @param componentName the component name of the service that has been connected
         */
        @Override
        public void onServiceDisconnected(ComponentName componentName) {
            Log.i(TAG, "onServiceDisconnected");
            mCY8CKIT021Model = null;
        }
    };


    private static final int PERMISSION_REQUEST_COARSE_LOCATION = 1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(com.iotexpert.example10.R.layout.activity_main);

        mBootLoad = (Button) findViewById(com.iotexpert.example10.R.id.bootloadbutton);
        mLed0Switch = (Switch) findViewById(com.iotexpert.example10.R.id.led0switch);
        mButton0 = (ToggleButton) findViewById(com.iotexpert.example10.R.id.button0);
        mScan = (Button) findViewById(com.iotexpert.example10.R.id.scanbutton);

        mBootLoad.setEnabled(false);
        mLed0Switch.setChecked(false);
        mButton0.setEnabled(false);
        mButton0.setClickable(false);

        //This section required for Android 6.0 (Marshmallow)
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            // Android M Permission check 
            if (this.checkSelfPermission(Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
                final AlertDialog.Builder builder = new AlertDialog.Builder(this);
                builder.setTitle("This app needs location access ");
                builder.setMessage("Please grant location access so this app can detect devices.");
                builder.setPositiveButton(android.R.string.ok, null);
                builder.setOnDismissListener(new DialogInterface.OnDismissListener() {
                    public void onDismiss(DialogInterface dialog) {
                        requestPermissions(new String[]{Manifest.permission.ACCESS_COARSE_LOCATION}, PERMISSION_REQUEST_COARSE_LOCATION);
                    }
                });
                builder.show();
            }
        } //End of section for Android 6.0 (Marshmallow)


        mBootLoad.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //mCY8CKIT021Model.readButton0Characteristic();
                //mCY8CKIT021Model.setNotify();
                mCY8CKIT021Model.writeButton0Notification(true);
            }
        });


        mScan.setOnClickListener(new View.OnClickListener() {
            @Override public void onClick(View v) {
                mCY8CKIT021Model.scan();
                mScan.setEnabled(false);
                Log.d(TAG,"Clicked Scan Button");
            }
        });

        mLed0Switch.setOnClickListener(new View.OnClickListener() {
            @Override public void onClick(View v) {
                mCY8CKIT021Model.writeLed0Characteristic(mLed0Switch.isChecked());
                //mCY8CKIT021Model.writeLed0Characteristic(true);

            }
        });

        Log.d(TAG, "Starting BLE Service");
        Intent gattServiceIntent = new Intent(this, CY8CKIT021.class);
        bindService(gattServiceIntent, mServiceConnection, BIND_AUTO_CREATE);

    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.d(TAG,"OnResume: adding filters");
        final IntentFilter filter = new IntentFilter();
        filter.addAction(CY8CKIT021.ACTION_CONNECTED);
        filter.addAction(CY8CKIT021.ACTION_DISCONNECTED);
        filter.addAction(CY8CKIT021.ACTION_UPDATED_LED0);
        filter.addAction(CY8CKIT021.ACTION_UPDATED_BUTTON0);
        registerReceiver(mBleUpdateReceiver, filter);
    }

    @Override
    protected void onPause() {
        super.onPause();
        unregisterReceiver(mBleUpdateReceiver);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        // Close and unbind the service when the activity goes away
        mCY8CKIT021Model.close();
        unbindService(mServiceConnection);
    }


    /**
     */
    private final BroadcastReceiver mBleUpdateReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            final String action = intent.getAction();
            Log.d(TAG,action);
            switch (action) {

                case CY8CKIT021.ACTION_CONNECTED:
                        mBootLoad.setEnabled(true);
                        mLed0Switch.setEnabled(true);
                        mButton0.setEnabled(true);
                        Log.d(TAG, "Connected to Device");
                    break;
                case CY8CKIT021.ACTION_DISCONNECTED:
                    // Turn off and disable the LED and CapSense switches
                    mLed0Switch.setEnabled(false); // turn off the Led switch
                    mBootLoad.setEnabled(false); // turn off the bootload button
                    mButton0.setEnabled(false);
                    mScan.setEnabled(true);
                    Log.d(TAG, "Disconnected");

                    break;
                case CY8CKIT021.ACTION_UPDATED_BUTTON0:
                    Log.d(TAG,"Button Update=" + mCY8CKIT021Model.isButton0SwitchState());
                    mButton0.setChecked(mCY8CKIT021Model.isButton0SwitchState()); // ask the model the current state of the button

                    break;
                case CY8CKIT021.ACTION_UPDATED_LED0:
                    mLed0Switch.setChecked(mCY8CKIT021Model.isLed0SwitchState()); // ask the model the current state of the switch
                    break;
                default:
                    break;
            }
        }
    };

}
