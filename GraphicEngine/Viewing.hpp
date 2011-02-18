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
    class Viewing
    {
    public:
	Viewing(PhyloTree *tree, GLsizei width, GLsizei height);

	Vec3f aimCamera() const;
	Vec3f locCamera() const;

	Vec3f upVectorCamera() const;
	Vec3f viewingDirection() const;

	void initSignal();
	void nextStep();

	void setAimCamera(Vec3f loc);
	void moveCamera(Vec3f desp);

	void resizeViewport(GLsizei width, GLsizei height);

    private:
	PhyloTree *_tree;

	Vec3f _aim;
	Vec3f _loc;
	Vec3f _up;

	GLsizei _width;
	GLsizei _height;
    };
}

#endif
