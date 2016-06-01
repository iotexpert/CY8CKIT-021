// BlueToothNeighborhood.swift
//
// Project: Example10
// Kit: CY8CKIT-021 Sheild
// Baseboard: CY8CKit-44 PSoC4M
//
// This file contains the model for the CY8CKIT021 board with 1 LED0 and 1 Button 0
//

import CoreBluetooth


// This structure conatains the UUIDS for the services and characteristics on the board
// it MUST match what you defined in the creator BLE Configuration Wizard
private struct BLEParameters {
    static let CY8CKIT021Service = CBUUID(string: "00000000-0000-1000-8000-00805F9B3400")
    static let bootloadCharactersticUUID = CBUUID(string:"00000000-0000-1000-8000-00805F9B3401")
    static let ledCharactersticUUID = CBUUID(string:"00000000-0000-1000-8000-00805F9B3402")
    static let buttonCharactersticUUID = CBUUID(string:"00000000-0000-1000-8000-00805F9B3404")

}

// The model for the board
// The BlueToothNeighborhood has BOTH the board model and the Bluetooth model.  This
// makes the code slightly simpler to explain but is a bit weird architectururally
class BlueToothNeighborhood: NSObject, CBCentralManagerDelegate, CBPeripheralDelegate  {
    
    private var centralManager : CBCentralManager!
    private var CY8CKIT021Board : CBPeripheral?
    private var CY8CKIT021Service : CBService!
    private var led0Characteristic : CBCharacteristic!
    private var button0Characteristic : CBCharacteristic!
    private var bootloadCharacteristic : CBCharacteristic!

    // This function is called by the main view controller to get things going
    func startUpCentralManager() {
        centralManager = CBCentralManager(delegate: self, queue: nil)
    }
    
    // This is the bluetooth delegate function
    @objc func centralManagerDidUpdateState(central: CBCentralManager) {
        switch (central.state) {
        case .PoweredOff: break
        case .PoweredOn:
            print("Bluetooth is on - Starting scan")
            // start scanning for a device that we can talk to
            centralManager.scanForPeripheralsWithServices([BLEParameters.CY8CKIT021Service], options: [CBCentralManagerScanOptionAllowDuplicatesKey:false])

        case .Resetting: break
        case .Unauthorized: break
        case .Unknown:break
        case .Unsupported:break
        }
    }
    
    // This delegate function is called by the bluetooth when it finds a device
    // that matches our UUID that we told it when we started the scan
    func centralManager(central: CBCentralManager, didDiscoverPeripheral peripheral: CBPeripheral, advertisementData: [String : AnyObject], RSSI: NSNumber)
    {
        // if you already are connected to a device ignore this one
        if CY8CKIT021Board == nil {
            print("Found a new Periphal advertising CY8CKIT021 Service")
            CY8CKIT021Board = peripheral
            centralManager.stopScan()
            centralManager.connectPeripheral(CY8CKIT021Board!, options: nil)
        }
    }
    
    // This delegate is called when a device connection is complete
    func centralManager(central: CBCentralManager, didConnectPeripheral peripheral: CBPeripheral) {
        print("Connection complete \(CY8CKIT021Board) \(peripheral)")
        CY8CKIT021Board!.delegate = self
        CY8CKIT021Board!.discoverServices(nil)
    }
    
    // This delegate is called after the service discovery is complete
    func peripheral(peripheral: CBPeripheral, didDiscoverServices error: NSError?) {
        print("discovered services")
        for service in peripheral.services! {
            print("Found service \(service)")
            if service.UUID == BLEParameters.CY8CKIT021Service {
                CY8CKIT021Service = service // as! CBService
            }
        }
        CY8CKIT021Board!.discoverCharacteristics(nil, forService: CY8CKIT021Service)
    }
    
    
    // This delegate is called when the characteristic discovery is complete
    func peripheral(peripheral: CBPeripheral, didDiscoverCharacteristicsForService service: CBService, error: NSError?) {
        for characteristic in service.characteristics!
        {
            
            print("Found characteristic \(characteristic)")
            switch characteristic.UUID {
            case BLEParameters.buttonCharactersticUUID: button0Characteristic = characteristic
            case BLEParameters.ledCharactersticUUID: led0Characteristic = characteristic
            case BLEParameters.bootloadCharactersticUUID: bootloadCharacteristic = characteristic
            default: break
            }
        }
        
        // You have a complete connection... so find out the current state of the LED0
        // and Button.. then notify the viewcontroller that things are rolling
        
        // read the led0 characteristic to find out its current state
        CY8CKIT021Board?.readValueForCharacteristic(led0Characteristic)
    
        // read the button0 characteristic to find out its current state
        CY8CKIT021Board?.readValueForCharacteristic(button0Characteristic)

        CY8CKIT021Board!.setNotifyValue(true, forCharacteristic: button0Characteristic)
        NSNotificationCenter.defaultCenter().postNotificationName(CY8CKIT021Notifications.ConnectionComplete, object: nil)
    }
    
    // disconnected device - start scanning again
    func centralManager(central: CBCentralManager, didDisconnectPeripheral peripheral: CBPeripheral, error: NSError?) {
        print("Disconnected \(peripheral)")
        CY8CKIT021Board = nil
        NSNotificationCenter.defaultCenter().postNotificationName(CY8CKIT021Notifications.DisconnectedDevice, object: nil)
        centralManager.scanForPeripheralsWithServices([BLEParameters.CY8CKIT021Service], options: [CBCentralManagerScanOptionAllowDuplicatesKey:false])
        
    }
    
    // start the bootloader...this will cause an immediate disconnect by the board
    func startBootloader()
    {
        var val: UInt8 = 1 // it doesnt matter the value... any write will cause the bootloader to start
        let ns = NSData(bytes: &val, length: sizeof(UInt8))
        CY8CKIT021Board!.writeValue(ns, forCharacteristic: bootloadCharacteristic, type: CBCharacteristicWriteType.WithResponse)
    }
    

    // a helper function to write the the device
    func writeLed0Characteristic(state: Bool)
    {
        var val : Int8
        if(state)
        {
            val = 1
        }
        else
        {
            val = 0
        }
        let ns = NSData(bytes: &val, length: sizeof(Int8))
        CY8CKIT021Board!.writeValue(ns, forCharacteristic: led0Characteristic, type: CBCharacteristicWriteType.WithResponse)
    }
    
    // this is the model of the board
    var button0State : Bool = false 
    var led0State : Bool = false // assume that it is off
    
    // This delegate function is called when an updated value is received from the Bluetooth Stack
    func peripheral(peripheral: CBPeripheral, didUpdateValueForCharacteristic characteristic: CBCharacteristic, error: NSError?) {
        if characteristic == button0Characteristic {
            var out: UInt8 = 0
            characteristic.value!.getBytes(&out, length:sizeof(UInt8))
            if(out == 0)
            {
                button0State = false
            }
            else
            {
                button0State = true
            }
            NSNotificationCenter.defaultCenter().postNotificationName(CY8CKIT021Notifications.UpdatedButton0, object: nil)
        }
        
        if characteristic == led0Characteristic {
            var out: NSInteger = 0
            characteristic.value!.getBytes(&out, length:sizeof(UInt8))
            if(out == 0)
            {
                led0State = false
            }
            else
            {
                led0State = true
            }
            NSNotificationCenter.defaultCenter().postNotificationName(CY8CKIT021Notifications.UpdateLed0, object: nil)
        }
    }
}

