//
//  globals.swift
//
// Project: Example10
// Kit: CY8CKIT-021 Sheild
// Baseboard: CY8CKit-44 PSoC4M
//

// This is the global structure to define the legal notifications for the system
// these notifications are currently used to notify the main view controller that
// the state of the board has changed
// 
struct CY8CKIT021Notifications {
    static let ConnectionComplete = "ConnectionComplete"
    static let DisconnectedDevice = "DisconnectedDevice"
    static let UpdatedButton0 = "UpdatedButton0"
    static let UpdateLed0 = "UpdatedLed0"
}