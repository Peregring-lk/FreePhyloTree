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

using namespace fpt;

VecXf::VecXf(Dim dim)
{
    VecXf(dim, 0);
}

VecXf::VecXf(Dim dim, float k)
{
    for (Dim i = 0; i < dim; ++i)
	_coords.push_back(k);

    _dim = dim;
}

VecXf::VecXf(const VecXf& center, float radius)
{
    for (Dim i = 0; i < center.dim(); ++i) {
	float r = radius * (2 * rand() / RAND_MAX - 1);

	_coords.push_back(center.coord(i) + r);
    }

    _dim = center.dim();
}

template<typename... Coords>
VecXf::VecXf(Dim dim, Coords... coords)
{
    _build(dim, coords...);
}

template<typename... Coords>
VecXf::VecXf(Coords... coords)
{
    _build(0, coords...);
}

Dim VecXf::dim() const
{
    return _dim;
}

Dim VecXf::totalDim() const
{
    return _coords.size();
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
    if (dim < this->dim())
	return _coords[dim];
    else
	return 0;
}

float VecXf::x() const
{
    return coord(0);
}

float VecXf::y() const
{
    return coord(1);
}

float VecXf::z() const
{
    return coord(2);
}

float VecXf::w() const
{
    return coord(3);
}

VecXf VecXf::operator+ (const VecXf& vec) const
{
    return VecXf(*this) += vec;
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
    for (Dim i = 0; i < _dim; ++i)
	_coords[i] += vec.coord(i);

    _upToDateNorm = false;

    return *this;
}

VecXf& VecXf::operator-= (const VecXf& vec)
{
    for (Dim i = 0; i < _dim; ++i)
	_coords[i] -= vec.coord(i);

    _upToDateNorm = false;

    return *this;
}

VecXf& VecXf::operator+= (float k)
{
    return *this += VecXf(_dim, k);
}

VecXf& VecXf::operator-= (float k)
{
    return *this -= VecXf(_dim, k);
}

VecXf& VecXf::operator*= (float k)
{
    for (Dim i = 0; i < _dim; ++i)
	_coords[i] *= k;

    _upToDateNorm = false;

    return *this;
}

VecXf& VecXf::operator/= (float k)
{
    for (Dim i = 0; i < _dim; ++i)
	_coords[i] /= k;

    _upToDateNorm = false;

    return *this;
}

void VecXf::setDim(Dim dim)
{
    if (dim < totalDim())
	_dim = dim;
    else {
	_coords.push_back(0);
	++_dim;

	setDim(dim);
    }
}

void VecXf::resetDim()
{
    _dim = totalDim();
}

void VecXf::setCoord(Dim dim, float value)
{
    if (dim < this->dim())
	_coords[dim] = value;
}

void VecXf::_calcNorm() const
{
    _norm = 0;

    for (Dim i = 0; i < _dim; ++i)
	_norm += pow(_coords[i], 2);

    _norm = sqrt(_norm);

    _upToDateNorm = true;
}

void VecXf::_build(Dim dim)
{
    _upToDateNorm = false;

    if (dim == 0)
	_dim = _coords.size();
    else
	_dim = dim;
}

template<typename... Coords>
void VecXf::_build(Dim dim, float value, Coords... coords)
{
    if (dim == 0 || _coords.size() < dim) {
	_coords.push_back(value);
	_build(dim, coords...);
    }
    else
	_build(dim);
}
