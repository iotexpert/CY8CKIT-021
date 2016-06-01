//
//  ViewController.swift
//  SimpleBLE
//
// Project: Example10
// Kit: CY8CKIT-021 Sheild
// Baseboard: CY8CKit-44 PSoC4M
//
//  This file contains the viewcontroller for the single view application.
//  Basically when it loads you startup and connect to the bleboard
//  then display the state of things... or let the user flip the switch
//

import UIKit

class ViewController: UIViewController {

    var bleLand : BlueToothNeighborhood!
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // bleLand-BlueToothNeighborhood is the model.  It is capable of finding
        // a CY8CKIT021 and connecting to it.
        // it can also read/write etc
        bleLand = BlueToothNeighborhood()
        bleLand.startUpCentralManager()
        
        // start with the switch disabled.  it will turn on once there is a connection
        led0switch.userInteractionEnabled = false
        bootLoaderButton.userInteractionEnabled = false
        
        
        // The global structure CY8CKITNotifications defines the different notificateions
        // that can come from the bleLand model.  Basically a connection/disconnection or
        // and update of the Led0 or Button0 State
        
        // If you get a complete connection then turn on the buttons to start working
        NSNotificationCenter.defaultCenter().addObserverForName(CY8CKIT021Notifications.ConnectionComplete, object: nil, queue: NSOperationQueue.mainQueue()) { _ in
            self.led0switch.userInteractionEnabled = true
            self.bootLoaderButton.userInteractionEnabled = true
        }
        
        // if you get disconnected then turn off the buttons
        NSNotificationCenter.defaultCenter().addObserverForName(CY8CKIT021Notifications.DisconnectedDevice, object: nil, queue: NSOperationQueue.mainQueue()) { _ in
                self.led0switch.userInteractionEnabled = false
                self.bootLoaderButton.userInteractionEnabled = false
            }
        
        
        // The we got feedback from the model about the state of the button0
        NSNotificationCenter.defaultCenter().addObserverForName(CY8CKIT021Notifications.UpdatedButton0, object: nil, queue: NSOperationQueue.mainQueue()) { _ in         self.button0.selected = self.bleLand.button0State }
        
        // The we got feedback from the model about the state of the led0
        NSNotificationCenter.defaultCenter().addObserverForName(CY8CKIT021Notifications.UpdateLed0, object: nil, queue: NSOperationQueue.mainQueue()) { _ in self.updateLed0() }
        
    }
    
    // This function grabs the current button0 state from the model and sets the button
    // to indicate it is either being pressed or not
    func updateButton0()
    {
        self.button0.selected = self.bleLand.button0State
    }
    
    // This functiong rabs the current led0 state from the model and then flips the 
    // switch the right way
    func updateLed0()
    {
        led0switch.on = bleLand.led0State
    }

    @IBOutlet weak var button0: UIButton!
    @IBOutlet weak var led0switch: UISwitch!
    
    // When the user flips the switch you need to write the updated value to the model
    @IBAction func led0SwitchAction(sender: UISwitch) {
               
            bleLand.writeLed0Characteristic(sender.on)
    }
    
    // If the user presses the bootload button then send the bootload command
    // this will cause and immediate BLE disconnect... etc
    @IBOutlet weak var bootLoaderButton: UIButton!
    @IBAction func startBootLoader(sender: AnyObject) {
        bleLand.startBootloader()
    }

}

