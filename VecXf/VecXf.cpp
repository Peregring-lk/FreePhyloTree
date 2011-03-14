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

#include <cstdlib>
#include <cmath>

#include "VecXf.hpp"

using namespace fpt;

VecXf::VecXf(const VecXf& center, float radius)
{
    float x = radius * (2.0f * rand() / RAND_MAX - 1);
    float y = radius * (2.0f * rand() / RAND_MAX - 1);
    float z = radius * (2.0f * rand() / RAND_MAX - 1);

    *this = VecXf(center.x() + x,
		  center.y() + y,
		  center.z() + z);
}

VecXf::VecXf(float x, float y, float z) : _x(x), _y(y), _z(z)
{
    _upToDateNorm = false;
}

float VecXf::norm() const
{
    if (!_upToDateNorm)
	_calcNorm();

    return _norm;
}

VecXf VecXf::unit() const
{
    if (!_upToDateNorm)
	_calcNorm();

    if (_norm < 0.00001)
	return *this;
    else
	return *this / _norm;
}

float VecXf::coord(Dim dim) const
{
    switch(dim)
    {
    case 0:
	return _x;
    case 1:
	return _y;
    case 2:
	return _z;
    default:
	return 0;
    }
}

float VecXf::x() const
{
    return _x;
}

float VecXf::y() const
{
    return _y;
}

float VecXf::z() const
{
    return _z;
}

VecXf VecXf::operator+ (const VecXf& vec) const
{
    return VecXf(*this) += vec;
}

VecXf VecXf::operator- () const
{
    return *this * -1;
}

VecXf VecXf::operator- (const VecXf& vec) const
{
    return VecXf(*this) -= vec;
}

VecXf VecXf::operator+ (float k) const
{
    return VecXf(*this) += k;
}

VecXf VecXf::operator- (float k) const
{
    return VecXf(*this) -= k;
}

VecXf VecXf::operator* (float k) const
{
    return VecXf(*this) *= k;
}

VecXf VecXf::operator/ (float k) const
{
    return VecXf(*this) /= k;
}

bool VecXf::inRadius(const VecXf& vec, float radius) const
{
    return (*this - vec).norm() < radius;
}

VecXf& VecXf::operator+= (const VecXf& vec)
{
    _x += vec.x();
    _y += vec.y();
    _z += vec.z();

    _upToDateNorm = false;

    return *this;
}

VecXf& VecXf::operator-= (const VecXf& vec)
{
    _x -= vec.x();
    _y -= vec.y();
    _z -= vec.z();

    _upToDateNorm = false;

    return *this;
}

VecXf& VecXf::operator+= (float k)
{
    _x += k;
    _y += k;
    _z += k;

    _upToDateNorm = false;

    return *this;
}

VecXf& VecXf::operator-= (float k)
{
    _x -= k;
    _y -= k;
    _z -= k;

    _upToDateNorm = false;

    return *this;
}

VecXf& VecXf::operator*= (float k)
{
    _x *= k;
    _y *= k;
    _z *= k;

    _upToDateNorm = false;

    return *this;
}

VecXf& VecXf::operator/= (float k)
{
    _x /= k;
    _y /= k;
    _z /= k;

    _upToDateNorm = false;

    return *this;
}

void VecXf::clear()
{
    *this = VecXf();

    _upToDateNorm = false;
}

void VecXf::setX(float value)
{
    _x = value;

    _upToDateNorm = false;
}

void VecXf::setY(float value)
{
    _y = value;

    _upToDateNorm = false;
}

void VecXf::setZ(float value)
{
    _z = value;

    _upToDateNorm = false;
}

void VecXf::setCoord(Dim dim, float value)
{
    switch(dim)
    {
    case 0:
	setX(value);
	break;
    case 1:
	setY(value);
	break;
    case 2:
	setZ(value);
    default:
	break;
    }
}

void VecXf::_calcNorm() const
{
    _norm = sqrt(pow(_x, 2) + pow(_y, 2) + pow(_z, 2));

    _upToDateNorm = true;
}
