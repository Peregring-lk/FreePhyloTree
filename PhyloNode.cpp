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

#include "PhyloNode.hpp"

using namespace fpt;

PhyloNode::PhyloNode(const Name& name, PhyloNode *father)
    : LocNode(name, father), ColorNode(name, father), Node(name, father)
{}

PhyloNode* PhyloNode::father() const
{
    return dynamic_cast<PhyloNode*>(Node::father());
}

PhyloNode* PhyloNode::child(unsigned i) const
{
    return dynamic_cast<PhyloNode*>(Node::child(i));
}

void PhyloNode::init()
{
    ColorNode::init();
    LocNode::init();
}

void PhyloNode::step()
{
    ColorNode::step();
    LocNode::step();
}
