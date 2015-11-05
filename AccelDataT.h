// -*- mode: C++; tab-width: 2; c-basic-offset: 2; indent-tabs-mode: nil; coding: utf-8 -*-
// (c) Flummy 2015 <lab15@koffein.org> All rights reserved.

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
   AccelDataT operator+(const AccelDataT<B> &rhs)
   {
      AccelDataT<T> tmp;
      tmp.x = this->x + (T) rhs.x;
      tmp.y = this->y + (T) rhs.y;
      tmp.z = this->z + (T) rhs.z;
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

   template <typename B>
   AccelDataT operator-(const AccelDataT<B> &rhs)
   {
      AccelDataT<T> tmp;
      tmp.x = this->x - (T) rhs.x;
      tmp.y = this->y - (T) rhs.y;
      tmp.z = this->z - (T) rhs.z;
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
};
