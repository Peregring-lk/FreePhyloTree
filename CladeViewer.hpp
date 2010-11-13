#ifndef _CLADE_VIEWER_
#define _CLADE_VIEWER_

#include "Engine.hpp"
#include "Clade.hpp"
#include "StrategyMakeTree.hpp"

namespace FreePhyloTree
{
  enum DrawStrategy { GOURCEIAN };

  class CladeViewer
  {
  public:
    CladeViewer(Clade *clade, DrawStrategy strategy);
    ~CladeViewer();

    void run();

    void draw();

    void killSignal();

  private:
    Clade *_clade;

    Engine *_engine;
    StrategyMakeTree *_strategy;

    bool _continue;
  };
}

#endif
