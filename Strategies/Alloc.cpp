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
#include "Alloc.hpp"

using namespace std;
using namespace FreePhyloTree;

SpringAlloc::SpringAlloc(float c1, float c2, float c3, float c4)
  : _c1(c1), _c2(c2), _c3(c3), _c4(c4)
{}

void SpringAlloc::reAlloc(Tree *tree)
{
  _moves.clear();
  _moves.resize(tree->order());

  const Edges& edges = tree->edges();
  const Edges& noAdjs = tree->noAdjs();

  for (int i = 0; i < edges.size(); ++i) {
    Edge edge = edges[i];
    Node *source = edge.source();
    Node *target = edge.target();

    if (!target->hide()) {
      _fa(source, target, edge.weight());
      _fa(target, source, edge.weight());
    }
  }

  for (int i = 0; i < noAdjs.size(); ++i) {
    Edge edge = noAdjs[i];
    Node *source = edge.source();
    Node *target = edge.target();

    if (!source->hide() && !target->hide()) {
      _fr(source, target);
      _fr(target, source); 
    }
  }

  for (int i = 0; i < _moves.size(); ++i)
    tree->node(i)->move(_moves[i]);
}

void SpringAlloc::_fa(Node *source, Node *target, int weight)
{
  Vec3f vu = source->alloc() - target->alloc();
  Vec3f fa = vu.unit() * _c1 * log(vu.norm() / weight);

  _moves[target->label()] += fa * _c4;
}

void SpringAlloc::_fr(Node *source, Node *target)
{
  Vec3f uv = target->alloc() - source->alloc();
  Vec3f fr = uv.unit() * (_c3 / pow(uv.norm(), 2));

  _moves[target->label()] += fr * _c4;
}
