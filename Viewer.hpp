#ifndef _CLADE_VIEWER_
#define _CLADE_VIEWER_

#include "PhyloTree.hpp"

namespace FreePhyloTree
{
  class Engine;

  class Viewer
  {
  public:
    Viewer(PhyloTree *_tree);
    ~Viewer();

    PhyloTree* tree() const;

    void run();

    void draw();

    void killSignal();

  private:
    PhyloTree *_tree;

    Engine *_engine;

    bool _continue;
  };
}

#endif
