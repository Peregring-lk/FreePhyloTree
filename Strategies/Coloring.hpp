#ifndef _COLORING_
#define _COLORING_

#include "../Tree/Tree.hpp"
#include "Interval.hpp"

namespace FreePhyloTree
{
  class Coloring
  {
  public:
    void coloring(Node *tree);

  private:
    TypeColor _actual;

    void _coloring(Node *node, Interval interval, TypeColor t);
  };
};

#endif
