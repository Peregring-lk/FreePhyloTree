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

Camera::Camera(PhyloTree *tree, float aspectRatio)
    : _tree(tree)
    , _aspectRatio(aspectRatio)
    , _pos(0.f,0.f,-1.f)
    , _aim(0.f,0.f,0.f)
{
    resize();
}

Camera::~Camera()
{
}

void Camera::setAspectRatio(float aspectRatio)
{
    _aspectRatio = aspectRatio;
    resize();
}

float Camera::aspectRatio()
{
    return _aspectRatio;
}

Vec2f Camera::size()
{
    return _size;
}

void Camera::setPosition(Vec3f pos)
{
    _pos = pos;
}

Vec3f Camera::position()
{
    return _pos;
}

void Camera::setAimingPoint(Vec3f aim)
{
    _aim = aim;
}

Vec3f Camera::aimingPoint()
{
    return _aim;
}

Vec3f Camera::viewDirection()
{
    Vec3f normal = _aim - _pos;
    normal /= normal.norm();
    return normal;
}

void Camera::resize()
{
    float radius = _tree->supPic().x()-_tree->infPic().x();
    if(_tree->supPic().y()-_tree->infPic().y() > radius)
        radius = _tree->supPic().y()-_tree->infPic().y();
    if(_aspectRatio < 1.f)
        _size = Vec2f(radius, radius*_aspectRatio);
    else
        _size = Vec2f(radius/_aspectRatio, radius);
}
