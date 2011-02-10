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
    , _up(0.f,1.f,0.f)
{
/*
    resize();
    setPosition(Vec3f(0.f,0.f,_size.z()));
*/
}

Camera::~Camera()
{
}

void Camera::initSignal()
{
    resize();
    setPosition(Vec3f(0.f,0.f,_size.z()));
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
    reCalcUp();
    setupModelViewProjMatrix();
}

void Camera::setAimingPoint(Vec3f aim)
{
    _aim = aim;
    reCalcUp();
    setupModelViewProjMatrix();
}

Vec3f Camera::position() const
{
    return _pos;
}

Vec3f Camera::aimingPoint() const
{
    return _aim;
}

Vec3f Camera::up() const
{
    return _up;
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
    setupModelViewProjMatrix();
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
    Mat4f Rot(   cs,  0.f,   sn,  0.f,
                0.f,  1.f,  0.f,  0.f,
                -sn,  0.f,   cs,  0.f,
                0.f,  0.f,  0.f,  1.f);
    AimToCam2 = Rot*AimToCam;
    // Apply new pitch
    cs = cos(pitch);
    sn = sin(pitch);
    Rot=Mat4f(  1.f,  0.f,  0.f,  0.f,
                0.f,   cs,  -sn,  0.f,
                0.f,   sn,   cs,  0.f,
                0.f,  0.f,  0.f,  1.f);
    AimToCam = Rot*AimToCam2;
    // Apply accumulated heading
    cs = cos(OldHead+head);
    sn = sin(OldHead+head);
    Rot=Mat4f(   cs,  0.f,   sn,  0.f,
                0.f,  1.f,  0.f,  0.f,
                -sn,  0.f,   cs,  0.f,
                0.f,  0.f,  0.f,  1.f);
    AimToCam2 = Rot*AimToCam;
    // Set the new position of the camera
    AimToCam = AimToCam2 * Distance;
    setPosition(_aim+AimToCam);
}

Mat4f Camera::modelViewProjMatrix() const
{
    return _modelViewProjMatrix;
}

void Camera::setupModelViewProjMatrix(bool OpenGL)
{
    if(OpenGL)
        _modelViewProjMatrix = getModelViewProjMatrix();
    else
        _modelViewProjMatrix = recalcModelViewProjMatrix();
}

Mat4f Camera::getModelViewProjMatrix() const
{
    GLfloat	proj[16], modv[16];
    Mat4f modelViewMatrix, ProjectionMatrix;
    /** ModelViewProjection matrix is the matrix that transform real coordinates
     * into camera space coordinates. We use orthodromic projection, so the apllied
     * matrix is oprthogonal, and deph is linear. \n
     * To learn more, see glOrtho and gluLookAt of OpenGL documentation.
     */
    // Get the info from OpenGL
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();     // Save actual matrix
    glLoadIdentity();
    glOrtho(-_size.x(),_size.x(),-_size.y(),_size.y(),0.f,2.f*_size.z());
    glGetFloatv( GL_PROJECTION_MATRIX, proj );
    glPopMatrix();      // Restore matrix
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();     // Save actual matrix
    glLoadIdentity();
    gluLookAt(  _pos.x(), _pos.y(), _pos.z(),
                _aim.x(), _aim.y(), _aim.z(),
                 _up.x(),  _up.y(),  _up.z());
    glGetFloatv( GL_MODELVIEW_MATRIX, modv );
    glPopMatrix();      // Restore matrix
    // Process info
    modelViewMatrix = Mat4f( modv[ 0], modv[ 1], modv[ 2], modv[ 3],
                             modv[ 4], modv[ 5], modv[ 6], modv[ 7],
                             modv[ 8], modv[ 9], modv[10], modv[11],
                             modv[12], modv[13], modv[14], modv[15]);
    ProjectionMatrix = Mat4f( proj[ 0], proj[ 1], proj[ 2], proj[ 3],
                              proj[ 4], proj[ 5], proj[ 6], proj[ 7],
                              proj[ 8], proj[ 9], proj[10], proj[11],
                              proj[12], proj[13], proj[14], proj[15]);
    return modelViewMatrix*ProjectionMatrix;
}

Mat4f Camera::recalcModelViewProjMatrix() const
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
    Vec3f s = f.cross(_up);
    Vec3f u = s.cross(f);

    Mat4f view(  s.x(),  s.y(),  s.z(), 0.f,
                 u.x(),  u.y(),  u.z(), 0.f,
                -f.x(), -f.y(), -f.z(), 0.f,
                   0.f,    0.f,    0.f, 1.f);

    Mat4f viewProj = view*proj;
    Vec3f eye = viewProj*_aim;

    Mat4f model(  1.f,  0.f,  0.f,  -eye.x(),
                  0.f,  1.f,  0.f,  -eye.y(),
                  0.f,  0.f,  1.f,  -eye.z(),
                  0.f,  0.f,  0.f,       1.f);

    return model*viewProj;
}

void Camera::reCalcUp()
{
    // Gets normal to view direction into XZ plane
    Vec3f viewDir = viewDirection();
    Vec3f nViewDir(viewDir.z(), 0.f, -viewDir.x());
    if(nViewDir.norm() < 0.001f) {
        _up = Vec3f(1.f, 0.f, 0.f);
    }
    else {
        _up = viewDir.cross(nViewDir);
        if(_up.y() < 0.f)
            _up *= -1.f;

    }
    _up /= _up.norm();
}
