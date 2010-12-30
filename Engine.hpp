/*
  Copyright (C) 2010 Aarón Bueno Villares <abv150ci@gmail.com>

  This file is part of FreePhyloTree.

  FreePhyloTree is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  GoM is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with FreePhyloTree.  If not, see <http://www.gnu.org/licenses/>.
*/

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
