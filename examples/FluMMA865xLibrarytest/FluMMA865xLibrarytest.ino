// -*- mode: C++; tab-width: 2; c-basic-offset: 2; indent-tabs-mode: nil; coding: utf-8 -*-
//    Example for MMA865x Accelerometer Driver Library for Arduino, Version 0.1.0, 2015-11-12
//    http://koffein.org/E/FluMMA865x/
//    This work is based on the efforts of other open source engineers, please see Credits.txt
//    Copyright (c) 2015 Herwig Wittmann <lab15@koffein.org>
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Affero General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.


// Hardware setup: See HardwareSetup.txt

#include <Streaming.h>
#include <Wire.h>
#include <FluMMA865xI2C.h>        // Accelerometer I2C bus communication
#include <FluMMA865xR.h>          // Accelerometer configuration and data register layout
#include <FluMMA865x.h>           // Accelerometer basic utility functions
#include <AccelDataT.h>           // A 3D Vector data type for x/y/z data
#include "InitializeFluMMA865x.h" // InitializeMMA865x class : Set up Accelerometer with wanted configuration
#include "Demo.h"                 // reads accelerometer status and data and prints it

uint16_t                   convFactMicrograv; // factor for conversion from lsb to micrograv
AccelDataT<int16_t>        accelLsb;
AccelDataT<int32_t>        accelMicrograv;
FluMMA865xR::IntSourceRegT lastIntSourceR;

FluMMA865x           accel;
FluMMA865xI2C        comms;
InitializeFluMMA865x ini;
Demo                 demo;

void setup()
{
  Serial.begin(57600);
  while(!Serial) ;
  Serial << "\n";
  delay(200);
  Serial << F("FluMMA865x/examples/FluMMA865xLibrarytest\n");
  ini.begin();
}


void loop() 
{
  demo.work();  
}

