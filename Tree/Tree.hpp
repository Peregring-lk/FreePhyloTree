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

#ifndef _FPT_TREE_
#define _FPT_TREE_

#include "Node.hpp"
#include "IteratorTree.hpp"

namespace fpt
{
    class Tree
    {
    public:
	Tree(const Name& name, Node *root);
	~Tree();

	Name name() const;
	unsigned order() const;

	virtual Node* root() const;

	IteratorTree begin(Node *node = NULL) const;

    protected:
	Name _name;
	Node *_root;

	void _checkRoot();
    };
}

#endif
