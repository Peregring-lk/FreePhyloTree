#ifndef _STRATEGY_MAKE_TREE_
#define _STRATEGY_MAKE_TREE_

#include <GL/glut.h>

#include "Clade.hpp"

namespace FreePhyloTree
{
  class StrategyMakeTree
  {
  public:
    void init()
    {
      glutDisplayFunc(makeTreeClade);
    }

    virtual void makeTreeClade() = 0;
  };
}

#endif
