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

#ifndef _COLOR_
#define _COLOR_

#include <GL/gl.h>

namespace fpt
{
    enum TypeColor { R, G, B };

    class Color
    {
    public:
	Color();
	Color(GLfloat r, GLfloat g, GLfloat b);
	Color(const Color& color);

	GLfloat r() const;
	GLfloat g() const;
	GLfloat b() const;

	GLfloat color(TypeColor t) const;

	void setColor(GLfloat r, GLfloat g, GLfloat b);
	void setColor(TypeColor t, GLfloat value);

    private:
	GLfloat _color[3];
    };
}

#endif
