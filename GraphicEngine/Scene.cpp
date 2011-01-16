/*
  Copyright (C) 2011 Aarón Bueno Villares <abv150ci@gmail.com>

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
#include "Scene.hpp"

// Activate namespace
using namespace std;
using namespace FreePhyloTree;

Scene::Scene(PhyloTree *tree, Camera *cam)
    : _tree(tree)
    , _cam(cam)
{
    /// 1st.- Build another OpenGL context
    _context = new QGLContext(QGLFormat());
    _context->create();
    /// 2nd.- Build the frame buffer object where the rendered scene will be stored
    _rttObject = new QGLFramebufferObject(1024, 1024);
}

Scene::~Scene()
{
}

void Scene::Render()
{
    /// 1st.- Create a painter.
    QPainter fbo_painter(_rttObject);
    /// 2nd.- Set the context
    _context->makeCurrent();
    /// 3rd.- Draws the scene
    _rttObject->bind();
    Draw();
    _rttObject->release();
    /// 4th.- End offscreen render
    fbo_painter.end();
}
