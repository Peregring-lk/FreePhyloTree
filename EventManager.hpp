#ifndef _FPT_EVENT_MANAGER_
#define _FPT_EVENT_MANAGER_

#include <GL/glut.h>

namespace FreePhyloTree
{
  class EventManager
  {
  public:
    void init();

    void mouse(int button, int state, int x, int y);
  };
}

#endif
