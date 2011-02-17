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

#include <cstdlib>

#include "LocTree.hpp"

using namespace fpt;

LocTree::LocTree(const Name& name) : Tree(name)
{
    srand(time(NULL));
}

Vec3f LocTree::_rand(LocNode *father)
{
    GLfloat nx = rand() / (GLfloat)RAND_MAX;
    GLfloat ny = rand() / (GLfloat)RAND_MAX;

    nx = 30 * (1 - 2 * nx);
    ny = 30 * (1 - 2 * ny);

    Vec3f loc(nx, ny);

    if (father != NULL) {
//    loc *= _root->height() / (father->level() + 1);
	loc += father->loc();
    }

    return loc;
}

void LocTree::_rebootChildren(LocNode *father)
{
    const Nodes& children = father->children();

    for (int i = 0; i < children.size(); ++i) {
	LocNode *node = dynamic_cast<LocNode*>(children[i]);

	node->setLoc(_rand(father));

	if (!node->crib())
	    _rebootChildren(node);
    }
}
