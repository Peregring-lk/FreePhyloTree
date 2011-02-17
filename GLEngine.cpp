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
#include "GLEngine.hpp"

using namespace std;
using namespace fpt;

GLEngine::GLEngine(PhyloTree *tree)
    : _tree(tree), _webView(this),
      _nameWeb("http://es.wikipedia.org/wiki/")
{
    setMouseTracking(true);

    _smoothResizeViewport = 0.1;
    _smoothResizeWW = 0.2;

    _actualWidth = width();
    _actualHeight = height();

    _pctWWSize = 0.9;
    resizeGL(_actualWidth, _actualHeight);

    _webView.hide();
}

GLEngine::~GLEngine()
{
    delete _tree;
}

void GLEngine::viewPage(PhyloNode *node)
{
    if (node != NULL) {
	string dir = _nameWeb + node->name();
	_webView.load(QUrl(dir.c_str()));

	if (_webView.isHidden())
	    _webView.show();
    }
    else if (_webView.isVisible()) {
	_webView.hide();
	_webView.clearFocus();
    }
}

void GLEngine::animate()
{
    repaint();
    _reloadViewport();
    _reloadWebView();
}

void GLEngine::initializeGL()
{
    _tree->initSignal(this);
}

void GLEngine::paintGL()
{
    _tree->draw();
}

void GLEngine::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
	_tree->gotoRoot();
    else if (event->key() == Qt::Key_Escape) {
	if (_webView.isVisible())
	    viewPage(NULL);
	else
	    QApplication::quit();
    }
}

void GLEngine::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
	_tree->cribNode(_screen2pic(event->x(), event->y()));
    else if (event->button() == Qt::RightButton)
	viewPage(_tree->actualNode());
}

void GLEngine::mouseMoveEvent(QMouseEvent *event)
{
    QPointF pos = event->posF();

    if (event->buttons() == Qt::LeftButton) {
	Vec3f vec = Vec3f(pos.x() - _lastMouseEvent.x(),
			  _lastMouseEvent.y() - pos.y());

	_tree->lookAt(vec);
    }
    else {
	Vec3f loc = _screen2pic(event->x(), event->y());
	_tree->locMouse(loc);
    }

    _lastMouseEvent = pos;
}

void GLEngine::resizeGL(int width, int height)
{
    _finalWWWidth = width * _pctWWSize;
    _finalWWHeight = height * _pctWWSize;
}

Vec3f GLEngine::_screen2pic(int x, int y)
{
    Vec3f inf = _tree->infPic();
    Vec3f sup = _tree->supPic();

    float desplX = ((float)x / width()) * (sup.x() - inf.x());
    float desplY = (1 - (float)y / height()) * (sup.y() - inf.y());

    return Vec3f(inf.x() + desplX,
		 inf.y() + desplY);
}

void GLEngine::_reloadViewport()
{
    bool change = false;

    if ((int)_actualWidth != width()) {
	float difWidth = _actualWidth - width();
	_actualWidth -= difWidth * _smoothResizeViewport;
	change = true;
    }

    if ((int)_actualHeight != height()) {
	float difHeight = _actualHeight - height();
	_actualHeight -= difHeight * _smoothResizeViewport;
	change = true;
    }

    if (change)
	glViewport(0, 0, _actualWidth, _actualHeight);
}

void GLEngine::_reloadWebView()
{
    bool change = false;

    int wwWidth = _webView.width();
    int wwHeight = _webView.height();

    if ((int)_finalWWWidth != wwWidth) {
	float dif = wwWidth - _finalWWWidth;
	wwWidth -= dif * _smoothResizeWW;
	change = true;
    }

    if ((int)_finalWWHeight != wwHeight) {
	float dif = wwHeight - _finalWWHeight;
	wwHeight -= dif * _smoothResizeWW;
	change = true;
    }

    if (true){
	_webView.resize(wwWidth, wwHeight);

	_webView.move((width() - wwWidth) / 2,
		      (height() - wwHeight) / 2);
    }
}
