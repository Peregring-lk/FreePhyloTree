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

#include "Node.hpp"

using namespace fpt;

Edge::Edge(Node *source, Node *target, int weight)
  : _source(source), _target(target), _weight(weight)
{}

Node* Edge::source() const
{
  return _source;
}

Node* Edge::target() const
{
  return _target;
}

int Edge::weight() const
{
  return _weight;
}

Node::Node(const Name& name) : _name(name)
{
  _father = NULL;

/*
  _level = 0;
  _height = 0;
*/
}

const Name& Node::name() const
{
  return _name;
}

Label Node::label() const
{
  return _label;
}

Node* Node::father() const
{
  return _father;
}

const Nodes& Node::children() const
{
  return _children;
}

unsigned Node::nodes() const
{
    unsigned nodes = 1;

    for (int i = 0; i < _children.size(); ++i)
	nodes += _children[i]->nodes();

    return nodes;
}

/*
unsigned Node::degree() const
{
  return _children.size();
}

unsigned Node::level() const
{
  return _level;
}

unsigned Node::height() const
{
  return _height;
}
*/

Node* Node::root()
{
  if (_father == NULL)
    return this;
  else
    _father->root();
}

/*
void Node::_uploadHeight(Node *n)
{
  unsigned newHeight = n->height() + 1;

  if (newHeight > _height) {
    _height = newHeight;

    if (_father != NULL)
      _father->_uploadHeight(this);
  }
}
*/
