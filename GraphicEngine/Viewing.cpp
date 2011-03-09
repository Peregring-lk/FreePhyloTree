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
{
    _border = 30;
}

void Viewing::init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    _calcOrtho();
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

void Viewing::_calcOrtho()
{
    VecXf quad = _tree->convexQuad();

    /*
     *
     *  Igualamos ratio de Viewport con quad.
     *
     */
    float vwRatio = _width / _height;
    float quadRatio = quad.coord(2) / quad.coord(3);

    if (quadRatio < vwRatio)
	quad.setCoord(2, vwRatio * quad.coord(3));
    else
	quad.setCoord(3, quad.coord(2) / vwRatio);

    /*
     *
     *  Calculamos el cuadro de proyección.
     *
     */
    VecXf center(quad.x(), quad.y());
    VecXf distance(quad.coord(2), quad.coord(3));

    /*
     *
     *  Reducimos el ratio coordenadas / píxel.
     *
     */
    if (2 * distance.x() / _width < _maxRatio) {
	distance.setX(_width * _maxRatio * 0.5);
	distance.setY(distance.x() / vwRatio);
    }

    distance -= _border;

    VecXf inf = center - distance;
    VecXf sup = center + distance;

    glOrtho(inf.x(), sup.x(), inf.y(), sup.y(), -1, 1);

}
