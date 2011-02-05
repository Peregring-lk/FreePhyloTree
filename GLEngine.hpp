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


#ifndef _GL_ENGINE_
#define _GL_ENGINE_

#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWebView>

#include <string>

#include "PhyloTree.hpp"

namespace fpt
{
  class GLEngine : public QGLWidget
  {
    Q_OBJECT

  public:
    GLEngine(PhyloTree *tree);
    ~GLEngine();

    void viewPage(PhyloNode *node);

  public slots:
    void animate();

  private:
    PhyloTree *_tree;
    QPointF _lastMouseEvent;

    QWebView _webView;
    const std::string _nameWeb;
    float _pctWWSize;
    float _finalWWWidth;
    float _finalWWHeight;
    float _smoothResizeWW;

    float _actualWidth;
    float _actualHeight;
    float _smoothResizeViewport;

    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void keyPressEvent(QKeyEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    Vec2f _screen2pic(int x, int y);
    void _reloadViewport();
    void _reloadWebView();
  };
}

#endif
