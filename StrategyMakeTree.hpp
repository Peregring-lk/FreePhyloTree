#ifndef _STRATEGY_MAKE_TREE_
#define _STRATEGY_MAKE_TREE_

#include "Clade.hpp"

namespace FreePhyloTree
{
  class StrategyMakeTree
  {
  public:
    virtual void initSignal() = 0;

    virtual void draw(Clade *clade) = 0;
  };
}

#endif
