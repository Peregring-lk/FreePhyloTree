#include "Coloring.hpp"

using namespace FreePhyloTree;

void Coloring::coloring(Node *node)
{
  _coloring(node, Interval(), R);
}

void Coloring::_coloring(Node *node, Interval interval, TypeColor t)
{
  TypeColor newt = (TypeColor)((t + 1) % 3);
  const Nodes& nodes = node->children();

  node->setColor(interval.center());

  for (int i = 0; i < nodes.size(); ++i) {

    Interval newInterval(interval);
    newInterval.cut(t, nodes.size(), i);

    _coloring(nodes[i], newInterval, newt);
  }
}
