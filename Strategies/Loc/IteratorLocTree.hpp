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

#ifndef _FPT_ITERATOR_LOC_TREE_
#define _FPT_ITERATOR_LOC_TREE_

#include "../../Tree/IteratorTree.hpp"
#include "LocNode.hpp"

namespace fpt
{
    /*! \class IteratorLocTree
     *  \brief Especialización de \c IteratorTree para \c LocTree.
     *
     *  Ésta clase es un «wrapper» de \c IteratorTree para hacer
     *  transparente al usuario el tipado dinámico, desde \c Node a \c
     *  LocNode.
     *
     */
    class IteratorLocTree : public IteratorTree
    {
    public:
	IteratorLocTree(LocNode *node);

	LocNode* node() const;
	IteratorLocTree forward() const;
    };
}

#endif
