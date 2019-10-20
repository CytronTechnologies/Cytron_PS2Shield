/*
 * Repeated_SoftwareSerial_TX
 * 
 * Publish messages of all basic levels every 5 seconds
 * 
 * Tested on:
 *    - Arduino Mega (ATMEGA 2560)
 *    - Arduino Uno (ATMEGA 328P)
 * Test comments:
 *    Library works.
 *    Takes about 6 ms to send messages if baud rate of software serial being used is 115200
 *    Check the end of file for more comments on testing
 *    
 * Created by : @TheProjectsGuy
 * Maintained by : RoboManipal-9-0 organization
 */
// Include header files for the library
#include <DebuggerSerial.h>
// Header file for SoftwareSerial
#include <SoftwareSerial.h>
// SoftwareSerial object
SoftwareSerial softSerial(10, 11);  // Rx, Tx
// Debugger object with name
DebuggerSerial debuggerObj("MyDebugger");
void setup() {
  // Setup the software serial
  softSerial.begin(115200);
  // Attach the software serial to the debugger
  debuggerObj.AttachSerial(&softSerial);
}

void loop() {
  // Publish all kinds of possible messages every five seconds
  debuggerObj.print(DEBUG, "This is a DEBUG message");
  debuggerObj.print(INFO, "This is an INFO message");
  debuggerObj.print(WARNING, "This is a WARNING message");
  debuggerObj.print(ERROR, "This is an ERROR message");
  debuggerObj.print(FATAL, "This is a DEBUG message");
  debuggerObj.printSensorData(10);
  delay(5000);
}


/* Testing Comments
 *    Use the following code for the receiving end
 ```
 void setup() {
  // put your setup code here, to run once:
  Serial1.begin(115200);
  Serial.begin(115200);  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial1.available()) {
    Serial.print(Serial1.readStringUntil("\n"));
  }
}
```
 *  Uploaded and tested on arduino mega
 *  Connect 10 to Serial1 TX
 *  Connect 11 to Serial1 RX
 */
