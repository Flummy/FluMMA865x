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

#include "Demo.h"

void Demo::work()
{
  FluMMA865xR::IntSourceRegT intSourceR;
  FluMMA865xR::StatusRegT    statusR;
  intSourceR.v = comms.readByte(FluMMA865xR::INT_SOURCE); // check if any interrupts are pending
  
  if(0 != intSourceR.v && intSourceR.v != lastIntSourceR.v)
  {
    //intSourceR.print();
    lastIntSourceR.v = intSourceR.v;
  }

  if(intSourceR.f.SRC_DRDY) // data ready
  {
    statusR.v = comms.readByte(FluMMA865xR::F_STATUS); // clear all int flags by reading F_STATUS and data output regs
    if(statusR.f.ZYXDR) accelDataHandler();
    else Serial << F("spurious SRC_DRDY interrupt\n");
  }

  if(intSourceR.f.SRC_ASLP) // Int source: sleep/wake Int
  {
    Serial << F("SLEEP/ACTIVE\n");
    comms.readByte(FluMMA865xR::SYSMOD); // clear sleep interrupt by reading SYSMOD
  }

  if(intSourceR.f.SRC_TRANS)  transientHandler();   // handles transient event = transient IRQ
  if(intSourceR.f.SRC_FF_MT)  motionHandler();      // handles free fall / motion event
  if(intSourceR.f.SRC_LNDPRT) orientationHandler(); // handles orientation change event (landscape/portrait)
  if(intSourceR.f.SRC_PULSE)  pulseHandler();       // handles pulse/tap event
}


void Demo::accelDataHandler()
{
  accelLsb = accel.readData();
  //accelMicrograv = accelLsb * (uint32_t) convFactMicrograv; // TODO
  //accelMicrograv.x = (uint32_t) accelLsb.x * (uint32_t) convFactMicrograv;
  //accelMicrograv.y = (uint32_t) accelLsb.y * (uint32_t) convFactMicrograv;
  //accelMicrograv.z = (uint32_t) accelLsb.z * (uint32_t) convFactMicrograv;
  if(abs(accelLsb.x) > 1 || abs(accelLsb.y) > 1 || abs(accelLsb.z) > 1)
    Serial << "x=" << accelLsb.x       << F("\t y=") << accelLsb.y       << F("\t z=") << accelLsb.z
           << "\n";
         //<< "x=" << accelMicrograv.x << F("\t y=") << accelMicrograv.y << F("\t z=") << accelMicrograv.z << F("ug\n");  
}


void Demo::transientHandler()
{
  static uint32_t timeLastTransient = 0;
  FluMMA865xR::TransientSrcRegT transientSrcR;
  
  if(millis() - timeLastTransient   <   100) return;

  transientSrcR.v = comms.readByte(FluMMA865xR::TRANSIENT_SRC);
  if(!transientSrcR.f.EA) Serial << F("spurious transient interrupt\n");
  transientSrcR.print();
  timeLastTransient = millis();
}


void Demo::motionHandler()
{
  static uint32_t timeLastMotion = 0;
  FluMMA865xR::FfMtSrcRegT ffMtSrcR;
  
  if(millis() - timeLastMotion   <   100) return;

  ffMtSrcR.v = comms.readByte(FluMMA865xR::FF_MT_SRC);
  if(!ffMtSrcR.f.EA) Serial << F("spurious motion interrupt\n");
  ffMtSrcR.print();
  timeLastMotion = millis();
}


void Demo::orientationHandler()
{
  byte pl = comms.readByte(FluMMA865xR::PL_STATUS);  // Reads the PL_STATUS register
  switch((pl&0x06)>>1)  // Check on the LAPO[1:0] bits
  {
  case 0:
    Serial << F("A-PortraitUp, ");
    break;
  case 1:
    Serial << F("B-PortraitDown, ");
    break;
  case 2:
    Serial << F("C-LandscapeRight, ");
    break;
  case 3: 
    Serial << F("D-LandscapeLeft, ");
    break;
  }
  
  if (pl & 0x01)  // Check the BAFRO bit
    Serial << F("Back");
  else
    Serial << ("Front");
  if (pl & 0x40)  // Check the LO bit
    Serial.print(", Z-tilt!");
    
  Serial.println();
}


void Demo::pulseHandler()
{
  FluMMA865xR::PulseSrcRegT pulseSrcR;
  pulseSrcR.v = comms.readByte(FluMMA865xR::PULSE_SRC);  // Reads the PULSE_SRC register
  pulseSrcR.print();
}

