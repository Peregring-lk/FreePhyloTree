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

#ifndef _FPT_VECXF_
#define _FPT_VECXF_

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>

namespace fpt
{
    typedef unsigned Dim;

    class VecXf
    {
    public:
	VecXf(Dim dim, float k = 0)
	{
	    for (Dim i = 0; i < dim; ++i)
		_coords.push_back(k);

	    _dim = dim;
	}

	VecXf(const VecXf& center, float radius)
	{
	    for (Dim i = 0; i < center.dim(); ++i) {
		float r = radius * (2.0f * rand() / RAND_MAX - 1);

		_coords.push_back(center.coord(i) + r);
	    }

	    _dim = center.dim();
	}

	template<typename... Coords>
	VecXf(Coords... coords) { _build(0, coords...); }

	template<typename... Coords>
	VecXf(Dim dim, Coords... coords) { _build(dim, coords...); }

	Dim dim() const	{ return _dim; }

	Dim totalDim() const { return _coords.size(); }

	float norm() const
	{
	    if (!_upToDateNorm)
		_calcNorm();

	    return _norm;
	}

	VecXf unit() const
	{
	    if (!_upToDateNorm)
		_calcNorm();

	    if (_norm < 0.00001)
		return *this;
	    else
		return *this / _norm;
	}

	float coord(Dim dim) const
	{
	    if (dim < this->dim())
		return _coords[dim];
	    else
		return 0;
	}

	float x() const { return coord(0); }
	float y() const { return coord(1); }
	float z() const { return coord(2); }
	float w() const { return coord(3); }

	VecXf operator+ (const VecXf& vec) const
	{ return VecXf(*this) += vec; }

	VecXf operator- () const
	{
	    return *this * -1;
	}

	VecXf operator- (const VecXf& vec) const
	{ return VecXf(*this) -= vec; }

	VecXf operator+ (float k) const { return VecXf(*this) += k; }

	VecXf operator- (float k) const { return VecXf(*this) -= k; }

	VecXf operator* (float k) const { return VecXf(*this) *= k; }

	VecXf operator/ (float k) const { return VecXf(*this) /= k; }

	bool inRadius(const VecXf& vec, float radius) const
	{ return (*this - vec).norm() < radius;	}

	VecXf& operator+= (const VecXf& vec)
	{
	    for (Dim i = 0; i < _dim; ++i)
		_coords[i] += vec.coord(i);

	    _upToDateNorm = false;

	    return *this;
	}

	VecXf& operator-= (const VecXf& vec)
	{
	    for (Dim i = 0; i < _dim; ++i)
		_coords[i] -= vec.coord(i);

	    _upToDateNorm = false;

	    return *this;
	}

	VecXf& operator+= (float k)
	{ return *this += VecXf(_dim, k); }

	VecXf& operator-= (float k)
	{ return *this -= VecXf(_dim, k); }

	VecXf& operator*= (float k)
	{
	    for (Dim i = 0; i < _dim; ++i)
		_coords[i] *= k;

	    _upToDateNorm = false;

	    return *this;
	}

	VecXf& operator/= (float k)
	{
	    for (Dim i = 0; i < _dim; ++i)
		_coords[i] /= k;

	    _upToDateNorm = false;

	    return *this;
	}

	void setDim(Dim dim)
	{
	    if (dim < totalDim())
		_dim = dim;
	    else {
		_coords.push_back(0);
		++_dim;

		setDim(dim);
	    }
	}

	void resetDim() { _dim = totalDim(); }

	void clear()
	{
	    *this = VecXf((Dim)_dim);
	}

	void setCoord(Dim dim, float value)
	{
	    if (dim < this->dim())
		_coords[dim] = value;
	}

	void setX(float value)
	{
	    setCoord(0, value);
	}

	void setY(float value)
	{
	    setCoord(1, value);
	}

	void setZ(float value)
	{
	    setCoord(2, value);
	}

	void setW(float value)
	{
	    setCoord(3, value);
	}

    protected:
	std::vector<float> _coords;
	Dim _dim;

	mutable float _norm;

    private:
	mutable bool _upToDateNorm;

	void _calcNorm() const
	{
	    _norm = 0;

	    for (Dim i = 0; i < _dim; ++i)
		_norm += pow(_coords[i], 2);

	    _norm = sqrt(_norm);

	    _upToDateNorm = true;
	}

	void _build(Dim dim)
	{
	    _upToDateNorm = false;

	    if (dim == 0)
		_dim = _coords.size();
	    else
		_dim = dim;
	}

	template<typename... Coords>
	void _build(Dim dim, float value, Coords... coords)
	{
	    if (dim == 0 || _coords.size() < dim) {
		_coords.push_back(value);
		_build(dim, coords...);
	    }
	    else
		_build(dim);
	}
    };
}

// #include "VecXf.cpp"

#endif
