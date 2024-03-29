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

#include "Tree.hpp"

using namespace std;
using namespace fpt;

Tree::Tree(const Name& name, Node *root) : _name(name), _root(root)
{}

Tree::~Tree()
{
    delete _root;
}

Name Tree::name() const
{
    return _name;
}

unsigned Tree::order() const
{
    if (_root == NULL)
	return 0;
    else
	return _root->order();
}

Node* Tree::root() const
{
    return _root;
}

IteratorTree Tree::begin(Node *node) const
{
    if (node == NULL)
	node = root();

    return IteratorTree(node);
}

void Tree::crib(Node *node)
{
    if (node != root())
    {
	node->father()->quitChild(node);

	delete root();

	node->changeFather(NULL);

	_root = node;
    }
}

void Tree::reboot(const Name& name, Node *root)
{
    delete _root;

    _name = name;
    _root = root;
}
