// -*- mode: C++; tab-width: 2; c-basic-offset: 2; indent-tabs-mode: nil; coding: utf-8 -*-
//    MMA865x Accelerometer Driver Library for Arduino, Version 1, 2015-11-12
//    http://koffein.org/MMA865x/
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
