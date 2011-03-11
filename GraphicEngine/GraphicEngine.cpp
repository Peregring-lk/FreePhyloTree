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
#include <QApplication>
#include "GraphicEngine.hpp"

#include "Scene.hpp"
#include "Viewing.hpp"

using namespace std;
using namespace fpt;

GraphicEngine::GraphicEngine(PhyloTree *tree)
    : Strategy(), _tree(tree)
{
    _viewing = new Viewing(_tree, width(), height());
    _mouse = new Mouse(_tree, _viewing);
    _scene = new Scene(_tree, _mouse);

    setMouseTracking(true);
}

GraphicEngine::~GraphicEngine()
{
    delete _viewing;
    delete _scene;
    delete _mouse;
}

void GraphicEngine::animate()
{
    step();
}

void GraphicEngine::_init()
{
    _loadTextures();

    _tree->init();
    _scene->init();
    _viewing->init();
    _mouse->init();
}

void GraphicEngine::_step()
{
    repaint();
}

void GraphicEngine::initializeGL()
{
    init();
}

void GraphicEngine::paintGL()
{
    _tree->step();

    if (_mouse->leftClick()) {
	VecXf move = _mouse->mov();
	move.setY(-move.y());

	_viewing->moveCamera(move);
    }

    _viewing->step();
    _mouse->step();

    _scene->step();
}

void GraphicEngine::resizeGL()
{
    _viewing->sizeViewport(width(), height());
}

void GraphicEngine::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
	QApplication::quit();
    else if (event->key() == Qt::Key_Space)
	_viewing->centering();
}

void GraphicEngine::mouseMoveEvent(QMouseEvent *event)
{
    QPointF pos = event->posF();

    _mouse->setPos(VecXf(pos.x(), pos.y()));
    _mouse->setLeftClick(event->buttons() == Qt::LeftButton);

//    if (event->buttons() == Qt::LeftButton) {
//	_tree->lookAt(vec);
//    }

/*    else {
	Vec2f loc = _screen2pic(event->x(), event->y());
	_tree->locMouse(loc);
    }

    _lastMouseEvent = pos;*/
}

void GraphicEngine::resizeGL(int width, int height)
{
    _viewing->sizeViewport(width, height);
}

void GraphicEngine::_loadTextures()
{
    QImage textureNode("Resources/file.png");
    QImage textureGlow("Resources/bloom.png");
    QImage textureEdge("Resources/beam.png");

    _scene->setTextureNode(bindTexture(textureNode, GL_TEXTURE_2D,
				       QGLContext::MipmapBindOption));
    _scene->setTextureGlow(bindTexture(textureGlow, GL_TEXTURE_2D,
				       QGLContext::MipmapBindOption));
    _scene->setTextureEdge(bindTexture(textureEdge, GL_TEXTURE_2D,
				       QGLContext::MipmapBindOption));
}
