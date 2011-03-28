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

#include <iostream>

#include "GraphicEngine/GraphicEngine.hpp"
#include "PhyloTree.hpp"

using namespace fpt;

PhyloTree::PhyloTree(Name name, PhyloNode *root,
		     float c1, float c2, float c3, float c4)
    : LocTree(name, root, c1, c2, c3, c4),
      ColorTree(name, root),
      Tree(name, root)
{}

PhyloNode* PhyloTree::root() const
{
    return dynamic_cast<PhyloNode*>(Tree::root());
}

PhyloNode* PhyloTree::phyloNode(const Name& name) const
{
    for (auto i = begin(); !i.end(); i.next()) {
	PhyloNode *node = i.node();

	if (node->name() == name)
	    return node;
    }

    return NULL;
}

bool PhyloTree::changed() const
{
    return ColorTree::changed() || LocTree::changed();
}

IteratorPhyloTree PhyloTree::begin(PhyloNode *node) const
{
    if (node == NULL)
	node = root();

    return IteratorPhyloTree(node);
}

void PhyloTree::clearNode(PhyloNode *node)
{
    LocTree::clearNode(node);
    ColorTree::clearNode(node);
}

void PhyloTree::_init()
{
    ColorTree::_init();
    LocTree::_init();
}

void PhyloTree::_step()
{
    ColorTree::_step();
    LocTree::_step();
}
