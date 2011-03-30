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

#ifndef _FPT_LOC_NODE_
#define _FPT_LOC_NODE_

#include "../../Tree/Node.hpp"

#include "../Strategy.hpp"
#include "../Smooth.hpp"

namespace fpt
{
    /*! \typedef Loc
     *  \brief Tipo \a Location.
     *
     *  Cada \c LocNode no contiene una posición, sino un «camino»,
     *  desde su última posición hasta la siguiente posición especificada.
     */
    typedef Smooth Loc;

    /*! \class LocNode
     *  \brief Clase nodo con posición o posicionable (\a Location \a
     *  node).
     *
     *  Cada nodo de un \c LocTree tiene una posición actual y va
     *  cambiando de posición a medida que va ejecutándose el
     *  algoritmo \a Spring \a embedder. Para que los cambios de
     *  posiciones no sean bruscos, el nodo va cambiando de posición
     *  regido por el comportamiento de una variable \c Smooth, que es
     *  la que contiene la posición actual y cómo ésta va a cambiar.
     *
     */
    class LocNode : virtual public Node, virtual public Strategy
    {
    public:
	LocNode(const Name& name, LocNode *father = NULL);

	LocNode* child(unsigned i) const;
	LocNode* father() const;

	float x() const;
	float y() const;
	float z() const;

	VecXf loc() const;
	VecXf dir() const;

	VecXf locFather() const;
	const Loc& smoothLoc() const;

	bool changed() const;

	void setSourceLoc(const VecXf& loc);
	void setTargetLoc(const VecXf& loc);
	void moveTargetLoc(const VecXf& delta);
	void changeSmooth(float smooth);

    protected:
	void _init();
	void _step();

    private:
	Loc _loc;
    };
}

#endif
