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

/*! \file FreePhyloTree.hpp
 *  \brief Archivo que define a la clase \c fpt::QFreePhyloTree.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2011
 *  \version 0.7
 *  \since 0.7
 */

#ifndef _FPT_FREE_PHYLO_TREE_
#define _FPT_FREE_PHYLO_TREE_

#include <QApplication>
#include <QTimer>

#include "GraphicEngine/GraphicEngine.hpp"

/*! \namespace fpt
 *  \brief Espacio de nombres de FreePhyloTree.
 */
namespace fpt
{
    /*! \class QFreePhyloTree
     *  \brief Clase principal de FreePhyloTree.
     *
     *  \c QFreePhyloTree es una \c Qt::QApplication, de la librería Qt y se
     *  encarga de construir, inicializar (\c QFreePhyloTree::init) y
     *  ejecutar la aplicación (\c exec).
     *
     *  Solo posee una función propia, \c init. Las restantes
     *  funciones de \c QFreePhyloTree son las funciones de \c
     *  QApplication. Las única función de \c QApplication que se usa
     *  es la función \c exec, llamada desde la función \c main.
     *
     *  \c QFreePhyloTree controla el \c framerate de la aplicación,
     *  la gestión de eventos, y se encarga de \c inicializar a la
     *  aplicación vía \c fpt::QFreePhyloTree::_glEngine.
     *
     */
    class QFreePhyloTree : public QApplication
    {
    public:
	/*! \fn QFreePhyloTree(int argc, char **argv)
	 *  \brief Función principal del juego.
	 *
	 *  \param argc Número de argumentos.
	 *  \param argv Lista de argumentos.
	 *
	 *  Construye a \c Qt::QApplication, \c
	 *  QFreePhyloTree::_glEngine y a \c QFreePhyloTree::_qTimer.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	QFreePhyloTree(int argc, char **argv);

	/*! \fn ~QFreePhyloTree()
	 *  \brief Destruye a la aplicación.
	 *
	 *  Destruye recursivamente a todas las clases de la aplicación.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	~QFreePhyloTree();

	/*! \fn void init()
	 *  \brief Inicializa a la aplicación.
	 *
	 *  Ésta función sólo se encarga de conectar al temporizador,
	 *  \c QFreePhyloTree::_qTimer, a la función \c animate de \c
	 *  QFreePhyloTree::_glEngine. La función \c _animate representa un paso de
	 *  ejecución. El temporizador se configura a 40 milisegundos,
	 *  de modo que se en un segundo la función \c animate es
	 *  llamada 25 veces, para tener un \a framerate de 25, es
	 *  decir, 25 fotogramas por segundo.
	 *
	 *  También muestra al widget \c _glEngine. \c fpt::GraphicEngine
	 *  es una especialización de \c Qt::QGLWidget, un widget
	 *  openGL. Los widget, por defecto, son ocultos. Para
	 *  mostrarlos se llama a la función \c show del widget (no
	 *  está sobrecargada en \c QGLWidget). La función \c show
	 *  llama a la función de \c QGLWidget, \c initializeGL, y
	 *  ésta a su vez, inicializa recursivamente a todas las
	 *  clases del juego. Para comprender el por qué de ésta
	 *  cadena de funciones-puente, véase la documentación de la
	 *  clase \c fpt::GraphicEngine.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	void init();

    private:
	/*! \var GraphicEngine *_glEngine
	 *  \brief Puntero a un objeto \c fpt::GraphicEngine. Es el
	 *  motor gráfico de la aplicación.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	GraphicEngine *_glEngine;

	/*! \var QTimer _qTimer
	 *  \brief Temporizador de la aplicación. Controla el \a
	 *  framerate.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	QTimer _qTimer;
    };
}

#endif
