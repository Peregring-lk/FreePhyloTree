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

#include <iostream>
#include "Viewing.hpp"

using namespace fpt;

Viewing::Viewing(PhyloTree *tree, GLsizei width, GLsizei height,
		 float maxRatio)
    : _tree(tree), _width(width), _height(height), _maxRatio(maxRatio)
{}

void Viewing::init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    VecXf center = _tree->locRoot();
    VecXf distance(_width * 0.5 * _maxRatio, _height * 0.5 * _maxRatio);

    VecXf inf = center - distance;
    VecXf sup = center + distance;

    glOrtho(inf.x(), sup.x(), inf.y(), sup.y(), -1, 1);
    glViewport(0, 0, _width, _height);

    glMatrixMode(GL_MODELVIEW);
}

void Viewing::step()
{
    init();
}

void Viewing::sizeViewport(GLsizei width, GLsizei height)
{
    _width = width;
    _height = height;
}

