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

#include "Interval.hpp"

using namespace fpt;

Interval::Interval() : _inf(0, 0, 0), _sup(1, 1, 1)
{}

Interval::Interval(const Color& inf, const Color& sup)
  : _inf(inf), _sup(sup)
{}

Color Interval::inf() const
{
  return _inf;
}

Color Interval::sup() const
{
  return _sup;
}

Color Interval::center() const
{
  return Color((_inf.r() + _sup.r()) / 2,
	       (_inf.g() + _sup.g()) / 2,
	       (_inf.b() + _sup.b()) / 2);
}

void Interval::cut(TypeColor t, unsigned pieces, unsigned n)
{
  GLfloat infT = _inf.color(t);
  GLfloat supT = _sup.color(t);

  GLfloat intervalT = supT - infT;
  GLfloat step = intervalT / pieces;

  infT += n * step;
  supT = infT + step;

  _inf.setColor(t, infT);
  _sup.setColor(t, supT);
}
