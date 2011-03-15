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

#ifndef _FPT_PHYLO_TREE_
#define _FPT_PHYLO_TREE_

#include "IteratorPhyloTree.hpp"
#include "Strategies/Color/ColorTree.hpp"
#include "Strategies/Loc/LocTree.hpp"

namespace fpt
{
    class PhyloTree : public LocTree, public ColorTree
    {
    public:
	PhyloTree(Name name, PhyloNode *root,
		  float c1, float c2, float c3, float c4);

	PhyloNode* root() const;

	bool changed() const;

	IteratorPhyloTree begin(PhyloNode *node = NULL);

    protected:
	void _init();
	void _step();

    private:
	float _radiusNode;
	float _radiusBloom;
    };
}

#endif
