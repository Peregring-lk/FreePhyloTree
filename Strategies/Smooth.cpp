/*
  Copyright (C) 2011 Aarón Bueno Villares <abv150ci@gmail.com>

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

#include "Smooth.hpp"

using namespace fpt;

Smooth::Smooth() : Strategy()
{
    *this = Smooth(0.1, 1);
}

Smooth::Smooth(float gap, float smooth, float ssmooth)
    : _gap(gap), _smooth(smooth), _ssmooth(ssmooth)
{
    _originalSmooth = _smooth;
    _changed = false;
}

float Smooth::x() const
{
    return _source.x();
}

float Smooth::y() const
{
    return _source.y();
}

float Smooth::z() const
{
    return _source.z();
}

float Smooth::gap() const
{
    return _gap;
}

VecXf Smooth::source() const
{
    return _source;
}

VecXf Smooth::target() const
{
    return _target;
}

VecXf Smooth::dir() const
{
    return _dir.unit();
}

float Smooth::originalSmooth() const
{
    return _originalSmooth;
}

float Smooth::actualSmooth() const
{
    return _smooth;
}

bool Smooth::changed() const
{
    return _changed;
}

void Smooth::changeSource(const VecXf& source)
{
    _source = source;

    _dir = _target - _source;

    _smooth = _originalSmooth;
}

void Smooth::changeTarget(const VecXf& target)
{
    _target = target;

    _dir = _target - _source;

    _smooth = _originalSmooth;
}

void Smooth::changeSmooth(float smooth)
{
    _originalSmooth = smooth;
    _smooth = _originalSmooth;
}

float Smooth::changeGap(float gap)
{
    _gap = gap;
}

void Smooth::_step()
{
    _changed = false;

    if (_dir.norm() > _gap) {
	_source += _dir.unit() * _dir.norm() * _smooth;

	_dir = _target - _source;

	_smooth *= _ssmooth;

	_changed = true;
    }
}
