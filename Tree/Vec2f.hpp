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

#ifndef _VEC_
#define _VEC_

#include <GL/gl.h>

namespace FreePhyloTree
{
  class Vec2f
  {
  public:
    Vec2f();
    Vec2f(GLfloat x, GLfloat y);

    GLfloat x() const;
    GLfloat y() const;

    GLfloat norm() const;
    Vec2f unit() const;

    Vec2f operator+ (const Vec2f& vec) const;
    Vec2f operator- (const Vec2f& vec) const;
    Vec2f operator* (GLfloat k) const;
    Vec2f operator/ (GLfloat k) const;

    bool inRadius(Vec2f vec, GLfloat radius) const;

    void setAlloc(GLfloat x, GLfloat y);
    void setX(GLfloat x);
    void setY(GLfloat y);

    Vec2f operator+= (const Vec2f& vec);
    Vec2f operator-= (const Vec2f& vec);
    Vec2f operator*= (GLfloat k);
    Vec2f operator/= (GLfloat k);

  private:
    GLfloat _x;
    GLfloat _y;

    GLfloat _norm;

    void _calcNorm();
  };
}

#endif
