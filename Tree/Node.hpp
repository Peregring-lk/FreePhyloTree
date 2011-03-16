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

#ifndef _FPT_NODE_
#define _FPT_NODE_

#include <string>
#include <vector>

namespace fpt
{
    class Tree;

    /*! \typedef Name
     *  \brief Tipo nombre.
     *
     *  Clase usada para tratar con nombres de clados / árboles.
     *
     *  \note Por ahora, un simple string, pero ésto podría cambiar
     *  para tratar con meta-información del nombre.
     *
     */
    typedef std::string Name;

    /*! \class Node
     *  \brief Clase nodo de un árbol.
     *
     *  La clase nodo permite obtener y manipular los nodos de un
     *  árbol, y obtener propiedades de él, como el grado, el órden o
     *  el nivel.
     *
     */
    class Node
    {
    public:
	Node(const Name& name, Node *father = NULL);
	virtual ~Node();

	const Name& name() const;

	unsigned degree() const;
	unsigned order() const;
	unsigned level() const;

	virtual Node* father() const;
	virtual Node* child(unsigned i) const;

	void changeFather(Node *node);

	void addChild(Node *node);
	void quitChild(Node *node);
	virtual void clear();

    protected:
	Name _name;

	Node *_father;
	std::vector<Node*> _children;

	unsigned _order;

	void _updateOrder(int f = 1);
    };
}

#endif
