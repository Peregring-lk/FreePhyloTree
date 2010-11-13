#ifndef _FPT_ENGINE_
#define _FPT_ENGINE_

#include <SDL/SDL.h>

#include "EventManager.hpp"

namespace FreePhyloTree
{
  class CladeViewer;

  class Engine
  {
  public:
    Engine(CladeViewer *viewer);
    ~Engine();

    void initSignal();
    void flowStage();
    void killSignal();

    int screenW();
    int screenH();

  private:
    SDL_Surface *_screen;

    EventManager *_eventMgr;

    CladeViewer *_viewer;

    // Private functions
    void _bestScreen();
  };
}

#endif
