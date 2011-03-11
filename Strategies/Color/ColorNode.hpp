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

#ifndef _FPT_COLOR_NODE_
#define _FPT_COLOR_NODE_

#include "../../Tree/Node.hpp"

#include "../Strategy.hpp"
#include "../Smooth.hpp"
#include "CubeColor.hpp"

namespace fpt
{
    typedef Smooth Color;
    typedef Smooth Glow;

    class ColorNode : virtual public Node, virtual public Strategy
    {
    public:
	ColorNode(const Name& name, ColorNode *father = NULL);

	ColorNode* father() const;
	ColorNode* child(unsigned i) const;

	float r() const;
	float g() const;
	float b() const;
	float glow() const;

	const Color& smoothColor() const;
	const Glow& smoothGlow() const;

	CubeColor fatherCubeColor() const;
	CubeColor cubeColor() const;

	bool changed() const;

	void randSourceGlow(float center, float radius = 0);

	void setSourceColor(float r, float g, float b);
	void setCubeColor(const CubeColor& cube);

	void setSourceGlow(float glow);
	void setTargetGlow(float glow);

	void changeSmoothColor(float smooth);
	void changeSmoothGlow(float smooth);

    protected:
	void _init();
	void _step();

    private:
	Color _color;
	Glow _glow;

	CubeColor _cube;
    };
}

#endif
