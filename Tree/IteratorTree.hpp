/*
  Copyright (C) 2010 Aarón Bueno Villares <abv150ci@gmail.com>

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

/*! \file IteratorTree.hpp
 *  \brief Fichero que define a la clase \c fpt::IteratorTree.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2011
 *  \version 0.7
 *  \since 0.7
 */
#ifndef _FPT_ITERATOR_TREE_
#define _FPT_ITERATOR_TREE_

#include "Node.hpp"

#include <stack>

namespace fpt
{
    /*! \class IteratorTree
     *  \brief Iterator para recorrer un árbol.
     *
     *  Esta clase permite recorrer todos los elementos de un árbol como
     *  si fuera un vector. El recorrido se hace en preorden.
     *
     *  Para implementar el árbol, se hace uso de la pila \c
     *  IteratorTree::_mem y las variables \c IteratorTree::_node y \c
     *  IteratorTree::_top. \c _top es la raíz del árbol y \c _node el
     *  nodo actual. El tope de la pila \c _mem contiene el n-ésimo
     *  hijo procesado, de modo que, para realizar un siguiente paso,
     *  si el \c _node posee hijos se coloca un 0 en el tope, y se lee
     *  su primer hijo. En caso contrario se obtiene el siguiente hijo
     *  de su padre (su hermano) incrementando el tope de la pila. El
     *  nodo actual se obtiene con la función \c node().
     *
     *  \note Evidentemente, heredando y sobrecargando se pueden
     *  especificar otros recorridos: inorden, postorden, anchura,
     *  etcétera.
     */
    class IteratorTree
    {
    public:
        /*! \fn IteratorTree(Node *node)
	 *  \brief Constructor del iterator.
	 *
	 *  \param node Raíz del árbol a procesar.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	IteratorTree(Node *node);

        /*! \fn bool end() const
	 *  \brief Si ha finalizado el recorrido.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	bool end() const;

        /*! \fn Node* node() const
	 *  \brief Nodo actual.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	Node* node() const;

        /*! \fn unsigned index() const
	 *  \brief Índice actual.
	 *
	 *  El índice indica el n-ésimo elemento leido, desde el punto
	 *  de vista de un vector.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	unsigned index() const;

        /*! \fn IteratorTree fordward() const
	 *  \brief Iterador que salta al siguiente elemento.
	 *
	 *  Esta función es útil para dobles bucles, por ejemplo,
	 *  cuando se quieren procesar aristas. En éstos casos, si se
	 *  desea procesar aristas bidireccionales, de modo que la
	 *  arista (n, m) sea igual a (m, n) se puede hacer un
	 *  recorrido de modo que el segundo bucle comience por el
	 *  siguiente elemento al actual, del mismo modo que se
	 *  procesa solo media matríz cuando ésta es simétrica.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	IteratorTree forward() const;

        /*! \fn void next()
	 *  \brief Nuevo paso de recorrido.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	void next();

    private:
        /*! \var Node *_node
	 *  \brief Nodo actual.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	Node *_node;

        /*! \var Node *_top
	 *  \brief Raíz del árbol.
	 *
	 *  El nombre de \c _top se justifica en el hecho de que ésta
	 *  variable indica cuando el recorrido ha finalizado.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	Node *_top;

        /*! \var stack<unsigned> _mem.
	 *  \brief Pila auxiliar de recorrido.
	 *
	 *  \sa IteratorTree
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	std::stack<unsigned> _mem;

        /*! \var unsigned _index.
	 *  \brief Índice de recorrido.
	 *
	 *  \sa index()
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	unsigned _index;
    };
};

#endif
