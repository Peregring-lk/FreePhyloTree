#ifndef _FPT_ENGINE_
#define _FPT_ENGINE_

#include <SDL/SDL.h>

#include "EventManager.hpp"

namespace FreePhyloTree
{
  class Viewer;

  class Engine
  {
  public:
    Engine(Viewer *viewer);
    ~Engine();

    void initSignal();
    void flowStage();
    void killSignal();

    int screenW();
    int screenH();

  private:
    SDL_Surface *_screen;

    EventManager *_eventMgr;

    Viewer *_viewer;

    // Private functions
    void _bestScreen();
  };
}

#endif
