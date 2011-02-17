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

#ifndef _FPT_LOC_TREE_
#define _FPT_LOC_TREE_

#include "../Tree/Tree.hpp"
#include "LocNode.hpp"

namespace fpt
{
    class LocTree : virtual public Tree
    {
    public:
	LocTree(const Name& name);

    protected:
	Vec3f _rand(LocNode *father);
	void _rebootChildren(LocNode *father);
    };
}

#endif
