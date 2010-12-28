#include <iostream>

#include "Engine.hpp"
#include "EventManager.hpp"

using namespace std;
using namespace FreePhyloTree;

Engine::Engine(Viewer *viewer) : _screen(NULL), _viewer(viewer)
{
  _eventMgr = new EventManager(this);

  _width = 400;
  _height = 400;
}

Engine::~Engine()
{
  delete _eventMgr;
}

int Engine::width() const
{
  return _width;
}

int Engine::height() const
{
  return _height;
}

Viewer* Engine::viewer() const
{
  return _viewer;
}

void Engine::initSignal()
{
  SDL_Init(SDL_INIT_VIDEO);

  _bestScreen();

  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  SDL_WM_SetCaption("FreePhyloTree", "FreePhyloTree");
}

void Engine::flowStage()
{
  _viewer->draw();

  SDL_GL_SwapBuffers();

  _eventMgr->readInput();

  SDL_Delay(40);
  //TODO: Framerate
}

void Engine::killSignal()
{
  SDL_Quit();
}

void Engine::_bestScreen()
{
  const SDL_VideoInfo *info = SDL_GetVideoInfo();
  Uint32 flags = SDL_OPENGL;

  if (info->hw_available)
    flags = flags | SDL_HWSURFACE;
  else
    flags = flags | SDL_SWSURFACE;

  int bbp = info->vfmt->BitsPerPixel;

  if (!(_screen = SDL_SetVideoMode(_width, _height, bbp, flags)))
    cerr << SDL_GetError() << endl;
}
