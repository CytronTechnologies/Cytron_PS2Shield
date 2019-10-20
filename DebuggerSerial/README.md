![Version tag](https://img.shields.io/badge/version-1.0.1-orange.svg)
# Introduction
The **DebuggerSerial** library is for defining and using a serial as a debugger.

~~**Node**: This library is still in developer beta, ask the developer before using.~~ This library has finished testing :tada:. Check [examples](#examples).

# Index
- [Introduction](#introduction)
- [Index](#index)
- [Users Guide](#users-guide)
    - [Downloading the library](#downloading-the-library)
    - [Using the library with Arduino](#using-the-library-with-arduino)
    - [Using the library](#using-the-library)
    - [Protocol implementation](#protocol-implementation)
        - [About the priority levels](#about-the-priority-levels)
    - [Examples](#examples)
        - [Repeated_HardwareSerial](#repeatedhardwareserial)
        - [Repeated_SoftwareSerial_TX](#repeatedsoftwareserialtx)
- [Developers Guide](#developers-guide)
    - [Library Details](#library-details)
        - [Files in the library](#files-in-the-library)
            - [DebuggerSerial.h](#debuggerserialh)
            - [DebuggerSerial.cpp](#debuggerserialcpp)
            - [keywords.txt](#keywordstxt)
            - [README.md](#readmemd)
        - [Code description](#code-description)
        - [Debugger](#debugger)
        - [DebuggerSerial class](#debuggerserial-class)
            - [Protected members](#protected-members)
                - [Variables](#variables)
                - [Functions](#functions)
            - [Public](#public)
                - [Constructors](#constructors)
                - [Functions](#functions)
- [Debugger Notifications](#debugger-notifications)
    - [Notification level](#notification-level)
    - [Sensor feed level](#sensor-feed-level)
    - [All user levels](#all-user-levels)

# Users Guide

## Downloading the library
It is suggested that you download the entire repository and then select this folder, so that you can enjoy the benefits of VCS like git. It makes it simpler to update the contents whenever patch fixes are done. You can simply open a terminal (or gitbash on windows), go to the folder where you want to save this repository and type the following command.
```bash
git clone https://github.com/RoboManipal-9-0/Libraries.git -b dev
```
_You might want to omit the `-b <branch>` tag if you're downloading from the master branch_.

**<font color="#AA0000">Not recommended</font>** : You can download just this folder by clicking [here](placeholder).

## Using the library with Arduino
Move this folder into the arduino libraries folder on your PC. If you don't know where the libraries folder of your arduino is, you can check out the README file of this entire repository for this, click [here](../README.md).

## Using the library
- Declare an object of `DebuggerSerial` class.
- Call the function **Initialize** to initialize the debugger, you may also use the constructor.

## Protocol implementation
Here are how the messages are put out on the _debuggerSerial_ for different priority levels
- For `SENSOR_FEED` data
```
[%Timestamp%] $%Name%$ %Value%
```
- For `NOTIFICATION` data
```
[%Timestamp%] > %Message%
```
- For other user based priority levels
```
[%Timestamp% %LevelToString%] $%Name%$ %Message%
```
> **Timestamp** or **TS** is the number of milliseconds passed after the initialization of the microcontroller.<br>
> **LevelToString** is the level converted to string form using the _PriorityLevelName_ function.<br>
> **Name**: Name of the debugger.<br>
> **Value**: Sensor floating point data converted to string type.<br>
> **Message**: String message to be sent.

### About the priority levels
| Priority Level | Description |  Use case Example |Protocol implementation |
| :------: | :---- | :------ | :----- |
| **SENSOR_FEED** | Used to publish **ONLY** floating point data published by sensors. | IMU Data | [**TS**] \$**Name**\$ **Value** |
| **NOTIFICATION** | Used by the _DebuggerSerial_ library to give notifications about the debugger itself. It's not suggested to use this priority level outside the _DebuggerSerial_ class. | Debugger initialized (_do not use this tag_) | [**TS**] > **Message** |
| **DEBUG** | Debugging level messages for debugging phase | Continuous values given to actuators | [**TS** _**DEBUG**_] \$**NAME**\$ **Message** |
| **INFO** | Information level messages | Pin connections and initialization, mode settings | [**TS** _**INFO**_] \$**NAME**\$ **Message** |
| **WARNING** | Warning level messages. An exception occurred but it won't cause any problems in the functioning (it can be handled) | Collision alerts that can be handled | [**TS** _**WARNING**_] \$**NAME**\$ **Message** |
| **ERROR** | Error level messages. An exception occurred and some functionalities might have been compromised | A sensor or serial connection disconnected | [**TS** _**ERROR**_] \$**NAME**\$ **Message** |
| **FATAL** | Fatal level messages. An exception occurred and the entire functioning is jeopardized. | Battery level low; Controller link lost; | [**TS** _**FATAL**_] \$**NAME**\$ **Message** |

## Examples
### Repeated_HardwareSerial
**File**: Code [here](./examples/Repeated_HardwareSerial/Repeated_HardwareSerial.ino).
- Declare a DebuggerSerial and send messages of all priorities and a sensor reading every 5 seconds.

### Repeated_SoftwareSerial_TX
**File**: Code [here](./examples/Repeated_SoftwareSerial_TX/Repeated_SoftwareSerial_TX.ino).
- Same as **Repeated_HardwareSerial** 
- We use a software serial instead of hardware serial here.

# Developers Guide
Here is the developers guide to the library. <br>
This markdown is best viewed in [_Atom_](https://atom.io/) and [VSCode](https://code.visualstudio.com/) editor.

## Library Details

### Files in the library
Let's first explore about all the files in this library

#### DebuggerSerial.h
This is the header file and contains the class blueprint (prototypes). We will explore the details about the class soon.

#### DebuggerSerial.cpp
This is the file that contains the main code for the class. In the header file, only the function prototypes are mentioned, the code for the functions (definitions) are present in this file.

#### keywords.txt
This file contains the keywords that we want the Arduino IDE to identify. This provides syntax highlighting features for the library for convenience of the programmer.

#### README.md
The description file containing details about the library. The file that you are reading right now.

### Code description
This library assumes the following :-
- You have an ATMEGA Microcontroller (or a microcontroller supported by Arduino IDE) which will host the debugger on a _HardwareSerial_ or _SoftwareSerial_.

The purpose of the *DebuggerSerial* class is to create a pipeline for Debugger.

Let's explore the code in detail
### Debugger 
- Priority levels, each one of these is a constant defined in the header file.
    - `SENSOR_FEED`: To send sensor data to the serial. Use _printSensorData_ to send sensor readings.
    - `NOTIFICATION`: To send out notifications from the library itself, it's suggested that the user doesn't use these. It's **only** for the library alone.
    - `DEBUG`: Debugging messages
    - `INFO`: Messages that given information messages
    - `WARNING`: Warning messages. An issue has occurred, but the functioning will not be affected.
    - `ERROR`: Error messages. An issue has occurred, the standard functioning might have been compromised.
    - `FATAL`: Fatal messages. An issue has occurred, the functioning is completely compromised.
- Global functions 
    -  **<font color="#5052FF">String</font> <font color="#f2e165">PriorityLevelName</font>(<font color="#76bef2">int</font> priorityLevel)**: Returns the _String_ equivalent of the priority level.

### DebuggerSerial class
#### Protected members
##### Variables
- **<font color="#87ff7c">Stream</font> \*debuggerSerial**: Main debugger serial through which the messages are transmitted.
- **<font color="#3d8aff">String</font> name**: Name of the debugger.
- **<font color="#3d8aff">int</font> debuggerPriorityLevel**: The priority level of debugger. Messages having a priority level lesser than this are going to be discarded.
- **<font color="#3d8aff">bool</font> debuggerEnabled**: Flag to check if the debugger is enabled or not.
- **<font color="#3d8aff">bool</font> debuggerSerialDefined**: Flag to check if the debugger serial has been attached or not.

##### Functions
- **<font color="#3d8aff">void</font> <font color="#f7e47b">DebuggerOutput</font>(<font color="#3d8aff">int</font> Level, <font color="#3d8aff">int</font> output)**: Print a message on the _debuggerSerial_.
- **<font color="#3d8aff">void</font> <font color="#f7e47b">RaiseNotification</font>(<font color="#3d8aff">String</font> message)**: Publish notifications about the _Debugger_ on the serial.

#### Public
##### Constructors
- **<font color="#fceb8f">DebuggerSerial</font> ()**: Empty constructor
- **<font color="#fceb8f">DebuggerSerial</font> (<font color="#3d8aff">String</font> name)**: Assign name only
- **<font color="#fceb8f">DebuggerSerial</font> (<font color="#3d8aff">int</font> priorityLevel)**: Assign priority level only
- **<font color="#fceb8f">DebuggerSerial</font> (<font color="#87ff7c">Stream</font> \*debuggerSerial)**: Assign the debuggerSerial only
- **<font color="#fceb8f">DebuggerSerial</font> (<font color="#3d8aff">String</font> name, <font color="#3d8aff">int</font> priorityLevel)**: Assign name and priority level to the debugger
- **<font color="#fceb8f">DebuggerSerial</font> (<font color="#3d8aff">String</font> name, <font color="#87ff7c">Stream</font> \*debuggerSerial)**: Assign _name_ and _debuggerSerial_ to debugger
- **<font color="#fceb8f">DebuggerSerial</font> (<font color="#3d8aff">String</font> name, <font color="#87ff7c">Stream</font> \*debuggerSerial, <font color="#3d8aff">int</font> priorityLevel)**: Assign _name_, _debuggerSerial_ and _priorityLevel_

##### Functions
- **<font color="#3d8aff">void</font> <font color="#f9e784">Initialize</font>(<font color="#3d8aff">String</font> name, <font color="#87ff7c">Stream</font> \*debuggerSerial, <font color="#3d8aff">int</font> priorityLevel = 0)**: Initializer to assign _name_, _debuggerSerial_ and _priorityLevel_. By default, the lowest level is 0 (minimum), it's the *SENSOR_FEED* level.
- **<font color="#3d8aff">void</font> <font color="#f9e784">Initialize</font>(<font color="#87ff7c">Stream</font> \*debuggerSerial, <font color="#3d8aff">int</font> priorityLevel = 0)**: Initializer for _debuggerSerial_ and _priorityLevel_
- **<font color="#3d8aff">void</font> <font color="#f9e784">AttachSerial</font>(<font color="#87ff7c">Stream</font> \*debuggerSerial)**: Attach the _debuggerSerial_ only (standalone)
- **<font color="#3d8aff">void</font> <font color="#f9e784">AttachSerial</font>(<font color="#3d8aff">String</font> name)**: Attach the _name_ only (standalone)
- **<font color="#3d8aff">void</font> <font color="#f9e784">SetDebuggerPriorityToLevel</font>(<font color="#3d8aff">int</font> minLevel)**: Attach the _debuggerPriorityLevel_ only (standalone)
- **<font color="#3d8aff">void</font> <font color="#f9e784">enableDebugger</font>()**: Enable the debugger
- **<font color="#3d8aff">void</font> <font color="#f9e784">disableDebugger</font>()**: Disable the debugger
- **<font color="#3d8aff">void</font> <font color="#f9e784">printMessage</font>(<font color="#3d8aff">int</font> level, <font color="#3d8aff">String</font> output)**: Print message to the _debuggerSerial_
- **<font color="#3d8aff">void</font> <font color="#f9e784">print</font>(<font color="#3d8aff">int</font> level, <font color="#3d8aff">String</font> output)**: Print message to the _debuggerSerial_ (alternate to printMessage)
- **<font color="#3d8aff">void</font> <font color="#f9e784">print</font>(<font color="#3d8aff">String</font> output, <font color="#3d8aff">int</font> level)**: Print message to the _debuggerSerial_ (alternate to printMessage). Arguments are reversed
- **<font color="#3d8aff">void</font> <font color="#f9e784">printSensorData</font>(<font color="#3d8aff">double</font> value)**: Print the value of a sensor reading on _debuggerSerial_.
- **<font color="#3d8aff">void</font> <font color="#f9e784">printSensorData</font>(<font color="#3d8aff">String</font> data)**: Print the data of a sensor reading on _debuggerSerial_ (data is passed as a string here).

# Debugger Notifications
## Notification level
1. **AttachSerial** function<br>
    Notifies about the debugger link being connected.
    ```bash
    [TIMESTAMP] > DebuggerSerial attached
    ```
    For example:<br>
    - Debugger attached 10 milliseconds into the program
        ```bash
        [10] > DebuggerSerial attached
        ```
2. **InitializeName** function<br>
   Notifies about the name of the debugger being initialized.
   ```bash
   [TIMESTAMP] > Debugger name initialized to %name%
   ```
   For example:<br>
    - Debugger name set to _TWBase_ 11524 milliseconds into the start of the execution.
        ```bash
        [11524] > Debugger name initialized to TWBase
        ```
3. **SetDebuggerPriorityToLevel** function<br>
    Notifies about the current priority level of the debugger.
    ```
    [TIMESTAMP] > Debugger set to %LEVEL_STRING%
    ```
    For example:<br>
    - Debugger set to priority **WARNING** at 11500 milliseconds from start of execution
        ```
        [11500] > Debugger set to WARNING
        ```
4. **enableDebugger** and **disableDebugger** functions<br>
    Tell the state of the debugger (if changed). Note that the debugger is activated the moment you initialize it a serial.
    ```
    [TIMESTAMP] > Debugger %state%
    ```
    For example:
    - Debugger enabled after 24000 milliseconds from start
        ```
        [24000] > Debugger enabled
        ```
    - Debugger disabled after 72000 milliseconds from start
        ```
        [72000] > Debugger disabled
        ```

## Sensor feed level
1. **printSensorData** function<br>
    It takes in sensor readings (as a floating value) and prints it as a string.
    ```
    [TIMESTAMP] $%Name%$ %value%
    ```
    For example:
    - Print the sensor value 25.7 after 76000 milliseconds from start on a serial named _BaseDebugger_
        ```
        [76000] $BaseDebugger$ 25.7
        ```

## All user levels
All user levels can be accessed using the function **DebuggerOutput**. It's a private function, only **print**, **printMessage** and **printSensorData** can access it.

[![Image](https://img.shields.io/badge/developed%20using-VSCode-lightgrey.svg)](https://code.visualstudio.com/)
[![Image](https://img.shields.io/badge/Developer-TheProjectsGuy-blue.svg)](https://github.com/TheProjectsGuy)
[![Spawning issue](https://img.shields.io/badge/issue-%237-green.svg)](https://github.com/RoboManipal-9-0/Libraries/issues/7)