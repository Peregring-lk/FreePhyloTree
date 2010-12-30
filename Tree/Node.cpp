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

void Node::setBloom(float bloom)
{
  _bloom = bloom;
}

void Node::move(const Vec2f& desp)
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
