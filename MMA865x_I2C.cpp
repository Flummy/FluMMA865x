// -*- mode: C++; tab-width: 2; c-basic-offset: 2; indent-tabs-mode: nil; coding: utf-8 -*-
// (c) Flummy 2015 <lab15@koffein.org> All rights reserved.

#include <Wire.h>
#include "MMA865x_I2C.h"


//#define MMA8652_ADDRESS 0x1C  // Sparkfun breakout board jumper SA0 set
#define MMA8652_ADDRESS   0x1D  // Sparkfun breakout board jumper SA0 open (default)


void MMA865x_I2C::writeByte(const uint8_t subAddress, const uint8_t data)
{
	Wire.beginTransmission(MMA8652_ADDRESS);  // Initialize the Tx buffer
	Wire.write(subAddress);           // Put slave register address in Tx buffer
	Wire.write(data);                 // Put data in Tx buffer
	Wire.endTransmission();           // Send the Tx buffer
}


uint8_t MMA865x_I2C::readByte(const uint8_t subAddress)
{
	Wire.beginTransmission(MMA8652_ADDRESS); // Initialize the Tx buffer
	Wire.write(subAddress);	                 // Put slave register address in Tx buffer
	Wire.endTransmission(false);             // Send the Tx buffer, but send a restart to keep connection alive
	Wire.requestFrom((uint8_t)MMA8652_ADDRESS, (uint8_t)1);  // Read one uint8_t from slave register address 
  return Wire.read();
}


void MMA865x_I2C::readBytes(const uint8_t subAddress, const uint8_t count, uint8_t * const dest)
{  
  uint8_t i = 0;
	Wire.beginTransmission(MMA8652_ADDRESS);   // Initialize the Tx buffer
	Wire.write(subAddress);            // Put slave register address in Tx buffer
	Wire.endTransmission(false);       // Send the Tx buffer, but send a restart to keep connection alive
  Wire.requestFrom((uint8_t)MMA8652_ADDRESS, count);  // Read bytes from slave register address 
	while (Wire.available()) dest[i++] = Wire.read();
}
