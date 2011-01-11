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

#ifndef _COLORING_
#define _COLORING_

#include "../Tree/Tree.hpp"
#include "Interval.hpp"

namespace FreePhyloTree
{
  class Coloring
  {
  public:
    void coloring(Node *tree);

  private:
    TypeColor _actual;

    void _coloring(Node *node, Interval interval, TypeColor t);
  };
};

#endif
