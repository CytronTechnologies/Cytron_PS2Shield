/*
 * Repeated_HardwareSerial
 * 
 * Publish messages of all basic levels every 5 seconds
 * 
 * Tested on:
 *    - Arduino Mega (ATMEGA 2560)
 *    - Arduino Uno (ATMEGA 328P)
 * Test comments:
 *    Library works.
 *    Takes about 2 ms to send messages if baud rate of hardware serial being used is 115200
 * 
 * Created by : @TheProjectsGuy
 * Maintained by : RoboManipal-9-0 organization
 */
// Include the header file 

#include <DebuggerSerial.h>
// Declare the object and pass it a name
DebuggerSerial debuggerObj("SampleDebugger");
void setup() {
  Serial.begin(115200);               // Start the serial
  debuggerObj.AttachSerial(&Serial);  // Attach serial to debugger
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

