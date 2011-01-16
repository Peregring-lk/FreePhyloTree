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

// -------------------------------------------
// Main header file
// -------------------------------------------
#include "GraphicEngine.hpp"

// Activate namespace
using namespace std;
using namespace FreePhyloTree;

GraphicEngine::GraphicEngine(QFreePhyloTree *app, PhyloTree *tree)
    : _app(app)
    , _tree(tree)
{
    /// 1st.- Construct entities
    _cam = new Camera(_tree);
    _canvas = new Canvas(this, _tree, _cam);
    /// 2nd.- Build entities (shared info channels)
    /// 3rd.- Setup the canvas
    app->connect(app->GetTimer(), SIGNAL(timeout()), _canvas, SLOT(animate()));
    app->GetTimer()->start(40);
    _canvas->show();
}

GraphicEngine::~GraphicEngine()
{
    /// Destructor libera la memoria del arbol (y lo anula para evitar problemas)
    delete _tree;
    _tree=0;
}
