#ifndef _NODE_
#define _NODE_

#include <vector>
#include "Clade.hpp"
#include "StrategyColor.hpp"

namespace FreePhyloTree
{
  class Node;
  typedef std::vector<Node*> Children;

  class Node
  {
  public:
    Node(Clade *clade, Node *father, StrategyColor *strategyColor);

    Color getColor() const;

    int getDepth() const;
    int getHeight() const;
    int getDegree() const;

    const Children& getChildren() const;
    void calcColor(int windows, int brothers, int n,
		   const Interval *father);

  private:
    Clade *_clade;
    Node *_father;

    StrategyColor *_strategyColor;
    Color _color;

    Children _children;

    int _depth;
    int _height;

    void _calcDepth();
    void _calcHeight();
  };
}

#endif
