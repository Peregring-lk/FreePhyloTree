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

/*! \file Scene.hpp
 *  \brief Fichero que define a la clase \c fpt::Scene.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2011
 *  \version 0.7
 *  \since 0.7
 */
#ifndef _FPT_SCENE_
#define _FPT_SCENE_

#include <vector>
#include <GL/gl.h>
#include <FTGL/ftgl.h>

#include "../PhyloTree.hpp"
#include "Mouse.hpp"

namespace fpt
{
    /*! \class Scene
     *  \brief Clase que renderiza el árbol \c fpt::PhyloTree.
     *
     *  Ésta clase, fundamentalmente, se dedica a renderizar el árbol
     *  (\c PhyloTree) y a mostrar el texto de los nodos requeridos.
     *
     *  \sa Mouse
     *
     *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
     *  \date 04/2011
     *  \version 0.7
     *  \since 0.7
     */
    class Scene : public Strategy
    {
    public:
        /*! \fn Scene(PhyloTree *tree, Mouse *mouse)
	 *  \brief Constructor de la clase.
	 *
	 *  \param tree Referencia al árbol (éste es
	 *  creado en \c fpt::GraphicEngine).
	 *  \param mouse Referencia al ratón (éste es creado en \c
	 *  fpt::GraphicEngine).
	 *
	 *  El único objeto que se crea es la fuente usada para
	 *  mostrar los nombres de los clados.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	Scene(PhyloTree *tree, Mouse *mouse);

        /*! \fn ~Scene()
	 *  \brief Destructor de la clase.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	~Scene();

        /*! \fn bool changed() const
	 *  \brief Función que indica si la escena ha sufrido cambios.
	 *
	 *  Esta función solo es un \a wrapper de la función \c
	 *  PhyloTree::changed, ya que la escena solo cambia si cambia
	 *  el árbol.
	 *
	 *  \sa Strategy.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	bool changed() const;

        /*! \fn bool describedNodes() const
	 *  \brief Función que indica si la escena está en modo
	 *  mostrar nodos.
	 *
	 *  Si el usuario pulsa la combinación de teclas \c Ctrl + \c
	 *  A, \c fpt::GraphicEngine llama a la función \c
	 *  Scene::describeAllNodes para indicar que deben mostrarse
	 *  los nombres de todos los taxones presentes en el árbol.
	 *
	 *  Ésta función devuelve si actualmente se están mostrando
	 *  todos los nombres o no.
	 *
	 *  \sa Strategy.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	bool describedNodes() const;

	/*! \fn GLuint textureNode() const
	 *  \brief Devuelve el identificador de la textura usada para
	 *  dibujar nodos.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	GLuint textureNode() const;

	/*! \fn GLuint textureGlow() const
	 *  \brief Devuelve el identificador de la textura usada para
	 *  dibujar la iluminación de los nodos.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	GLuint textureGlow() const;

	/*! \fn GLuint textureGlow() const
	 *  \brief Devuelve el identificador de la textura usada para
	 *  dibujar las aristas.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	GLuint textureEdge() const;

	/*! \fn GLuint setTextureNode(GLuint id)
	 *  \brief Indica cuál es la textura que ha de usarse para
	 *  dibujar nodos.
	 *
	 *  \param id Identificador de la textura.
	 *
	 *  Las texturas son creadas y cargadas en la clase \c
	 *  fpt::GraphicEngine, ya que él es, en sí, el motor
	 *  openGL. Ésta clase sólo se encarga de dibujar.
	 *
	 *  Una vez creada la textura, el identificador de la textura
	 *  es recibido mediante esta función.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	void setTextureNode(GLuint id);

	/*! \fn GLuint setTextureGlow(GLuint id)
	 *  \brief Indica cuál es la textura que ha de usarse para
	 *  dibujar el iluminado de los nodos.
	 *
	 *  \param id Identificador de la textura.
	 *
	 *  \sa setTextureNode
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	void setTextureGlow(GLuint id);

	/*! \fn GLuint setTextureEdge(GLuint id)
	 *  \brief Indica cuál es la textura que ha de usarse para
	 *  dibujar las aristas.
	 *
	 *  \param id Identificador de la textura.
	 *
	 *  \sa setTextureNode
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	void setTextureEdge(GLuint id);

	/*! \fn void describeAllNodes(bool describe)
	 *  \brief Pide a la clase que dibuje los nombres de todos los
	 *  nodos.
	 *
	 *  \param describe Indica si se desean mostrar o no los
	 *  nombres de todos los nodos, es decir, activa/desactiva la
	 *  opción.
	 *
	 *  \sa describedNodes
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	void describeAllNodes(bool describe = true);

    protected:
	void _init();
	void _step();

    private:
        /*! \var vector<PhyloNode*> _seenNodes
	 *  \brief Nodos cuyos nombres han de mostrarse.
	 *
	 *  El usuario puede, haciendo \c Ctrl + \c click en un nodo,
	 *  mostrar su nombre. En éste vector de guardan todos los
	 *  nodos cuyos nombres deben visualizarse.
	 *
	 *  \note Si está activa el modo de visualización de todos los
	 *  nombres (\c Scene::describedNodes), esta variable es
	 *  ignorada. Así, al desactivar el modo, se vuelven a mostrar
	 *  los nodos que antes fueron marcados.
	 *
	 *  \sa describedNodes
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	std::vector<PhyloNode*> _seenNodes;

        /*! \var PhyloTree *_tree
	 *  \brief Referencia al árbol taxonómico.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	PhyloTree *_tree;

        /*! \var Mouse *_mouse
	 *  \brief Referencia al ratón.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	Mouse *_mouse;

        /*! \var FTFont *_font
	 *  \brief Fuente usada para mostrar los nombres.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	FTFont *_font;

        /*! \var GLuint _textureIDnode
	 *  \brief Identificador de la textura para dibujar nodos.
	 *
	 *  \sa setTextureNode
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	GLuint _textureIDnode;

        /*! \var GLuint _textureIDglow
	 *  \brief Identificador de la textura para dibujar la
	 *  iluminación de cada nodo.
	 *
	 *  \sa setTextureGlow
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	GLuint _textureIDglow;

        /*! \var GLuint _textureIDedge
	 *  \brief Identificador de la textura para dibujar las
	 *  aristas.
	 *
	 *  \sa setTextureEdge
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	GLuint _textureIDedge;

        /*! \var bool _initTexNode
	 *  \brief Si la textura para dibujar nodos ha sido
	 *  inicializada.
	 *
	 *  \sa _textureIDnode;
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	bool _initTexNode;

        /*! \var bool _initTexNode
	 *  \brief Si la textura para dibujar la iluminación de cada
	 *  nodo ha sido inicializada.
	 *
	 *  \sa _textureIDglow;
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	bool _initTexGlow;

        /*! \var bool _initTexEdge
	 *  \brief Si la textura para dibujar aristas ha sido
	 *  inicializada.
	 *
	 *  \sa _textureIDedge;
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	bool _initTexEdge;

        /*! \var float _radiusNode
	 *  \brief Radio de cada nodo.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	float _radiusNode;

        /*! \var float _weightEdge
	 *  \brief Diámetro de las aristas.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	float _weightEdge;

        /*! \var bool _describeNodes
	 *  \brief Si está activa la visualización de los nombres de
	 *  todos los nodos.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	bool _describeNodes;

	void _drawTree();
	void _drawNode(PhyloNode *node);
	void _drawGlow(PhyloNode *node);
	void _drawEdge(PhyloNode *source, PhyloNode *target);

	void _drawSquare(PhyloNode *node, float side, GLuint tex);
	void _setColor(PhyloNode *node);

	void _drawText(PhyloNode *node);
	void _drawHelp();
    };
}

#endif
