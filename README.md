# FluMMA865x
Flummy's Arduino Library / Device driver for the MMA865x I2C accelerometers
http://koffein.org/E/FluMMA865x/


This low-power device can trigger interrupts for four kinds of events
*********************************************************************
Free fall/Motions events when the device is dropping or moved,
Landscape/Portrait Front/Back events when the device is tilted on any of its 6 surfaces,
Pulse/Tap/Double Tap events if it is tapped, and
Transient events (similiar to Motion, but read the Data sheet)


This is an experimental attempt to fully encapsulate a device driver in C++ classes
and unions: 

The 8-bit-registers of the device can be accessed by their 8-bit byte value .v:
intSourceR.v = comms.readByte(FluMMA865xR::INT_SOURCE); // check if any interrupts are pending

or by their flag structure .f:
if(intSourceR.f.SRC_FF_MT) Serial << F("Free fall / motion event detected!\n");


Quick Start
***********
1. Copy this library to you $HOME/sketchbook/libraries/ Folder.
  The resulting diretory tree should like this: sketchbook/libraries/FluMMA865x/
  and the FluMMA865x*.cpp and *.h files should reside directly there.
  
2. Wire up an MMA865x accelerometer as described in HardwareSetup.txt

3. Quit and restart your Arduino IDE.

4. Using the IDE, navigate to File > Examples > FluMMA865x > FluMMA865xLibrarytest
   to load the demo sketch.
   
5. Compile and upload the sketch to your Arduino with the connected accelerometer.

6. Open a serial terminal and set it to 57600 baud. You should see a line
   identifying the running sketch as "...FluMMA865xLibrarytest".
   
7. Move the accelerometer with various speeds and observe the generated events and outputs.

[EOF]
