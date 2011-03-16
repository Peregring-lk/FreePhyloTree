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

#ifndef _FPT_LOC_TREE_
#define _FPT_LOC_TREE_

#include <vector>

#include "../../Tree/Tree.hpp"
#include "IteratorLocTree.hpp"

namespace fpt
{
    /*! \class LocTree
     *  \brief Clase árbol posicionable (\a Location \c tree).
     *
     *  Ésta clase es un tipo \c Tree cuyos nodos son nodos
     *  posicionables, \c LocNode. Ésta clase se encarga de inicializar a
     *  cada uno de sus nodos y de calcular sus posiciones haciendo
     *  uso del algoritmo \a Spring \a embedder.
     *
     */
    class LocTree : virtual public Tree, virtual public Strategy
    {
    public:
	LocTree(const Name& name, LocNode *root,
		float c1, float c2, float c3, float c4,
		float smooth = 0.15);

	LocNode* root() const;
	VecXf locRoot() const;

	VecXf center() const;
	float radius() const;

	IteratorLocTree begin(LocNode *node = NULL);

	void prepareLoc(LocNode *node = NULL);
	void clearNode(LocNode *node);

    protected:
	void _init();
	void _step();

    private:
	float _smooth;

	float _c1;
	float _c2;
	float _c3;
	float _c4;

	bool _changed;
	VecXf _center;
	float _radius;

	typedef std::vector<VecXf> _Moves;

	VecXf _fa(LocNode *source, LocNode *target) const;
	VecXf _fr(LocNode *source, LocNode *target) const;

	void _calcConvexSphere();
	float _min(float a, float b);
	float _max(float a, float b);
    };
}

#endif
