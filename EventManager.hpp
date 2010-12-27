#ifndef _FPT_EVENT_MANAGER_
#define _FPT_EVENT_MANAGER_

namespace FreePhyloTree
{
  class Viewer;

  class EventManager
  {
  public:
    EventManager(Viewer *viewer);

    void readInput();

  private:
    Viewer *_viewer;
  };
}

#endif
