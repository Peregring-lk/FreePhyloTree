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

#include "LocNode.hpp"

using namespace fpt;

LocNode::LocNode(const Name& name, LocNode *father)
    : Node(name, father)
{}

LocNode* LocNode::father() const
{
    return dynamic_cast<LocNode*>(Node::father());
}

LocNode* LocNode::child(unsigned i) const
{
    return dynamic_cast<LocNode*>(Node::child(i));
}

float LocNode::x() const
{
    return _loc.source().x();
}

float LocNode::y() const
{
    return _loc.source().y();
}

float LocNode::z() const
{
    return _loc.source().z();
}

VecXf LocNode::loc() const
{
    return _loc.source();
}

VecXf LocNode::locFather() const
{
    LocNode *father = this->father();

    if (father == NULL) {
	VecXf vec(2u);

	return vec;
    }
    else
	return father->loc();
}

const Loc& LocNode::smoothLoc() const
{
    return _loc;
}

void LocNode::setSourceLoc(const VecXf& loc)
{
    _loc.changeSource(loc);
}

void LocNode::setTargetLoc(const VecXf& loc)
{
    _loc.changeTarget(loc);
}

void LocNode::moveTargetLoc(const VecXf& delta)
{
    setTargetLoc(_loc.target() + delta);
}

void LocNode::changeSmooth(float smooth)
{
    _loc.changeSmooth(smooth);
}

void LocNode::_init()
{
    _loc.init();
}

void LocNode::_step()
{
    _loc.step();
}
