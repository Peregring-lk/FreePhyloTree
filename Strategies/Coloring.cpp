/*
  Copyright (C) 2010 Aarón Bueno Villares <abv150ci@gmail.com>

  This file is part of FreePhyloTree.

  FreePhyloTree is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  GoM is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with FreePhyloTree.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Coloring.hpp"

using namespace FreePhyloTree;

void Coloring::coloring(Node *node)
{
  _coloring(node, Interval(), R);
}

void Coloring::_coloring(Node *node, Interval interval, TypeColor t)
{
  TypeColor newt = (TypeColor)((t + 1) % 3);
  const Nodes& nodes = node->children();

  node->setColor(interval.center());

  for (int i = 0; i < nodes.size(); ++i) {

    Interval newInterval(interval);
    newInterval.cut(t, nodes.size(), i);

    _coloring(nodes[i], newInterval, newt);
  }
}
