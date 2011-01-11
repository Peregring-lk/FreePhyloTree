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

#include "Viewer.hpp"

#include "Engine.hpp"

using namespace FreePhyloTree;

Viewer::Viewer(PhyloTree *tree) : _tree(tree), _continue(true)
{
  _engine = new Engine(this);
}

Viewer::~Viewer()
{
  delete _engine;
  delete _tree;
}

PhyloTree* Viewer::tree() const
{
  return _tree;
}

void Viewer::run()
{
  _engine->initSignal();
  _tree->initSignal();
  SDL_Delay(2000);

  while(_continue)
    _engine->flowStage();

  _engine->killSignal();
}

void Viewer::draw()
{
  _tree->draw();
}

void Viewer::killSignal()
{
  _continue = false;
}
