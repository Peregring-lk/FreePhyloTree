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

#ifndef _FPT_ITERATOR_TREE_
#define _FPT_ITERATOR_TREE_

#include "Node.hpp"

#include <stack>

namespace fpt
{
    class IteratorTree
    {
    public:
	IteratorTree(Node *node);

	bool end() const;
	Node* node() const;

	unsigned index() const;
	IteratorTree forward() const;

	void next();

    private:
	Node *_node;
	std::stack<unsigned> _mem;
	unsigned _index;
    };
};

#endif
