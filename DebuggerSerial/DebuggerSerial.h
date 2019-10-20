/*
    DebuggerSerial.h - Library for DebuggerSerial
    Copyright (c) 2018 RoboManipal. All right reserved
    File created by : Avneesh Mishra
    Last commit done by : Avneesh Mishra
*/

// Check for the flag
#ifndef DEBUGGERSERIAL_H
#define  DEBUGGERSERIAL_H

// Arduino main files
#include "Arduino.h"

// Debugger Levels
// DONE: Adjust levels and protocol
#define SENSOR_FEED 0         // Sensor data feed
#define NOTIFICATION 10       // Notifications about the debugger ONLY 
#define DEBUG 20              // Debugging level messages
#define INFO 30               // Info level messages
#define WARNING 40            // Warning level messages : Work can still go unaffected
#define ERROR 50              // Error messages : Some aspects might not work
#define FATAL 60              // Fatal messages : Some error caused the system to crash
// Number to String function
String PriorityLevelName(int priorityLevel);

class DebuggerSerial {
protected:
    // ########### Main parts of DebuggerSerial #############
    Stream *debuggerSerial;     // Main serial
    String name;    // Name of the debugger
    int debuggerPriorityLevel;    // The priority level of debugger
    // ---------------- Sanity flags ----------------
    bool debuggerEnabled;         // Enable or disable the debugger
    bool debuggerSerialDefined;   // If the debuggerSerial is defined
    // ############## Private functions ###################
    // (Main function that writes to serial)
    void DebuggerOutput(int Level, String output);   // One stop for all output to debuggerSerial 
    void RaiseNotification(String message);          // Notification messages (for DebuggerSerial library ONLY)
public:
    // ################ Initializer functions ###############
    // ----------------- Constructors ----------------------
    DebuggerSerial();     // Empty constructor
    DebuggerSerial(String name);    // Name only
    DebuggerSerial(Stream *debuggerSerial);   // DebuggerSerial only
    DebuggerSerial(int priorityLevel);   // Priority level
    DebuggerSerial(String name, int priorityLevel);  // Name and priority
    DebuggerSerial(String name, Stream *debuggerSerial); // Name and serial
    // All 3 in one
    DebuggerSerial(String name, Stream *debuggerSerial, int priorityLevel);
    // ------------ Standalone initializers ------------
    // All 3
    void Initialize(String name, Stream *debuggerSerial, int priorityLevel = 0);
    void Initialize(Stream *debuggerSerial, int priorityLevel = 0);  // Serial and priorityLevel
    // ------------ Individual initializers ------------
    void AttachSerial(Stream *debuggerSerial);   // DebuggerSerial
    void InitializeName(String name);            // Name
    void SetDebuggerPriorityToLevel(int minLevel);  // Level
    // ------------ Settings for debugger ------------
    void enableDebugger();       // Enable the debugger
    void disableDebugger();      // Disable the debugger
    // ----------------- Print messages to debuggerSerial -----------------
    void printMessage(int level, String output);    // Print message
    void print(int level, String output);           // Print message
    void print(String output, int level);           // Print, order or args reversed
    void printSensorData(double value);             // Print the value as SENSOR_FEED level
    void printSensorData(String data);              // Print values as sensor feed (directly as string)
};

#endif
