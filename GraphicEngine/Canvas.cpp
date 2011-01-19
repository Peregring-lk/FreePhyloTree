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
#include "Canvas.moc"

// -------------------------------------------
// FreePhyloTree classes
// -------------------------------------------
#include "GraphicEngine.hpp"

// Activate namespace
using namespace std;
using namespace FreePhyloTree;

Canvas::Canvas(GraphicEngine *ge, PhyloTree *tree, Camera *cam)
    : _ge(ge)
    , _tree(tree)
    , _cam(cam)
{
    /// 1st.- Activate mouse events
    setMouseTracking(true);
    /// 2nd.- Get canvas size
    _size = Vec2f(width(),height());
    resizeGL(_size.x(), _size.y());

    _webView.hide();
}

Canvas::~Canvas()
{
}

void Canvas::animate()
{
    repaint();
}

void Canvas::initializeGL()
{
    // Don't needed for the moment
}

void Canvas::paintGL()
{

}

void Canvas::resizeGL(int width, int height)
{
    _size = Vec2f(width, height);
}

void Canvas::keyPressEvent(QKeyEvent *event)
{
}

void Canvas::mouseDoubleClickEvent(QMouseEvent *event)
{
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
}

