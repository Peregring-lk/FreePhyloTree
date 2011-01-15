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

using namespace FreePhyloTree;

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

Node::Node(const Name& name, bool hide) : _name(name)
{
  _father = NULL;

  _level = 0;
  _height = 0;
  _crib = false;
}

Name Node::name() const
{
  return _name;
}

Label Node::label() const
{
  return _label;
}

bool Node::crib() const
{
  return _crib;
}

bool Node::hide() const
{
  if (_father == NULL)
    return false;
  else if (_father->crib())
    return true;
  else
    return _father->hide();
}

float Node::bloom() const
{
  return _bloom;
}

GLfloat Node::r() const
{
  return _color.r();
}

GLfloat Node::g() const
{
  return _color.g();
}

GLfloat Node::b() const
{
  return _color.b();
}

GLfloat Node::x() const
{
  return _alloc.x();
}

GLfloat Node::y() const
{
  return _alloc.y();
}

const Color& Node::color() const
{
  return _color;
}

const Vec3f& Node::alloc() const
{
  return _alloc;
}

Node* Node::father() const
{
  return _father;
}

const Nodes& Node::children() const
{
  return _children;
}

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

unsigned Node::nodes() const
{
  if (hide())
    return 0;
  else {
    unsigned nodes = 1;

    for (int i = 0; i < _children.size(); ++i)
      nodes += _children[i]->nodes();

    return nodes;
  }
}

Node* Node::root()
{
  if (_father == NULL)
    return this;
  else
    _father->root();
}

void Node::setColor(const Color& color)
{
  _color = color;
}

void Node::setAlloc(const Vec3f& alloc)
{
  _alloc = alloc;
}

void Node::setBloom(float bloom)
{
  _bloom = bloom;
}

void Node::move(const Vec3f& desp)
{
  _alloc += desp;
}

void Node::setCrib(bool crib)
{
  _crib = crib;
}

void Node::_uploadHeight(Node *n)
{
  unsigned newHeight = n->height() + 1;

  if (newHeight > _height) {
    _height = newHeight;
      
    if (_father != NULL)
      _father->_uploadHeight(this);
  }
}
