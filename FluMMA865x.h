// -*- mode: C++; tab-width: 2; c-basic-offset: 2; indent-tabs-mode: nil; coding: utf-8 -*-
//    MMA865x Accelerometer Driver Library for Arduino, Version 1, 2015-11-12
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

// Wire.begin() must be called before any I2C communications take place

// Hardware setup: See HardwareSetup.txt

#pragma once

#include <Arduino.h>
#include "FluMMA865xI2C.h"
#include "FluMMA865xReg.h"
#include "AccelDataT.h"

class FluMMA865x
{
public:

  static FluMMA865xI2C i2c; // "instantiating" a class with static methods multiple times causes no memory overhead
  static FluMMA865xR::XyzDataCfgRegT::AccelFsrT fullScaleRange;
  static FluMMA865xR::CtrlReg1T::AccelOdrT      outputDataRate;


  static void     begin();
  static void     reset();         // Command device to execute reset
  static boolean  devicePresent(); // Request device-specific ID
  static void     standby();       // Device must be in standby mode for most config register changes
  static void     active();        // Device must be in active mode to provide data
  static void     clearInterrupts();
  static AccelDataT<int16_t> readData();
  static uint16_t getConversionFactorMicrograv();
  static float    getConversionFactorMilligrav();
  static void     calibrate();
};
