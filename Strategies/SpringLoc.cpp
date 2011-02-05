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
#include <cmath>
#include "SpringLoc.hpp"

using namespace std;
using namespace FreePhyloTree;

SpringLoc::SpringLoc(float c1, float c2, float c3, float c4)
    : _c1(c1), _c2(c2), _c3(c3), _c4(c4)
{}

void SpringLoc::reLoc(LocTree *tree)
{
    _moves.clear();
    _moves.resize(tree->order());

    const Edges& edges = tree->edges();
    const Edges& noAdjs = tree->noAdjs();

    for (int i = 0; i < edges.size(); ++i) {
	Edge edge = edges[i];
	LocNode *source = dynamic_cast<LocNode*>(edge.source());
	LocNode *target = dynamic_cast<LocNode*>(edge.target());

	if (!target->hide()) {
	    _fa(source, target, edge.weight());
	    _fa(target, source, edge.weight());
	}
    }

    for (int i = 0; i < noAdjs.size(); ++i) {
	Edge edge = noAdjs[i];
	LocNode *source = dynamic_cast<LocNode*>(edge.source());
	LocNode *target = dynamic_cast<LocNode*>(edge.target());

	if (!source->hide() && !target->hide()) {
	    _fr(source, target);
	    _fr(target, source);
	}
    }

    for (int i = 0; i < _moves.size(); ++i) {
	LocNode *node = dynamic_cast<LocNode*>(tree->node(i));
	node->move(_moves[i]);
    }
}

void SpringLoc::_fa(LocNode *source, LocNode *target, int weight)
{
    Vec2f vu = source->loc() - target->loc();
    Vec2f fa = vu.unit() * _c1 * log(vu.norm() / weight);

    _moves[target->label()] += fa * _c4;
}

void SpringLoc::_fr(LocNode *source, LocNode *target)
{
    Vec2f uv = target->loc() - source->loc();
    Vec2f fr = uv.unit() * (_c3 / pow(uv.norm(), 2));

    _moves[target->label()] += fr * _c4;
}
