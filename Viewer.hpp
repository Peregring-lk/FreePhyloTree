#ifndef _CLADE_VIEWER_
#define _CLADE_VIEWER_

#include "Engine.hpp"
#include "PhyloTree.hpp"

namespace FreePhyloTree
{
  class Viewer
  {
  public:
    Viewer(PhyloTree *_tree);
    ~Viewer();

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
