#include "Node.hpp"

using namespace std;
using namespace FreePhyloTree;

Node::Node(Clade *clade, Node *father, StrategyColor *strategyColor)
  : _clade(clade), _father(father), _strategyColor(strategyColor)
{
  Subclades subclades = clade->getSubclades();

  _calcDepth();

  for (int i = 0; i < subclades.size(); ++i)
    _children.push_back(new Node(subclades[i], this, _strategyColor));

  _calcHeight();
  calcColor(_height, 0, 0, NULL);
}

Color Node::getColor() const
{
  return (_color);
}

int Node::getDepth() const
{
  return (_depth);
}

int Node::getHeight() const
{
  return (_height);
}

int Node::getDegree() const
{
  return (_children.size());
}

const Children& Node::getChildren() const
{
  return (_children);
}

void Node::calcColor(int depth, int brothers, int n,
		     const Interval *father)
{
  Interval interval = _strategyColor->getInterval(depth, brothers,
						  n, father);

  int nChild = _children.size();

  for (int i = 0; i < nChild; ++i)
    _children[i]->calcColor(depth, nChild, i, &interval);

  _color = _strategyColor->getColor(interval);
}

void Node::_calcDepth()
{
  if (_father == NULL)
    _depth = 0;
  else
    _depth = 1 + _father->getDepth();
}

void Node::_calcHeight()
{
  int _height = 0;
  int nChild = _children.size();

  for (int i = 0; i < nChild; ++i) {
    int childHeight = _children[i]->getHeight();

    if (_height < childHeight)
      _height = childHeight;
  }

  if (nChild)
    ++_height;
}
