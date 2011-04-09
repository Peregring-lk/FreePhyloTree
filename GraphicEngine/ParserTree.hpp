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

/*! \file ParserTree.hpp
 *  \brief Fichero que define a la clase \c fpt::ParserTree.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2011
 *  \version 0.7
 *  \since 0.7
 */
#ifndef _FPT_PARSER_TREE_
#define _FPT_PARSER_TREE_

#include <curl/curl.h>
#include "../PhyloTree.hpp"

namespace fpt
{
    /*! \class ParserTree
     *  \brief Clase que contruye el árbol.
     *
     *  Ésta clase explora en el wiki \a wikispecies el árbol
     *  taxonómico a visualizar, parseando cada uno de los ártilos de
     *  wikispecies para extraer los subclados de un clado dado.
     *
     *  Cada vez que se pide expandir un nodo, el número niveles a
     *  expandir es controlado mediante parámetros, dado que construir
     *  el árbol entero es poco tratable, por cuestión de tiempo de
     *  inicialización y de comodidad/eficiencia en la interacción con
     *  el árbol. El árbol podría contener miles de nodos, cuando la
     *  mayoría de ellos al usuario no les interesan.
     *
     *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
     *  \date 04/2011
     *  \version 0.7
     *  \since 0.7
     */
    class ParserTree
    {
    public:
        /*! \fn ParserTree(string wikiParh, unsigned levelsStep,
	 *      unsigned maxSons)
	 *  \brief Constructor de la clase \c fpt::ParserTree.
	 *
	 *  \param wikiPath Dirección del wiki a explorar
	 *  (wikispecies).
	 *  \param levelsStep Profundidad máxima de expansión (por
	 *  defecto, 2).
	 *  \param maxSons Número máximo de hijos de expansión (por
	 *  defecto, 20).
	 *
	 *  Ésta función permite explorar \a wikispecies para
	 *  construir el árbol taxonómico. La profundidad máxima
	 *  indica cuántas consultas recursivas han de hacerse. Un
	 *  nivel de 2 indica que, de cada clado a explorar, solo se
	 *  deben explorar 2 niveles más como máximo.
	 *
	 *  Si el número de hijos de un clado es demasiado grande,
	 *  construir todos los nietos puede ser muy ineficiente, ya
	 *  que deben hacerse muchas llamadas: uno por cada hijo. La
	 *  variable \c maxSons evita que se expanda un nodo con
	 *  demasiados hijos, que haría al árbol poco atractivo y
	 *  provocaría mucho tiempo de espera, ya que cada consulta
	 *  consume tiempo.
	 *
	 *  La librería usada para realizar las consultas es \c libcurl,
	 *  y ésta clase es la única clase ocupada de su manejo.
	 *
	 *  \sa _curl
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	ParserTree(std::string wikiPath,
		   unsigned levelsStep = 2, unsigned maxSons = 20);

	/*! \fn ~ParserTree()
	 *  \brief Destructor de la clase.
	 *
	 *  Se encarga de destruir adecuadamente a la librería \c
	 *  libcurl.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	~ParserTree();

	/*! \fn PhyloNode* expand(const string& name, const string& url)
	 *  \brief Crea y expande un nodo.
	 *
	 *  \param name Nombre del taxón.
	 *  \param url Dirección del taxón en \a wikispecies.
	 *
	 *  \return Devuelve el árbol construido, cuya raíz es el
	 *  taxón \c name, con una profundidad de \c
	 *  ParserTree::_levelsStep.
	 *
	 *  Para construir cualquier nodo, éste necesita un nombre,
	 *  pero el nombre no tiene por qué coincidir con la dirección
	 *  del ártilo en \c wikispecies. Con la dirección del
	 *  artículo, se hace la consulta, y con el nombre del clado
	 *  se crea el nodo, y así sucesivamente para cada uno de sus
	 *  hijos.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	PhyloNode* expand(const std::string& name,
			  const std::string& url);

	/*! \fn bool expand(PhyloNode *node)
	 *  \brief Expande un nodo ya creado.
	 *
	 *  \param node Nodo a expandir.
	 *
	 *  \return Si la expansión ha tenido o no éxito.
	 *
	 *  Ésta función permite expandir un nodo que sólo está
	 *  expandido un nivel, para expandir el siguiente.
	 *
	 *  \note Si un nodo tiene más de \c ParserTree::_levelsStep
	 *  nodo, igualmente no se expandirá el segundo nivel.
	 *
	 *  \note Ésta función sirve para la siguiente situación: si
	 *  expandimos un nodo dos niveles, el usuario podría querer
	 *  expandir a un hijo, que solo tendrá expandido un nivel
	 *  (que será el segundo y último nivel respecto a su padre).
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	bool expand(PhyloNode *node);

    private:
        /*! \var CURL *_curl
	 *  \brief Variable para la comunicación \c http.
	 *
	 *  Ésta variable es la principal de la librería \a
	 *  libcurl. Si no se inicializa correctamente esta variable,
	 *  con la función de \a libcurl \c curl_easy_init(), no se
	 *  puede realizar una comunicación \c http.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	CURL *_curl;

        /*! \var Node *_actualNode
	 *  \brief Nodo ha procesar actualmente.
	 *
	 *  Ésta variable es una variable auxiliar de comunicación
	 *  entre varias funciones mientras se expande el árbol. Es la
	 *  raíz del árbol a expandir.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	Node *_actualNode;

        /*! \var const unsigned _levelsStep
	 *  \brief Número máximo de niveles a expandir.
	 *
	 *  \sa ParserTree()
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	const unsigned _levelsStep;

        /*! \var const unsigned _maxSons
	 *  \brief Número de hijos máximo a expandir.
	 *
	 *  \sa ParserTree()
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	const unsigned _maxSons;

        /*! \var struct curl_slist *_headerlist
	 *  \brief Variable que almacena una lista de variables
	 *  necesarias para inicializar la comunicación \c http.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	struct curl_slist *_headerlist;

        /*! \var const string _wikiPath
	 *  \brief Dirección de \a wikispecies.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	const std::string _wikiPath;

        /*! \var string _query
	 *  \brief Consulta a realizar.
	 *
	 *  Ésta cadena incluye la consulta a realizar al \c
	 *  MediaWiki-API de \a wikispecies. A ésta consulta le hace
	 *  falta la dirección del artículo. La cadena con la \c url
	 *  del artículo se concatena en el momento de realizar la
	 *  consulta.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	std::string _query;

	bool _configQuery(PhyloNode *node);
	void _subclades(PhyloNode *node);
	std::string _fix(std::string& name);
	std::string _fixLink(std::string& name);
	std::string _fixTemplate(std::string& name);
    };
}

#endif
