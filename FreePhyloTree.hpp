#ifndef _FREE_PHYLO_TREE_
#define _FREE_PHYLO_TREE_

#include <QApplication>
#include "GLEngine.hpp"

namespace FreePhyloTree
{
  class QFreePhyloTree : public QApplication
  {
  public:
    QFreePhyloTree(PhyloTree *tree, int argc, char **argv);

    void run();
    
  private:
    GLEngine _glEngine;
  };
}

#endif
