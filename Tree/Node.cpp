#include "Node.hpp"

using namespace FreePhyloTree;

Node::Node(const Name& name) : _name(name)
{
  _father = NULL;

  _level = 0;
  _height = 0;
}

Name Node::name() const
{
  return _name;
}

Label Node::label() const
{
  return _label;
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

const Vec2f& Node::alloc() const
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

void Node::setAlloc(const Vec2f& alloc)
{
  _alloc = alloc;
}

void Node::move(const Vec2f& desp)
{
  _alloc += desp;
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
