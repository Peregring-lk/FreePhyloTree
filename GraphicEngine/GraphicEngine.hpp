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

/*! \file GraphicEngine.hpp
 *  \brief Archivo que define a la clase \c fpt::GraphicEngine.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2011
 *  \version 0.7
 *  \since 0.7
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
     *  (\c fpt::Viewing, \c fpt::ParserTree, \c fpt::Mouse, \c
     *  fpt::Scene, \c fpt::HelpDialog y \c Search), delegando en
     *  ellos las funciones necesarias.
     *
     *  Se encarga de manejar la fase de inicialización y cada uno de
     *  los pasos de la animación de todas las clases, es decir,
     *  maneja todas las clases \c fpt::Strategy de la aplicación,
     *  clase del que GraphicEngine también hereda.
     *
     *  Es, a su vez, un \c QGLWidget de \c Qt, ya que el motor gráfico se sienta
     *  sobre openGL, y contiene un \c QWebKit para visualizar los
     *  artículos pedidos de \a wikipedia de forma nativa a la aplicación.
     *
     *  Ésta clase controla las dos fases principales en las que se
     *  compone la ejecución de la aplicación: la fase de
     *  inicialización y la animación.
     *
     *  La fase de inicialización se ejecuta de la siguiente forma: en
     *  la función \c QFreePhyloTree::run() se muestra el widget
     *  openGL (mediante una llamada a la función \c
     *  QGLWidget::show()). QGLWidget llama entonces a la función
     *  protegida QGLWidget::initializeGL. Ésta función virtual no
     *  hace nada si no se redefine. La versión sobrecargada,
     *  GraphicEngine::initializeGL, es la que llama a la función
     *  Strategy::init, y comienza entonces el proceso de
     *  inicialización, inicializando a su vez al resto de clases del
     *  juego.
     *
     *  La animación se controla de la siguiente
     *  forma. En la clase \c fpt::QFreePhyloTree se conecta el
     *  temporizador \c QFreePhyloTree::_qTimer a la función \c
     *  GraphicEngine::animate. \c animate solo reenvía el mensaje a
     *  la función \c Strategy::step. Ésto es debido, por un lado, a
     *  que el mecanismo de signal-slots de Qt requiere de una función
     *  pública para realizar las conexiones, y además, la clase que
     *  haga uso de ese mecanismo debe incluir en su definición la
     *  macro Q_OBJECT. Podría usarse la propia función \c step (que
     *  también es pública) para
     *  realizar dicha conexión, pero eso implicaría que la clase \c
     *  fpt::Strategy sea la que contiene dicha macro, pero esa opción
     *  no es adecuada debido a que \c GraphicEngine es la única clase
     *  que necesita usar dicho mecanismo.
     *
     *  \note No confundir la función step con la función
     *  GraphicEngine::_step.
     *
     *  \sa Strategy
     *
     *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
     *  \date 04/2011
     *  \version 0.7
     *  \since 0.7
     */
    class GraphicEngine : public QGLWidget, public Strategy
    {
	Q_OBJECT

    public:
	/*! \fn GraphicEngine(const Name& root)
	 *  \brief Constructor de la clase GraphicEngine.
	 *
	 *  \param root Nombre del clado de presentación.
	 *
	 *  El clado de presentación es aquel que se presenta cuando
	 *  la aplicación se ejecuta.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	GraphicEngine(const Name& root);

        /*! \fn ~GraphicEngine()
	 *  \brief Destructor de la clase y los objetos que lo
	 *  componen.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	~GraphicEngine();

    public slots:
        /*! \fn void animate()
	 *  \brief Función que controla a la animación.
	 *
	 *  Ésta función está conectada al temporizador
	 *  \c QFreePhyloTree::_qTimer, y es llamada 25 veces por
	 *  segundo (cada 40 milisegundos). Se encarga de redirigir la
	 *  llamada a la función \c Strategy::init.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	void animate();

    protected:
        /*! \fn void _init()
	 *  \brief Función que inicializa a la aplicación.
	 *
	 *  Ésta función, en esencia, inicializa a todos los objetos
	 *  que contiene la clase, llamando a las correspondientes
	 *  funciones \c Strategy::init de cada uno de ellos.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	void _init();

        /*! \fn void _step()
	 *  \brief Función que ejecuta un paso de la animación.
	 *
	 *  Ésta función, primero mira si hay algunas búsqueda
	 *  nueva. En caso afirmativo modifica el árbol en
	 *  consecuencia. Acto seguido, llama a la función \c
	 *  GraphicEngine::paintGL.
	 *
	 *  En realidad, se llama a la función \c QGLWidget::repaint,
	 *  y ésta a su vez llama a la función \c
	 *  QGLWidget::paintGL. \c paintGL, al igual que inicializeGL,
	 *  es una función virtual que no hace nada a no ser que se
	 *  reimplemente. La versión sobrecargada, \c
	 *  GraphicEngine::paintGL, llama a las funciones \c step del
	 *  resto de objetos para que cada uno continúe con su
	 *  animación.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	void _step();

    private:
	/*! \var PhyloTree *_tree
	 *  \brief Árbol principal del juego.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	PhyloTree *_tree;

	/*! \var ParserTree *_parser
	 *  \brief Objeto que construye el árbol realizando llamadas a
	 *  \a wikispecies.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	ParserTree *_parser;

	/*! \var Viewing *_viewing
	 *  \brief Objeto que maneja el visionado de la escena.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	Viewing *_viewing;

	/*! \var Scene *_scene
	 *  \brief Objeto que se encarga de renderizar el árbol.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	Scene *_scene;

	/*! \var Mouse *_mouse
	 *  \brief Objeto que se controla la posición y las acciones
	 *  del ratón.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	Mouse *_mouse;

	/*! \var Search *_search
	 *  \brief Buscador.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	Search *_search;

	/*! \var HelpDialog *_helpDialog
	 *  \brief Objeto que renderiza el menú de ayuda de la
	 *  aplicación.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	HelpDialog *_helpDialog;

	/*! \var bool _controlKey
	 *  \brief Variable que controla si se ha pulsado la tecla
	 *  \c Ctrl.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	bool _controlKey;

	/*! \var bool _shiftKey
	 *  \brief Variable que controla si se ha pulsado la tecla
	 *  \c Shift.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	bool _shiftKey;

	/*! \var QWebView _webView
	 *  \brief Explorador integrado.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	QWebView _webView;

	/*! \var string _nameWeb
	 *  \brief Dirección (\c url) de wikipedia.
	 *
	 *  Cuando un usuario desea visualizar un artículo, se
	 *  concatena el nombre del clado a la dirección de wikipedia,
	 *  y ésta cadena es la que se pide a \c
	 *  GraphicEngine::_webView que visualice.
	 *
	 *  \note Los artículos de wikipedia tienen la dirección
	 *  http://es.wikipedia.org/wiki/nombre_artículo.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	std::string _nameWeb;

	/*! \var float _ratioKey
	 *  \brief Fuerza del movimiento de la cámara con las teclas
	 *  de dirección.
	 *
	 *  Ésta variable indica qué proporción hay entre una
	 *  pulsación de una tecla de movimiento, →, ↑, ← y ↓, y el
	 *  desplazamiento de cámara. A un mayor valor de ésta
	 *  variable, más rápida se moverá la cámara cuando se pulse
	 *  alguna de las teclas de dirección. Está inicializada al
	 *  valor 20.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
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
