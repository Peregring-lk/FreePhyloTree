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

#ifndef _COLOR_NODE_
#define _COLOR_NODE_

#include "Color.hpp"
#include "../Tree/Node.hpp"

namespace fpt
{
    class ColorNode : virtual public Node
    {
    public:
	ColorNode(const Name& name);

	GLfloat r() const;
	GLfloat g() const;
	GLfloat b() const;

	const Color& color() const;

	float bloom() const;

	void setColor(const Color& color);
	void setBloom(float bloom);

    private:
	Color _color;
	float _bloom;
    };
}

#endif
