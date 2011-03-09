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
#include <cmath>

#include "LocTree.hpp"

using namespace fpt;

LocTree::LocTree(const Name& name, LocNode *root,
		 float c1, float c2, float c3, float c4,
		 float smooth)
    : Tree(name, root), _c1(c1), _c2(c2), _c3(c3), _c4(c4),
      _smooth(smooth)
{
    srand(time(NULL));
}

LocNode* LocTree::root() const
{
    return dynamic_cast<LocNode*>(Tree::root());
}

VecXf LocTree::locRoot() const
{
    LocNode *root = this->root();

    if (root == NULL)
	return VecXf();
    else
	return root->loc();
}

void LocTree::init()
{
    for (auto i = begin(); !i.end(); i.next()) {
	LocNode *node = i.node();
	VecXf rand(node->locFather(), 100.0f);

	node->setSourceLoc(rand);
	node->setTargetLoc(rand);
	node->changeSmooth(_smooth);

	node->init();
    }
}

void LocTree::step()
{
    _Moves moves(order(), VecXf(2u));

    for (auto i = begin(); !i.end(); i.next()) {
	LocNode *source = i.node();

	for (auto j = i.forward(); !j.end(); j.next()) {
	    LocNode *target = j.node();

	    if (source == target->father()) {
		moves[j.index()] += _fa(source, target);
		moves[i.index()] += _fa(target, source);
	    }
	    else {
		moves[j.index()] += _fr(source, target);
		moves[i.index()] += _fr(target, source);
	    }
	}
    }

    for (auto i = begin(); !i.end(); i.next())
	i.node()->moveTargetLoc(moves[i.index()]);

    for (auto i = begin(); !i.end(); i.next())
	i.node()->step();
}

IteratorLocTree LocTree::begin()
{
    return IteratorLocTree(root());
}

VecXf LocTree::_fa(LocNode *source, LocNode *target) const
{
    VecXf vu = source->loc() - target->loc();
    VecXf fa = vu.unit() * _c1 * log(vu.norm() / _c2);

    return fa * _c4;
}

VecXf LocTree::_fr(LocNode *source, LocNode *target) const
{
    VecXf uv = target->loc() - source->loc();
    VecXf fr = uv.unit() * (_c3 / pow(uv.norm(), 2));

    return fr * _c4;
}
