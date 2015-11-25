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

#pragma once

class Demo
{
public:
  static void work();               // called by main loop(), prints any occured interrupt, checks if accel data is ready
  static void accelDataHandler();   // gets and prints accel data
  static void transientHandler();   // handles transient event = transient IRQ
  static void motionHandler();      // handles free fall / motion event
  static void orientationHandler(); // handles orientation change event
  static void pulseHandler();         // handles pulse/tap event
};

