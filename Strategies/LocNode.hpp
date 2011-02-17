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

#ifndef _FPT_LOC_NODE_
#define _FPT_LOC_NODE_

#include "Vec3f.hpp"
#include "../Tree/Node.hpp"

namespace fpt
{
    class LocTree;

    class LocNode : virtual public Node
    {
    public:
	LocNode(const Name& name);

	GLfloat x() const;
	GLfloat y() const;

	const Vec3f& loc() const;

	bool crib() const;
	bool hide() const;

	void setLoc(const Vec3f& loc);
	void move(const Vec3f& delta);

	void setCrib(bool crib);

    private:
	Vec3f _loc;
	bool _crib;
    };
}

#endif
