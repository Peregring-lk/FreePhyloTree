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

#ifndef _FPT_VIEWING_
#define _FPT_VIEWING_

#include "../PhyloTree.hpp"

#include <GL/gl.h>

namespace fpt
{
    class Viewing : public Strategy
    {
    public:
	Viewing(PhyloTree *tree, GLsizei width, GLsizei height,
		float maxRatio = 10.0f / 12);

	void init();
	void step();

	void sizeViewport(GLsizei width, GLsizei height);

    private:
	PhyloTree *_tree;

	GLsizei _width;
	GLsizei _height;
	float _maxRatio;
	float _border;

	void _calcOrtho();
    };
}

#endif
