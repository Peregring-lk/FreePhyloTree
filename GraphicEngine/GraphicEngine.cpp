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
    : _tree(tree)
{
    _viewing = new Viewing(_tree, width(), height());
    _scene = new Scene(_tree);

    setMouseTracking(true);
}

GraphicEngine::~GraphicEngine()
{
    delete _viewing;
    delete _scene;
}

void GraphicEngine::init()
{
    _loadTextures();

    _scene->init();
    _tree->init();
    _viewing->init();
}

void GraphicEngine::step()
{
    repaint();
}

void GraphicEngine::initializeGL()
{
    init();
}

void GraphicEngine::paintGL()
{
    _viewing->step();
    _scene->step();
    _tree->step();
}

void GraphicEngine::resizeGL()
{
    _viewing->sizeViewport(width(), height());
}

void GraphicEngine::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
	QApplication::quit();
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
