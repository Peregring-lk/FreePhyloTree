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
    , _pos(0.f,0.f,1.f)
    , _aim(0.f,0.f,0.f)
{
    resize();
    setPosition(Vec3f(0.f,0.f,_size.z()));
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

Vec3f Camera::size()
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
    radius /= 2.f;
    if(_aspectRatio < 1.f)
        _size = Vec3f(radius, radius*_aspectRatio, radius);
    else
        _size = Vec3f(radius/_aspectRatio, radius, radius);
}

void Camera::rotate(float head, float pitch)
{
    Vec3f AimToCam2;
    Vec3f AimToCam = _pos - _aim;
    float Distance = AimToCam.norm();
    AimToCam /= Distance;
    // Reverse heading rotation
    float OldHead = atan2(AimToCam.x(), AimToCam.z());
    float cs = cos(-OldHead);
    float sn = sin(-OldHead);
    AimToCam2 = Vec3f(cs*AimToCam.x()-sn*AimToCam.z(), AimToCam.y(), sn*AimToCam.x()+cs*AimToCam.z());
    // Apply new pitch
    cs = cos(pitch);
    sn = sin(pitch);
    AimToCam = Vec3f(AimToCam2.x(), cs*AimToCam.y()-sn*AimToCam2.z(), sn*AimToCam.y()+cs*AimToCam2.z());
    // Apply accumulated heading
    cs = cos(OldHead+head);
    sn = sin(OldHead+head);
    AimToCam2 = Vec3f(cs*AimToCam.x()-sn*AimToCam.z(), AimToCam.y(), sn*AimToCam.x()+cs*AimToCam.z());
    // Set the new position of the camera
    AimToCam = AimToCam2 * Distance;
    setPosition(_aim+AimToCam);
}

Mat4f Camera::viewProjMatrix() const
{
    /** ModelViewProjection matrix is the matrix that transform real coordinates
     * into camera space coordinates. We use orthodromic projection, so the apllied
     * matrix is oprthogonal, and deph is linear. \n
     * To learn more, see glOrtho and gluLookAt of OpenGL documentation.
     */
    Mat4f proj( 1.f/(_size.x()),             0.f,             0.f,             0.f,
                            0.f,   1.f/_size.y(),             0.f,             0.f,
                            0.f,             0.f,  -1.f/_size.z(),            -1.f,
                            0.f,             0.f,             0.f,             1.f);
    Vec3f f = _aim - _pos;
    f /= f.norm();
    Vec3f s = Vec3f(-f.z(), 0.f, f.x());
    Vec3f u = Vec3f(-f.x()*f.y(), f.x()*f.x() + f.z()*f.z(), -f.y()*f.z());

    Mat4f view( s.x(), s.y(), s.z(), 0.f,
                u.x(), u.y(), u.z(), 0.f,
                f.x(), f.y(), f.z(), 0.f,
                  0.f,   0.f,   0.f, 1.f);
    return view*proj;
}
