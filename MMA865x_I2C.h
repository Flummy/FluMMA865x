// -*- mode: C++; tab-width: 2; c-basic-offset: 2; indent-tabs-mode: nil; coding: utf-8 -*-
// (c) Flummy 2015 <lab15@koffein.org> All rights reserved.

#pragma once

#include <Arduino.h>

class MMA865x_I2C
{

public:
  static void    writeByte(const uint8_t subAddress, const uint8_t data);
  static uint8_t readByte(const uint8_t subAddress);
  static void    readBytes(const uint8_t subAddress, const uint8_t count, uint8_t * const dest);
};
