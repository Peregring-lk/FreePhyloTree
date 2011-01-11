/*
  Copyright (C) 2010 Aarón Bueno Villares <abv150ci@gmail.com>

  This file is part of FreePhyloTree.

  FreePhyloTree is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  FreePhyloTree is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with FreePhyloTree.  If not, see <http://www.gnu.org/licenses/>.
*/

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
