#ifndef _FPT_EVENT_MANAGER_
#define _FPT_EVENT_MANAGER_

namespace FreePhyloTree
{
  class CladeViewer;

  class EventManager
  {
  public:
    EventManager(CladeViewer *viewer);

    void readInput();

  private:
    CladeViewer *_viewer;
  };
}

#endif
