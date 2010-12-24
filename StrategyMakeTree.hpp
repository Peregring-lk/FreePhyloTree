#ifndef _STRATEGY_MAKE_TREE_
#define _STRATEGY_MAKE_TREE_

#include "Node.hpp"

namespace FreePhyloTree
{
  class StrategyMakeTree
  {
  public:
    virtual void initSignal() = 0;

    virtual void draw(Node *node) = 0;
  };
}

#endif
