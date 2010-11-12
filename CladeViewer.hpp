#ifndef _CLADE_VIEWER_
#define _CLADE_VIEWER_

#include "Engine.hpp"
#include "EventManager.hpp"
#include "Clade.hpp"
#include "StrategyMakeTree.hpp"

namespace FreePhyloTree
{
  enum BuildStrategy { GOURCEIAN };

  class CladeViewer
  {
  public:
    CladeViewer(Clade *clade, BuildStrategy strategy);
    ~CladeViewer();

    void init(int argc, char **argv);
    void kill();

  private:
    Clade *_clade;

    Engine *_engine;
    EventManager *_eventMgr;

    StrategyMakeTree *_strategy;
  };
}

#endif
