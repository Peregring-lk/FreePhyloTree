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

#ifndef _ALLOC_
#define _ALLOC_

#include "../Tree/Tree.hpp"

namespace FreePhyloTree
{
  class SpringAlloc
  {
  public:
    SpringAlloc(float c1, float c2, float c3, float c4);

    void reAlloc(Tree *tree);

  private:
    float _c1;
    float _c2;
    float _c3;
    float _c4;

    typedef std::vector<Vec2f> _Moves;
    _Moves _moves;

    void _fa(Node *source, Node *target, int _weight);
    void _fr(Node *source, Node *target);
  };
}

#endif
