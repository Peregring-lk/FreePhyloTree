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

#include "CubeColor.hpp"

using namespace fpt;

CubeColor::CubeColor() : _sup(1.0f, 1.0f, 1.0f)
{}

CubeColor::CubeColor(float r1, float g1, float b1,
		     float r2, float g2, float b2)
    : _inf(r1, g1, b1), _sup(r2, g2, b2)
{}

CubeColor::CubeColor(const VecColor& inf, const VecColor& sup)
    : _inf(inf), _sup(sup)
{}

const VecColor& CubeColor::inf() const
{
  return _inf;
}

const VecColor& CubeColor::sup() const
{
  return _sup;
}

VecColor CubeColor::center() const
{
  return VecColor((_inf.x() + _sup.x()) / 2,
		  (_inf.y() + _sup.y()) / 2,
		  (_inf.z() + _sup.z()) / 2);
}

void CubeColor::cut(TypeC color, unsigned pieces, unsigned n)
{
  float infT = _inf.coord(color);
  float supT = _sup.coord(color);

  float intervalT = supT - infT;
  float step = intervalT / pieces;

  infT += n * step;
  supT = infT + step;

  _inf.setCoord(color, infT);
  _sup.setCoord(color, supT);
}
