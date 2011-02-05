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

#include "Color.hpp"

using namespace FreePhyloTree;

Color::Color()
{
  _color[R] = _color[G] = _color[B] = 1;
}

Color::Color(GLfloat r, GLfloat g, GLfloat b)
{
  _color[R] = r;
  _color[G] = g;
  _color[B] = b;
}

Color::Color(const Color& color)
{
  _color[R] = color.r();
  _color[G] = color.g();
  _color[B] = color.b();
}

GLfloat Color::r() const
{
  return _color[R];
}

GLfloat Color::g() const
{
  return _color[G];
}

GLfloat Color::b() const
{
  return _color[B];
}

GLfloat Color::color(TypeColor t) const
{
  return _color[t];
}

void Color::setColor(GLfloat r, GLfloat g, GLfloat b)
{
  _color[R] = r;
  _color[G] = g;
  _color[B] = b;
}

void Color::setColor(TypeColor t, GLfloat value)
{
  _color[t] = value;
}
