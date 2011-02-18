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

#include "Viewing.hpp"

#include <GL/glu.h>

using namespace fpt;

Viewing::Viewing(PhyloTree *tree, GLsizei width, GLsizei height)
    : _tree(tree), _loc(0, 0, -1), _up(0, 1, 0),
      _width(width), _height(height)
{}

Vec3f Viewing::aimCamera() const
{
    return _aim;
}

Vec3f Viewing::locCamera() const
{
    return _loc;
}

Vec3f Viewing::upVectorCamera() const
{
    return _up;
}

void Viewing::initSignal()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    _aim = dynamic_cast<LocNode*>(_tree->root())->loc();

    /*
     *  Cámara
     */
    gluLookAt(_loc.x(), _loc.y(), _loc.z(),
	      _aim.x(), _aim.y(), _aim.z(),
	      _up.x(), _up.y(), _up.z());

    /*
     *  Perspectiva ortogonal
     */
    Vec3f distance(_width / 2.0f, _height / 2.0f);

    Vec3f inf = _aim - distance;
    Vec3f sup = _aim + distance;

    glOrtho(inf.x(), sup.x(), inf.y(), sup.y(), -1, 1);

    /*
     * Viewport
     */
    glViewport(0, 0, _width, _height);

    glMatrixMode(GL_MODELVIEW);
}

void Viewing::nextStep()
{
    initSignal();
}

void Viewing::setAimCamera(Vec3f loc)
{
    _aim = loc;
}

void Viewing::moveCamera(Vec3f desp)
{
    _loc += desp;
}

void Viewing::resizeViewport(GLsizei width, GLsizei height)
{
    _width = width;
    _height = height;
}

