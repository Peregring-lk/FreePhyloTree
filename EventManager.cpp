#include <iostream>
#include <SDL/SDL.h>

#include "EventManager.hpp"

using namespace std;
using namespace FreePhyloTree;

EventManager::EventManager(Engine *engine) : _engine(engine)
{
  _viewer = _engine->viewer();
  _click = false;
}

void EventManager::readInput()
{
  SDL_Event event;

  bool bcontinue = true;

  PhyloTree *tree = _viewer->tree();

  // while(bcontinue) {

  //   // Sin eventos, dormimos.
  //   if (!SDL_PollEvent(&event))
  //     SDL_WaitEvent(&event);

  do {

    if (event.type == SDL_KEYDOWN) {
      SDLKey key = event.key.keysym.sym;

      if (key == SDLK_ESCAPE) {
	_viewer->killSignal();
	//	bcontinue = false;
      }
      else if (key == SDLK_SPACE)
	tree->gotoRoot();
    }
    else if (event.type == SDL_MOUSEMOTION) {

      if (_click)
	tree->lookAt(Vec2f(event.motion.xrel,
			   event.motion.yrel));
      else {
	Vec2f alloc = _screen2pic(tree, event.button.x, event.button.y);
	tree->allocMouse(alloc);
      }
    }      
    else if (event.type == SDL_MOUSEBUTTONDOWN)
      _click = true;
    else if (event.type == SDL_MOUSEBUTTONUP)
      _click = false;

  } while(SDL_PollEvent(&event));
  //}
}

Vec2f EventManager::_screen2pic(PhyloTree *tree, int x, int y)
{
  Vec2f inf = tree->infPic();
  Vec2f sup = tree->supPic();

  float desplX = ((float)x / _engine->width()) * (sup.x() - inf.x());
  float desplY = (1 - (float)y / _engine->height()) * (sup.y() - inf.y());

  return Vec2f(inf.x() + desplX,
	       inf.y() + desplY);
}

