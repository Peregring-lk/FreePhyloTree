#include <SDL/SDL.h>

#include "EventManager.hpp"
#include "CladeViewer.hpp"

using namespace FreePhyloTree;

EventManager::EventManager(CladeViewer *viewer) : _viewer(viewer)
{}

void EventManager::readInput()
{
  SDL_Event event;

  bool bcontinue = true;

  while(bcontinue) {

    // Sin eventos, dormimos.
    if (!SDL_PollEvent(&event))
      SDL_WaitEvent(&event);

    do {

      if (event.type == SDL_KEYDOWN) {
	SDLKey key = event.key.keysym.sym;

	if (key == SDLK_ESCAPE) {
	  _viewer->killSignal();
	  bcontinue = false;
	}
      }

    } while(bcontinue && SDL_PollEvent(&event));
  }
}

