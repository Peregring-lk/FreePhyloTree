#ifndef _GOURCEIAN_MAKE_TREE_
#define _GOURCEIAN_MAKE_TREE_

#include "StrategyMakeTree.hpp"

namespace FreePhyloTree
{
  class GourceianMakeTree : public StrategyMakeTree
  {
  public:
    void initSignal();

    void draw(Clade *clade);

  private:
    void _drawTreeClade(Clade *clade, float dx, float dy);

    void _drawNode(float side, float x, float y);
    void _drawEdge(float xO, float yO, float xD, float yD);

  };
}

#endif
