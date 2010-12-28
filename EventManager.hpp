#ifndef _FPT_EVENT_MANAGER_
#define _FPT_EVENT_MANAGER_

#include "Engine.hpp"

namespace FreePhyloTree
{
  class EventManager
  {
  public:
    EventManager(Engine *engine);

    void readInput();

  private:
    Engine *_engine;
    Viewer *_viewer;

    bool _click;

    Vec2f _screen2pic(PhyloTree *tree, int x, int y);
  };
}

#endif
