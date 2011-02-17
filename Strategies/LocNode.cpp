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

LocNode::LocNode(const Name& name) : Node(name)
{
    _crib = false;
}

GLfloat LocNode::x() const
{
    return _loc.x();
}

GLfloat LocNode::y() const
{
    return _loc.y();
}

const Vec3f& LocNode::loc() const
{
    return _loc;
}

bool LocNode::crib() const
{
    return _crib;
}

bool LocNode::hide() const
{
    LocNode *father = dynamic_cast<LocNode*>(_father);

    if (_father == NULL)
	return false;
    else if (father->crib())
	return true;
    else
	return father->hide();
}

void LocNode::setLoc(const Vec3f& loc)
{
    _loc = loc;
}

void LocNode::move(const Vec3f& desp)
{
    _loc += desp;
}

void LocNode::setCrib(bool crib)
{
    _crib = crib;
}
