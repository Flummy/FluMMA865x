// -*- mode: C++; tab-width: 2; c-basic-offset: 2; indent-tabs-mode: nil; coding: utf-8 -*-
//    MMA865x Accelerometer Driver Library for Arduino, Version 0.1.0, 2015-11-12
//    http://koffein.org/E/FluMMA865x/
//    Version numbering follows the http://www.semver.org Semantic Versioning 2.0.0 specification
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

#include "FluMMA865x.h"
#include "FluMMA865xI2C.h"
#include "FluMMA865xR.h"
#include "AccelDataT.h"
#define MMA8652Q_ID       0x04A // MMA8653Q_ID 0x5A

FluMMA865xR::XyzDataCfgRegT::AccelFsrT FluMMA865x::fullScaleRange = FluMMA865xR::XyzDataCfgRegT::AFS_2g;
FluMMA865xR::CtrlReg1T::AccelOdrT      FluMMA865x::outputDataRate = FluMMA865xR::CtrlReg1T::AODR_50HZ;

void FluMMA865x::begin()
{
}


void FluMMA865x::reset()
{
  FluMMA865xR::CtrlReg2T ctrlReg2;
  ctrlReg2.v = 0;
  ctrlReg2.f.RST = true; // Set reset flag
  i2c.writeByte(FluMMA865xR::CTRL_REG2, ctrlReg2.v);
  delay(2); // 2ms delay guessed, not from datasheet, single test IC: 200us ok at room temp
}


boolean FluMMA865x::devicePresent()
{
  if(MMA8652Q_ID == i2c.readByte(FluMMA865xR::WHO_AM_I)) return true;
  return false;
}


void FluMMA865x::standby()
{
  FluMMA865xR::CtrlReg1T ctrlReg1; 
  ctrlReg1.v = i2c.readByte(FluMMA865xR::CTRL_REG1);
  ctrlReg1.f.ACTIVE = false;
  i2c.writeByte(FluMMA865xR::CTRL_REG1, ctrlReg1.v);
}


void FluMMA865x::active()
{
  FluMMA865xR::CtrlReg1T ctrlReg1; 
  ctrlReg1.v = i2c.readByte(FluMMA865xR::CTRL_REG1);
  ctrlReg1.f.ACTIVE = true;
  i2c.writeByte(FluMMA865xR::CTRL_REG1, ctrlReg1.v);  
}


void FluMMA865x::clearInterrupts()
{
  (void) readData(); // Clear all interrupts by reading the data output and F_STATUS registers
  (void) i2c.readByte(FluMMA865xR::F_STATUS);
}

AccelDataT<int16_t> FluMMA865x::readData()
{
  uint8_t rawData[6];  // x/y/z accel register data stored here
  AccelDataT<int16_t> assembledData;
  i2c.readBytes(FluMMA865xR::OUT_X_MSB, 6, &rawData[0]);  // Read the six raw data registers into data array
  assembledData.xyz[0] = 1 + (((int16_t) rawData[0] << 8 | rawData[1]) >> 4); // needs less flash than a loop
  assembledData.xyz[1] = 1 + (((int16_t) rawData[2] << 8 | rawData[3]) >> 4);
  assembledData.xyz[2] = 1 + (((int16_t) rawData[4] << 8 | rawData[5]) >> 4);
  return assembledData;
}


// Factor needed to convert assembledData lsb units to milligrav
uint16_t FluMMA865x::getConversionFactorMicrograv()
{
  static const byte rezTab[] PROGMEM = {2, 4, 8};
  return ((unsigned long)pgm_read_byte_near(rezTab + fullScaleRange) * 1000000UL) / 2048UL;
}


float FluMMA865x::getConversionFactorMilligrav()
{
  static const byte rezTab[] PROGMEM = {2, 4, 8};
  return ((unsigned long)pgm_read_byte_near(rezTab + fullScaleRange) * 1000UL) / 2048.0;
}


void FluMMA865x::calibrate()
{
  uint16_t ii, fcount;
  AccelDataT<int32_t> bias = {0, 0, 0};
  AccelDataT<uint8_t> reg;
  uint8_t rawData[6];  // x/y/z FIFO accel data stored here


  clearInterrupts(); // TODO after standby?
  standby();  // Must be in standby to change registers

  i2c.writeByte(FluMMA865xR::CTRL_REG1, 0x01);      // select 100 Hz ODR
//i2c.writeByte(FluMMA865xR::CTRL_REG1, 0x71);      // select  1.5 Hz ODR    
  fcount = 100;                                     // sample for 1 second
  i2c.writeByte(FluMMA865xR::XYZ_DATA_CFG, 0x00);   // select 2 g full scale
  uint16_t accelsensitivity = 1024;                 // 1024 LSB/g

  active();  // Set to active to start collecting data
  delay(2000); // wait for device to settle
  clearInterrupts();

  for(ii = 0; ii < fcount; ii++)   // construct count sums for each axis
  {
    bias += readData(); // was AccelDataT<int16_t> temp = readData();
    delay(15);
  }

  bias /= fcount;
  
  if(bias.z > 0L) {bias.z -= (int32_t) accelsensitivity;}  // Remove gravity from the z-axis
  else {bias.z += (int32_t) accelsensitivity;}

  Serial << F("bias x=") << bias.x << "\ty=" << bias.y << "\tz=" << bias.z << "mg\n";

  reg = -bias / 2; // assumes uint8_t

  standby();  // Must be in standby mode to change registers
  delay(1);
  i2c.writeByte(FluMMA865xR::OFF_X, reg.x); // X-axis compensation  
  delay(1);
  i2c.writeByte(FluMMA865xR::OFF_Y, reg.y); // Y-axis compensation  
  delay(1);
  i2c.writeByte(FluMMA865xR::OFF_Z, reg.z); // z-axis compensation 
  delay(1);
  active();  // Set to active mode to start reading
}

