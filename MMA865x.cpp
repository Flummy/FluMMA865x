// -*- mode: C++; tab-width: 2; c-basic-offset: 2; indent-tabs-mode: nil; coding: utf-8 -*-
// (c) Flummy 2015 <lab15@koffein.org> All rights reserved.

#include "MMA865x.h"
#include "MMA865x_I2C.h"
#include "MMA865x_Reg.h"
#include "AccelDataT.h"
#define MMA8652Q_ID       0x04A // MMA8653Q_ID 0x5A

MMA865x_Reg::XyzDataCfgRegT::AccelFsrT MMA865x::fullScaleRange = MMA865x_Reg::XyzDataCfgRegT::AFS_2g;
MMA865x_Reg::CtrlReg1T::AccelOdrT MMA865x::outputDataRate = MMA865x_Reg::CtrlReg1T::AODR_50HZ;

void MMA865x::begin()
{
}


void MMA865x::reset()
{
  MMA865x_Reg::CtrlReg2T ctrlReg2;
  ctrlReg2.value = 0;
  ctrlReg2.RST = true; // Set reset flag
  i2c.writeByte(MMA865x_Reg::CTRL_REG2, ctrlReg2.value);
  delay(2); // 2ms delay guessed, not from datasheet, single test IC: 200us ok at room temp
}


boolean MMA865x::devicePresent()
{
  if(MMA8652Q_ID == i2c.readByte(MMA865x_Reg::WHO_AM_I)) return true;
  return false;
}


void MMA865x::standby()
{
  MMA865x_Reg::CtrlReg1T ctrlReg1; 
  ctrlReg1.value = i2c.readByte(MMA865x_Reg::CTRL_REG1);
  ctrlReg1.ACTIVE = false;
  i2c.writeByte(MMA865x_Reg::CTRL_REG1, ctrlReg1.value);
}


void MMA865x::active()
{
  MMA865x_Reg::CtrlReg1T ctrlReg1; 
  ctrlReg1.value = i2c.readByte(MMA865x_Reg::CTRL_REG1);
  ctrlReg1.ACTIVE = true;
  i2c.writeByte(MMA865x_Reg::CTRL_REG1, ctrlReg1.value);  
}


AccelDataT<int16_t> MMA865x::readAccelData()
{
  uint8_t rawData[6];  // x/y/z accel register data stored here
  AccelDataT<int16_t> assembledData;
  i2c.readBytes(MMA865x_Reg::OUT_X_MSB, 6, &rawData[0]);  // Read the six raw data registers into data array
  assembledData.xyz[0] = ((int16_t) rawData[0] << 8 | rawData[1]) >> 4; // needs less flash than a loop
  assembledData.xyz[1] = ((int16_t) rawData[2] << 8 | rawData[3]) >> 4;
  assembledData.xyz[2] = ((int16_t) rawData[4] << 8 | rawData[5]) >> 4;
  return assembledData;
}


// Factor needed to convert assembledData lsb units to milligrav
uint16_t MMA865x::getConversionFactorMicrograv()
{
  static const byte rezTab[] PROGMEM = {2, 4, 8};
  return (pgm_read_byte_near(rezTab + fullScaleRange) * 1000000UL) / 2048UL;
}


void MMA865x::calibrate()
{
  uint16_t ii, fcount;
  AccelDataT<int16_t> temp;
  AccelDataT<int32_t> bias = {0, 0, 0};
  AccelDataT<uint8_t> reg;
  uint8_t rawData[6];  // x/y/z FIFO accel data stored here

  // Clear all interrupts by reading the data output and F_STATUS registers
  temp = readAccelData();
  i2c.readByte(MMA865x_Reg::F_STATUS);
  
  standby();  // Must be in standby to change registers

  i2c.writeByte(MMA865x_Reg::CTRL_REG1, 0x01);      // select 100 Hz ODR
//i2c.writeByte(MMA865x_Reg::CTRL_REG1, 0x71);      // select  1.5 Hz ODR    
  fcount = 100;                                     // sample for 1 second
  i2c.writeByte(MMA865x_Reg::XYZ_DATA_CFG, 0x00);   // select 2 g full scale
  uint16_t accelsensitivity = 1024;                 // 1024 LSB/g

  active();  // Set to active to start collecting data
   

  for(ii = 0; ii < fcount; ii++)   // construct count sums for each axis
  {
    temp = readAccelData(); 
    bias += temp;
    delay(15);  // wait for a new data reading (100 Hz)
  }
 
  bias /= fcount;
  
  if(bias.z > 0L) {bias.z -= (int32_t) accelsensitivity;}  // Remove gravity from the z-axis
  else {bias.z += (int32_t) accelsensitivity;}

  // weirdness from upstream:
  reg.x = (-bias.x / 2) & 0xFF; // get average values
  reg.y = (-bias.y / 2) & 0xFF; // get average values
  reg.z = (-bias.z / 2) & 0xFF; // get average values
  
  standby();  // Must be in standby to change registers
  i2c.writeByte(MMA865x_Reg::OFF_X, reg.x); // X-axis compensation  
  i2c.writeByte(MMA865x_Reg::OFF_Y, reg.y); // Y-axis compensation  
  i2c.writeByte(MMA865x_Reg::OFF_Z, reg.z); // z-axis compensation 
  active();  // Set to active to start reading
}

