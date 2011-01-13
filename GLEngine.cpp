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

#include <iostream>
#include "GLEngine.moc"

using namespace std;
using namespace FreePhyloTree;

GLEngine::GLEngine(PhyloTree *tree) : _tree(tree)
{
  setMouseTracking(true);
}

GLEngine::~GLEngine()
{
  delete _tree;
}

void GLEngine::animate()
{
  repaint();
}

void GLEngine::initializeGL()
{
  _tree->initSignal(this);
}

void GLEngine::paintGL()
{
  _tree->draw();
}

void GLEngine::mouseMoveEvent(QMouseEvent *event)
{
  QPointF pos = event->posF();

  if (event->buttons() == Qt::LeftButton) {
    Vec2f vec = Vec2f(pos.x() - _lastMouseEvent.x(),
		      _lastMouseEvent.y() - pos.y());

    _tree->lookAt(vec);
  }
  else {
    Vec2f alloc = _screen2pic(event->x(), event->y());
    _tree->allocMouse(alloc);
  }

  _lastMouseEvent = pos;
}

Vec2f GLEngine::_screen2pic(int x, int y)
{
  Vec2f inf = _tree->infPic();
  Vec2f sup = _tree->supPic();

  float desplX = ((float)x / width()) * (sup.x() - inf.x());
  float desplY = (1 - (float)y / height()) * (sup.y() - inf.y());

  return Vec2f(inf.x() + desplX,
	       inf.y() + desplY);
}
