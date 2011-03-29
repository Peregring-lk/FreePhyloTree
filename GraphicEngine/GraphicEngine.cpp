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
#include <QWebFrame>

#include "GraphicEngine.hpp"

#include "Scene.hpp"
#include "Viewing.hpp"

using namespace std;
using namespace fpt;

GraphicEngine::GraphicEngine(const Name& root)
    : _webView(this), _nameWeb("http://es.wikipedia.org/wiki/")
{
    _parser = new ParserTree("http://species.wikimedia.org/");
}

GraphicEngine::~GraphicEngine()
{
    deleteTexture(_scene->textureNode());
    deleteTexture(_scene->textureGlow());
    deleteTexture(_scene->textureEdge());
//    deleteTexture(_helpDialog->texture());

    delete _viewing;
    delete _scene;
    delete _mouse;
    delete _parser;
    delete _tree;
    delete _helpDialog;
}

void GraphicEngine::animate()
{
    step();
}

void GraphicEngine::_init()
{
    setFocus(Qt::MouseFocusReason);
    setMouseTracking(true);
    resize(600, 480);

    _ratioKey = 10;
    _controlKey = false;
    _shiftKey = false;

    PhyloNode *node = _parser->expand("Neomura", "Neomura");

    _tree = new PhyloTree("Neomura", node, 3, 40, 200, 2);

    node->showName(true);

    _viewing = new Viewing(_tree, width(), height());
    _mouse = new Mouse(_tree, _viewing);
    _scene = new Scene(_tree, _mouse);
    _search = new Search("Search", this);

    _helpDialog = new HelpDialog(_viewing, 0.6f);

    _loadTextures();

    _tree->init();
    _scene->init();

    _viewing->init();
    _mouse->init();
    _search->init();
    _helpDialog->init();

    _webView.hide();
    _resizeWebView();
}

void GraphicEngine::_step()
{
    if (_search->newSearch()) {
	PhyloNode *node = _tree->phyloNode(_search->actualSearch());

	if (node == NULL) {
	    node = _parser->expand(_search->actualSearch(),
				   _search->actualUrl());

	    if (node != NULL) {
		_tree->reboot(node->name(), node);
		_tree->init();
		_search->check(true);
	    }
	    else
		_search->check(false);
	}

	if (node != NULL)
	    node->showName(true);

	_search->reboot();
    }

    repaint();
    _resizeWebView();
}

void GraphicEngine::_viewPage(PhyloNode *node)
{
    if (node != NULL) {
	string url = _nameWeb + node->url();
	_webView.load(QUrl(url.c_str()));

	if (_webView.isHidden()) {
	    if (_helpDialog->isVisible())
		_helpDialog->setShow(false);

	    _webView.show();
	}
    }
    else if (_webView.isVisible()) {
	_webView.hide();
	_webView.clearFocus();
    }
}

void GraphicEngine::_resizeWebView()
{
    int w = 0.9 * width();
    int h = 0.9 * height();

    _webView.resize(w, h);
    _webView.move((width() - w) / 2,
		  (height() - h) / 2);
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
    _search->step();

    _helpDialog->step();
}

void GraphicEngine::resizeGL()
{
    _viewing->sizeViewport(width(), height());
}

void GraphicEngine::keyPressEvent(QKeyEvent *event)
{
    if (_controlKey) {
	if (event->key() == Qt::Key_F)
	    if (_search->isVisible()) {
		_search->setFocus();
		_search->selectAll();
	    }
	    else
		_search->reactivate();
	else if (event->key() == Qt::Key_S)
	    grabFrameBuffer().save("capture.png");
	else if (event->key() == Qt::Key_A)
	    _scene->describeAllNodes(!_scene->describedNodes());
    }
    else if (event->key() == Qt::Key_F4)
	if (_search->isVisible())
	    _search->hide();
	else
	    _search->reactivate();
    else if (event->key() == Qt::Key_F1)
	_helpDialog->setShow(!_helpDialog->isVisible());
    else if (event->key() == Qt::Key_Escape) {
	if (_webView.isVisible())
	    _webView.hide();
	else
	    QApplication::quit();
    }
    else if (event->key() == Qt::Key_Space)
	_viewing->centering();
    else if (event->key() == Qt::Key_Up)
	_viewing->moveCamera(VecXf(0, _ratioKey));
    else if (event->key() == Qt::Key_Down)
	_viewing->moveCamera(VecXf(0, -_ratioKey));
    else if (event->key() == Qt::Key_Right)
	_viewing->moveCamera(VecXf(_ratioKey, 0));
    else if (event->key() == Qt::Key_Left)
	_viewing->moveCamera(VecXf(-_ratioKey, 0));
    else if (event->key() == Qt::Key_Control)
	_controlKey = true;
    else if (event->key() == Qt::Key_Shift)
	_shiftKey = true;
}

void GraphicEngine::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control)
	_controlKey = false;
    else if (event->key() == Qt::Key_Shift)
	_shiftKey = false;
}

void GraphicEngine::mousePressEvent(QMouseEvent *event)
{
    _search->clearFocus();

    PhyloNode *node = _mouse->actualNode();

    if (node != NULL && _controlKey) {
	node->showName(!node->showedName());

	if (!node->showedName())
	    _mouse->clean();
    }
}

void GraphicEngine::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
	PhyloNode *node = _mouse->actualNode();

	if (node != NULL) {
	    if (_controlKey) {
		_tree->crib(node);
		_tree->prepareColor(NULL);

		node->showName(true);
	    }
	    else if (_shiftKey) {
		node->clear();
		_tree->clearNode(node);
		node->showName(false);
	    }
	    else {
		_parser->expand(node);
		_tree->prepareLoc(node);
		_tree->prepareColor(node);
		node->showName(true);
	    }
	}
    }
    else if (event->button() == Qt::RightButton)
	_viewPage(_mouse->actualNode());
}

void GraphicEngine::mouseMoveEvent(QMouseEvent *event)
{
    QPointF pos = event->posF();

    _mouse->setPos(VecXf(pos.x(), pos.y()));
    _mouse->setLeftClick(event->buttons() == Qt::LeftButton);
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
    QImage textureHelp("Resources/help.png");

    _scene->setTextureNode(bindTexture(textureNode, GL_TEXTURE_2D,
				       QGLContext::MipmapBindOption));
    _scene->setTextureGlow(bindTexture(textureGlow, GL_TEXTURE_2D,
				       QGLContext::MipmapBindOption));
    _scene->setTextureEdge(bindTexture(textureEdge, GL_TEXTURE_2D,
				       QGLContext::MipmapBindOption));
    _helpDialog->setTexture(bindTexture(textureHelp, GL_TEXTURE_2D,
					QGLContext::MipmapBindOption));
}
