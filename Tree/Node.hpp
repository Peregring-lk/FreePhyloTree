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

#ifndef _FPT_NODE_
#define _FPT_NODE_

#include <string>
#include <vector>

namespace fpt
{
    class Tree;
    typedef std::string Name;

    class Node
    {
    public:
	Node(const Name& name, Node *father = NULL);
	virtual ~Node();

	const Name& name() const;

	unsigned degree() const;
	unsigned order() const;
	unsigned level() const;

	virtual Node* father() const;
	virtual Node* child(unsigned i) const;

	void addChild(Node *node);
	virtual void clear();

    protected:
	Name _name;

	Node *_father;
	std::vector<Node*> _children;

	unsigned _order;

	void _updateOrder(int f = 1);
    };
}

#endif
