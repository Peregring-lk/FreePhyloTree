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
#include "Vec2f.hpp"

using namespace FreePhyloTree;

Vec2f::Vec2f()
{
    _x = _y = 0;
    _norm = 0;

    _upToDateNorm = true;
}

Vec2f::Vec2f(GLfloat x, GLfloat y) : _x(x), _y(y)
{
    _upToDateNorm = false;
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
    if (!_upToDateNorm)
	_calcNorm();

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

    _upToDateNorm = false;
}

Vec2f& Vec2f::operator+= (const Vec2f& vec)
{
    _x += vec.x();
    _y += vec.y();

    _upToDateNorm = false;

    return *this;
}

Vec2f& Vec2f::operator-= (const Vec2f& vec)
{
    _x -= vec.x();
    _y -= vec.y();

    _upToDateNorm = false;

    return *this;
}

Vec2f& Vec2f::operator*= (GLfloat k)
{
    _x *= k;
    _y *= k;

    _upToDateNorm = false;

    return *this;
}

Vec2f& Vec2f::operator/= (GLfloat k)
{
    _x /= k;
    _y /= k;

    _upToDateNorm = false;

    return *this;
}

void Vec2f::_calcNorm() const
{
    _norm = sqrt(pow(_x, 2) + pow(_y, 2));

    _upToDateNorm = true;
}
