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


// CAVE: self-assignment: http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html 

#pragma once

template <typename T>
union AccelDataT
{
   struct
   {
      T x;
      T y;
      T z;
   };

   T xyz[3];

   //AccelDataT & operator=(const AccelDataT &rhs) { return *this; }

  template <typename B>
  AccelDataT& operator=(const AccelDataT<B> &rhs)
  {
    this->x = (T) rhs.x;
    this->y = (T) rhs.y;
    this->z = (T) rhs.z;
    return *this;
  }

  AccelDataT& operator-()
  {
    this->x = -this->x;
    this->y = -this->y;
    this->z = -this->z;
    return *this;
  }

  template <typename B>
  AccelDataT operator+(const AccelDataT<B> &rhs)
  {
    AccelDataT<T> tmp;
    tmp.x = this->x + (T) rhs.x;
    tmp.y = this->y + (T) rhs.y;
    tmp.z = this->z + (T) rhs.z;
    return tmp;
  }
  
  template <typename SCALAR>
  AccelDataT operator+(const SCALAR &rhs)
  {
    AccelDataT<T> tmp;
    tmp.x = this->x + (T) rhs;
    tmp.y = this->y + (T) rhs;
    tmp.z = this->z + (T) rhs;
    return tmp;
  }


   template <typename B>
   AccelDataT& operator +=(const AccelDataT<B> &rhs)
   {
      this->x = this->x + (T) rhs.x;
      this->y = this->y + (T) rhs.y;
      this->z = this->z + (T) rhs.z;
      return *this;
   }


   template <typename SCALAR>
   AccelDataT& operator +=(const SCALAR &rhs)
   {
      this->x = this->x + (T) rhs;
      this->y = this->y + (T) rhs;
      this->z = this->z + (T) rhs;
      return *this;
   }


   template <typename B>
   AccelDataT operator-(const AccelDataT<B> &rhs)
   {
      AccelDataT<T> tmp;
      tmp.x = this->x - (T) rhs.x;
      tmp.y = this->y - (T) rhs.y;
      tmp.z = this->z - (T) rhs.z;
      return tmp;
   }


  template <typename SCALAR>
  AccelDataT operator-(const SCALAR &rhs)
  {
    AccelDataT<T> tmp;
    tmp.x = this->x - (T) rhs;
    tmp.y = this->y - (T) rhs;
    tmp.z = this->z - (T) rhs;
    return tmp;
  }


   template <typename B>
   AccelDataT& operator -=(const AccelDataT<B> &rhs)
   {
      this->x = this->x - (T) rhs.x;
      this->y = this->y - (T) rhs.y;
      this->z = this->z - (T) rhs.z;
      return *this;
   }


   template <typename SCALAR>
   AccelDataT& operator -=(const SCALAR &rhs)
   {
      this->x = this->x - (T) rhs;
      this->y = this->y - (T) rhs;
      this->z = this->z - (T) rhs;
      return *this;
   }


   template <typename B>
   AccelDataT operator/(const AccelDataT<B> &rhs)
   {
      AccelDataT<T> tmp;
      tmp.x = this->x / (T) rhs.x;
      tmp.y = this->y / (T) rhs.y;
      tmp.z = this->z / (T) rhs.z;
      return tmp;
   }

   template <typename SCALAR>
   AccelDataT operator/(const SCALAR &rhs)
   {
      AccelDataT<T> tmp;
      tmp.x = this->x / (T) rhs;
      tmp.y = this->y / (T) rhs;
      tmp.z = this->z / (T) rhs;
      return tmp;
   }


   template <typename B>
   AccelDataT& operator /=(const AccelDataT<B> &rhs)
   {
      this->x = this->x / (T) rhs.x;
      this->y = this->y / (T) rhs.y;
      this->z = this->z / (T) rhs.z;
      return *this;
   }

   template <typename SCALAR>
   AccelDataT& operator /=(const SCALAR &rhs)
   {
      this->x = this->x / (T) rhs;
      this->y = this->y / (T) rhs;
      this->z = this->z / (T) rhs;
      return *this;
   }

// xxx
   template <typename B>
   AccelDataT operator*(const AccelDataT<B> &rhs)
   {
      AccelDataT<T> tmp;
      tmp.x = this->x * (T) rhs.x;
      tmp.y = this->y * (T) rhs.y;
      tmp.z = this->z * (T) rhs.z;
      return tmp;
   }

   template <typename SCALAR>
   AccelDataT operator*(const SCALAR &rhs)
   {
      AccelDataT<T> tmp;
      tmp.x = this->x * (T) rhs;
      tmp.y = this->y * (T) rhs;
      tmp.z = this->z * (T) rhs;
      return tmp;
   }


   template <typename B>
   AccelDataT& operator *=(const AccelDataT<B> &rhs)
   {
      this->x = this->x * (T) rhs.x;
      this->y = this->y * (T) rhs.y;
      this->z = this->z * (T) rhs.z;
      return *this;
   }

   template <typename SCALAR>
   AccelDataT& operator *=(const SCALAR &rhs)
   {
      this->x = this->x * (T) rhs;
      this->y = this->y * (T) rhs;
      this->z = this->z * (T) rhs;
      return *this;
   }


};
