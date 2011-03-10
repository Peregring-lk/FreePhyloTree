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

#ifndef _FPT_COLOR_TREE_
#define _FPT_COLOR_TREE_

#include "../../Tree/Tree.hpp"
#include "IteratorColorTree.hpp"

namespace fpt
{
    class ColorTree : virtual public Tree, virtual public Strategy
    {
    public:
	ColorTree(const Name& name, ColorNode *root,
		  float smoothColor = 0.01, float smoothGlow = 0.01);

	ColorNode* root() const;

	IteratorColorTree begin(ColorNode *node = NULL);

    protected:
	void _init();
	void _step();

	void _initCubes(ColorNode *node, CubeColor cube, TypeC t);

    private:
	float _smoothColor;
	float _smoothGlow;
    };
}

#endif
