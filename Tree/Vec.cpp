/*
  Copyright (C) 2010 Aarón Bueno Villares <abv150ci@gmail.com>

  This file is part of FreePhyloTree.

  FreePhyloTree is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  FreePhyloTree is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with FreePhyloTree.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <cmath>
#include "Vec.hpp"

using namespace FreePhyloTree;

Vec2f::Vec2f()
{
  _x = _y = 0;
  _norm = 0;
}

Vec2f::Vec2f(GLfloat x, GLfloat y) : _x(x), _y(y)
{
  _calcNorm();
}

GLfloat Vec2f::x() const
{
  return _x;
}

GLfloat Vec2f::y() const
{
  return _y;
}

GLfloat Vec2f::norm() const
{
  return _norm;
}

Vec2f Vec2f::unit() const
{
  return Vec2f(_x / _norm, _y / _norm);
}

Vec2f Vec2f::operator+ (const Vec2f& vec) const
{
  return Vec2f(*this) += vec;
}

Vec2f Vec2f::operator- (const Vec2f& vec) const
{
  return Vec2f(*this) -= vec;
}

Vec2f Vec2f::operator* (GLfloat k) const
{
  return Vec2f(*this) *= k;
}

Vec2f Vec2f::operator/ (GLfloat k) const
{
  return Vec2f(*this) /= k;
}

bool Vec2f::inRadius(Vec2f vec, GLfloat radius) const
{
  return (*this - vec).norm() < radius;
}

void Vec2f::setAlloc(GLfloat x, GLfloat y)
{
  _x = x;
  _y = y;

  _calcNorm();
}

Vec2f Vec2f::operator+= (const Vec2f& vec)
{
  _x += vec.x();
  _y += vec.y();

  _calcNorm();

  return *this;
}

Vec2f Vec2f::operator-= (const Vec2f& vec)
{
  _x -= vec.x();
  _y -= vec.y();

  _calcNorm();

  return *this;
}

Vec2f Vec2f::operator*= (GLfloat k)
{
  _x *= k;
  _y *= k;

  if (k != 0)
    _norm *= k;
  else
    _norm = 0;

  return *this;
}

Vec2f Vec2f::operator/= (GLfloat k)
{
  _x /= k;
  _y /= k;

  _norm /= k;

  return *this;
}

void Vec2f::_calcNorm()
{
  _norm = sqrt(pow(_x, 2) + pow(_y, 2));
}

Vec3f::Vec3f()
{
  _x = _y = _z = 0;
  _norm = 0;
}

Vec3f::Vec3f(GLfloat x, GLfloat y, GLfloat z)
  : _x(x), _y(y), _z(z)
{
  _calcNorm();
}

GLfloat Vec3f::x() const
{
  return _x;
}

GLfloat Vec3f::y() const
{
  return _y;
}

GLfloat Vec3f::z() const
{
  return _z;
}

GLfloat Vec3f::norm() const
{
  return _norm;
}

Vec3f Vec3f::unit() const
{
  return Vec3f(_x / _norm, _y / _norm, _z / _norm);
}

Vec3f Vec3f::operator+ (const Vec3f& vec) const
{
  return Vec3f(*this) += vec;
}

Vec3f Vec3f::operator- (const Vec3f& vec) const
{
  return Vec3f(*this) -= vec;
}

Vec3f Vec3f::operator* (GLfloat k) const
{
  return Vec3f(*this) *= k;
}

Vec3f Vec3f::operator/ (GLfloat k) const
{
  return Vec3f(*this) /= k;
}

bool Vec3f::inRadius(Vec3f vec, GLfloat radius) const
{
  return (*this - vec).norm() < radius;
}

void Vec3f::setAlloc(GLfloat x, GLfloat y, GLfloat z)
{
  _x = x;
  _y = y;
  _z = z;

  _calcNorm();
}

Vec3f Vec3f::operator+= (const Vec3f& vec)
{
  _x += vec.x();
  _y += vec.y();
  _z += vec.z();

  _calcNorm();

  return *this;
}

Vec3f Vec3f::operator-= (const Vec3f& vec)
{
  _x -= vec.x();
  _y -= vec.y();
  _z -= vec.z();

  _calcNorm();

  return *this;
}

Vec3f Vec3f::operator*= (GLfloat k)
{
  _x *= k;
  _y *= k;
  _z *= k;

  if (k != 0)
    _norm *= k;
  else
    _norm = 0;

  return *this;
}

Vec3f Vec3f::operator/= (GLfloat k)
{
  _x /= k;
  _y /= k;
  _z /= k;

  _norm /= k;

  return *this;
}

void Vec3f::_calcNorm()
{
  _norm = sqrt(pow(_x, 2) + pow(_y, 2) + pow(_z, 2));
}
