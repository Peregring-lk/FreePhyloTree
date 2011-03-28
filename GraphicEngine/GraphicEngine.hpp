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

#ifndef _FPT_GRAPHIC_ENGINE_
#define _FPT_GRAPHIC_ENGINE_

#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWebView>

#include <string>

#include "ParserTree.hpp"
#include "Scene.hpp"
#include "Viewing.hpp"
#include "Mouse.hpp"
#include "Search.hpp"
#include "HelpDialog.hpp"

namespace fpt
{
    /*! \class GraphicEngine
     *  \brief Motor gráfico de la aplicación.
     *
     *  Clase que controla la parte no-lógica de FreePhyloTree, que no
     *  es más que un compuesto del resto de objetos del grupo gráfico
     *  (\c Viewing, \c ParserTree, \c Mouse y \c Scene), delegando en
     *  ellos las funciones necesarias.
     *
     *  Es, a su vez, un \c QGLWidget de \c Qt, ya que el motor gráfico se sienta
     *  sobre openGL, y contiene un \c QWebKit para visualizar los
     *  artículos pedidos de wikipedia de forma nativa a la aplicación.
     *
     */
    class GraphicEngine : public QGLWidget, public Strategy
    {
	Q_OBJECT

    public:
	GraphicEngine(const Name& root);
	~GraphicEngine();

    public slots:
	void animate();

    protected:
	void _init();
	void _step();

    private:
	PhyloTree *_tree;
	ParserTree *_parser;
	Viewing *_viewing;
	Scene *_scene;
	Mouse *_mouse;
	Search *_search;
	HelpDialog *_helpDialog;

	bool _controlKey;
	bool _shiftKey;

	QWebView _webView;
	std::string _nameWeb;
	float _ratioKey;

	void initializeGL();
	void paintGL();
	void resizeGL();

	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void resizeGL(int width, int height);

	void _loadTextures();
	void _viewPage(PhyloNode *node);
	void _resizeWebView();
    };
}

#endif
