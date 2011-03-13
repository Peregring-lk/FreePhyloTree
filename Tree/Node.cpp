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
#include "Tree.hpp"

using namespace fpt;

Node::Node(const Name& name, Node *father)
    : _name(name), _father(father)
{
    _order = 1;
}

Node::~Node()
{
    for (int i = 0; i < degree(); ++i)
	delete child(i);
}

const Name& Node::name() const
{
    return _name;
}

unsigned Node::degree() const
{
    return _children.size();
}

unsigned Node::order() const
{
    return _order;
}

Node* Node::father() const
{
  return _father;
}

Node* Node::child(unsigned i) const
{
    if (i < degree())
	return _children[i];
    else
	return NULL;
}

void Node::addChild(Node *node)
{
    _children.push_back(node);
    _updateOrder();
}

void Node::_updateOrder()
{
    _order += 1;

    Node *father = Node::father();

    if (father != NULL)
	father->_updateOrder();
}
