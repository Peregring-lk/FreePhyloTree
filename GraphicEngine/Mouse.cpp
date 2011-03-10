/*
  Copyright (C) 2011 Aarón Bueno Villares <abv150ci@gmail.com>

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

#include "Mouse.hpp"

using namespace fpt;

Mouse::Mouse(PhyloTree *tree) : _tree(tree), _pos(2u), _mov(2u)
{}

VecXf Mouse::pos() const
{
    return _pos;
}

VecXf Mouse::mov() const
{
    return _mov;
}

PhyloNode* Mouse::searchNode() const
{
    for (auto i = _tree->begin(); !i.end(); i.next()) {
	PhyloNode *node = i.node();

	if ((node->proj() - _pos).norm() < 10)
	    return node;
    }
}

void Mouse::setPos(VecXf pos)
{
    _mov = pos - _pos;
    _pos = pos;
}

void Mouse::move(VecXf delta)
{
    _mov = delta;
    _pos += delta;
}
