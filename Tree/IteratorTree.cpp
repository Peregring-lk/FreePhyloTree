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

/*! \file IteratorTree.cpp
 *  \brief Fichero que implementa a la clase \c fpt::IteratorTree.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2011
 *  \version 0.7
 *  \since 0.7
 */

#include <iostream>
#include "IteratorTree.hpp"

using namespace fpt;

IteratorTree::IteratorTree(Node *node)
{
    _node = node;
    _top = node->father();

    _mem.push(0);
    _index = 0;
}

bool IteratorTree::end() const
{
    return _node == _top;
}

Node* IteratorTree::node() const
{
    return _node;
}

unsigned IteratorTree::index() const
{
    return _index;
}

IteratorTree IteratorTree::forward() const
{
    IteratorTree clone = *this;

    clone.next();

    return clone;
}

void IteratorTree::next()
{
    if (end())
	return;

    if (_mem.top() < _node->degree()) {
	_node = _node->child(_mem.top());
	_mem.push(0);

	++_index;
    }
    else {
	_mem.pop();

	if (!_mem.empty())
	    ++_mem.top();

	_node = _node->father();
	next();
    }
}
