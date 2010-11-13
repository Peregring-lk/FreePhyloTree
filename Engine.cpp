#include <iostream>

#include "Engine.hpp"
#include "CladeViewer.hpp"

using namespace FreePhyloTree;
using namespace std;

Engine::Engine(CladeViewer *viewer) : _screen(NULL), _viewer(viewer)
{
  _eventMgr = new EventManager(_viewer);
}

Engine::~Engine()
{
  delete _eventMgr;
}

void Engine::initSignal()
{
  SDL_Init(SDL_INIT_VIDEO);

  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  _bestScreen();

  SDL_WM_SetCaption("FreePhyloTree", "FreePhyloTree");
}

void Engine::flowStage()
{
  _viewer->draw();

  SDL_GL_SwapBuffers();

  _eventMgr->readInput();

  //TODO: Reimprimir cuando la aplicación no esté en primer plano.
  //TODO: Framerate
}

void Engine::killSignal()
{
  SDL_Quit();
}

int Engine::screenW()
{
  return (_screen->w);
}

int Engine::screenH()
{
  return (_screen->h);
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

  if (!(_screen = SDL_SetVideoMode(400, 400, bbp, flags)))
    cerr << SDL_GetError() << endl;
}
