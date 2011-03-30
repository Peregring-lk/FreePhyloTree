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

#ifndef _FPT_COLOR_TREE_
#define _FPT_COLOR_TREE_

#include "../../Tree/Tree.hpp"
#include "IteratorColorTree.hpp"

namespace fpt
{
    /*! \class ColorTree
     *  \brief Clase árbol coloreable.
     *
     *  Ésta clase es un tipo \c Tree cuyos nodos son nodos
     *  coloreables, \c ColorNode. Ésta clase se encarga de inicializar a
     *  cada uno de sus nodos y de calcular sus colores haciendo
     *  uso de un algoritmo de la familia de los kd-tree, que divide
     *  el cubo cromático en regiones, asignándole a cada nodo una.
     *
     *  Al igual que con \c LocTree, \c ColorTree se encarga de
     *  controlar los colores y el brillo de cada uno de sus nodos
     *  durante toda la ejecución de la aplicación.
     *
     */
    class ColorTree : virtual public Tree, virtual public Strategy
    {
    public:
	ColorTree(const Name& name, ColorNode *root,
		  float smoothColor = 0.01, float smoothGlow = 0.005);

	ColorNode* root() const;
	bool changed() const;

	IteratorColorTree begin(ColorNode *node = NULL);

	void prepareColor(ColorNode *node = NULL);
	void clearNode(ColorNode *node);

    protected:
	void _init();
	void _step();

	void _initCubes(ColorNode *node, CubeColor& cube, TypeC t);

    private:
	bool _changed;

	float _smoothColor;
	float _smoothGlow;
    };
}

#endif
