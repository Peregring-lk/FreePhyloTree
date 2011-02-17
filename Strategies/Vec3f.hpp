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

#ifndef _FPT_VECTOR_
#define _FPT_VECTOR_

#include <GL/gl.h>

namespace fpt
{
    class Vec3f
    {
    public:
	Vec3f();
	Vec3f(GLfloat x, GLfloat y);
	Vec3f(GLfloat x, GLfloat y, GLfloat z);

	GLfloat x() const;
	GLfloat y() const;
	GLfloat z() const;

	GLfloat norm() const;
	Vec3f unit() const;

	Vec3f operator+ (const Vec3f& vec) const;
	Vec3f operator- (const Vec3f& vec) const;
	Vec3f operator* (GLfloat k) const;
	Vec3f operator/ (GLfloat k) const;

	bool inRadius(Vec3f vec, GLfloat radius) const;

	void setAlloc(GLfloat x, GLfloat y, GLfloat z = 0);
	void setX(GLfloat x);
	void setY(GLfloat y);
	void setZ(GLfloat z);

	Vec3f& operator+= (const Vec3f& vec);
	Vec3f& operator-= (const Vec3f& vec);
	Vec3f& operator*= (GLfloat k);
	Vec3f& operator/= (GLfloat k);

    private:
	GLfloat _x;
	GLfloat _y;
	GLfloat _z;

	mutable GLfloat _norm;
	mutable bool _upToDateNorm;

	void _calcNorm() const;
    };
}

#endif
