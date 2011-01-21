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

// -------------------------------------------
// Main header file
// -------------------------------------------
#include "Camera.hpp"

// Activate namespace
using namespace std;
using namespace FreePhyloTree;

Camera::Camera(PhyloTree *tree)
    : _tree(tree)
    , _pos(0.f,0.f,-1.f)
    , _aim(0.f,0.f,0.f)
{
    _size = Vec2f(_tree->supPic().x()-_tree->infPic().x(),_tree->supPic().y()-_tree->infPic().y());
}

Camera::~Camera()
{
}

Vec3f Camera::viewDirection()
{
    Vec3f normal = _aim - _pos;
    normal /= normal.norm();
    return normal;
}
