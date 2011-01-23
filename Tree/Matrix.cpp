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

// -------------------------------------------
// Main header file
// -------------------------------------------
#include "Matrix.hpp"

// Activate namespace
using namespace std;
using namespace FreePhyloTree;

Mat4f::Mat4f(GLfloat x00, GLfloat x01, GLfloat x02, GLfloat x03,
             GLfloat x10, GLfloat x11, GLfloat x12, GLfloat x13,
             GLfloat x20, GLfloat x21, GLfloat x22, GLfloat x23,
             GLfloat x30, GLfloat x31, GLfloat x32, GLfloat x33)
{
    int i;
    m = new GLfloat*[4];
    for(i=0;i<4;i++) {
        m[i] = new GLfloat[4];
    }
    m[0][0]=x00; m[0][1]=x01; m[0][2]=x02; m[0][3]=x03;
    m[1][0]=x10; m[1][1]=x11; m[1][2]=x12; m[1][3]=x13;
    m[2][0]=x20; m[2][1]=x21; m[2][2]=x22; m[2][3]=x23;
    m[3][0]=x30; m[3][1]=x31; m[3][2]=x32; m[3][3]=x33;
}

Mat4f::Mat4f(const Mat4f& mat)
{
    int i,j;
    m = new GLfloat*[4];
    for(i=0;i<4;i++) {
        m[i] = new GLfloat[4];
        for(j=0;j<4;j++) {
            m[i][j] = mat[i][j];
        }
    }
}

Mat4f::~Mat4f()
{
    int i;
    for(i=0;i<4;i++) {
        delete[] m[i];
    }
    delete[] m;
    m=0;
}

GLfloat* Mat4f::operator[] (const int& row) const
{
    return m[row];
}

void Mat4f::operator= (const Mat4f& mat) const
{
    int i,j;
    for(i=0;i<4;i++) {
        for(j=0;j<4;j++) {
            m[i][j] = mat[i][j];
        }
    }
}

Mat4f Mat4f::operator+ (const Mat4f& mat) const
{
    return Mat4f(*this) += mat;
}

Mat4f Mat4f::operator- (const Mat4f& mat) const
{
    return Mat4f(*this) -= mat;
}

Mat4f Mat4f::operator* (const Mat4f& mat) const
{
    return Mat4f(*this) *= mat;;
}

Vec3f Mat4f::operator* (const Vec3f& vec) const
{
    Vec3f out(  m[0][0]*vec.x() + m[0][1]*vec.y() + m[0][2]*vec.z() + m[0][3],
                m[1][0]*vec.x() + m[1][1]*vec.y() + m[1][2]*vec.z() + m[1][3],
                m[2][0]*vec.x() + m[2][1]*vec.y() + m[2][2]*vec.z() + m[2][3]);
    return out;
}

Mat4f Mat4f::operator+= (const Mat4f& mat) const
{
    int i,j;
    for(i=0;i<4;i++) {
        for(j=0;j<4;j++) {
            m[i][j] += mat[i][j];
        }
    }
    return *this;
}

Mat4f Mat4f::operator-= (const Mat4f& mat) const
{
    int i,j;
    for(i=0;i<4;i++) {
        for(j=0;j<4;j++) {
            m[i][j] -= mat[i][j];
        }
    }
    return *this;
}

Mat4f Mat4f::operator*= (const Mat4f& mat) const
{
    Mat4f aux;
    int i,j,k;
    for(i=0;i<4;i++) {
        for(j=0;j<4;j++) {
            aux[i][j] = 0.f;
            for(k=0;k<4;k++) {
                aux[i][j] += m[i][k] * mat[k][j];
            }
        }
    }
    for(i=0;i<4;i++) {
        for(j=0;j<4;j++) {
            m[i][j] = aux[i][j];
        }
    }
    return *this;
}
