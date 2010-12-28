#ifndef _FPT_ENGINE_
#define _FPT_ENGINE_

#include <SDL/SDL.h>

#include "Viewer.hpp"

namespace FreePhyloTree
{
  class EventManager;

  class Engine
  {
  public:
    Engine(Viewer *viewer);
    ~Engine();

    int width() const;
    int height() const;

    Viewer* viewer() const;

    void initSignal();
    void flowStage();
    void killSignal();

  private:
    SDL_Surface *_screen;

    Viewer *_viewer;
    EventManager *_eventMgr;

    int _width;
    int _height;

    // Private functions
    void _bestScreen();
  };
}

#endif
