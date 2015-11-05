// -*- mode: C++; tab-width: 2; c-basic-offset: 2; indent-tabs-mode: nil; coding: utf-8 -*-
// (c) Flummy 2015 <lab15@koffein.org> All rights reserved.

// Wire.begin() must be called before any I2C communications take place

#pragma once

#include <Arduino.h>
#include "MMA865x_I2C.h"
#include "MMA865x_Reg.h"
#include "AccelDataT.h"

class MMA865x
{
public:

  static MMA865x_I2C i2c; // "instantiating" a class with static methods multiple times causes no memory overhead
  static MMA865x_Reg::XyzDataCfgRegT::AccelFsrT fullScaleRange;
  static MMA865x_Reg::CtrlReg1T::AccelOdrT outputDataRate;


  static void       begin();
  static void       reset();         // Command device to execute reset
  static boolean    devicePresent(); // Request device-specific ID
  static void       standby();       // Device must be in standby mode for most config register changes
  static void       active();        // Device must be in active mode to provide data
  static AccelDataT<int16_t> readAccelData();
  static uint16_t            getConversionFactorMicrograv();
  static void       calibrate();
};
