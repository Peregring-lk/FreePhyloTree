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

#ifndef _FPT_MOUSE_
#define _FPT_MOUSE_

#include "../VecXf/VecXf.hpp"
#include "../PhyloTree.hpp"
#include "Viewing.hpp"

namespace fpt
{
    /*! \class Mouse
     *  \brief Clase que maneja la posición del ratón.
     *
     *  Ésta clase maneja las posiciones, movimientos y información
     *  necesaria acerca del ratón, así como encontrar a los nodos
     *  señalados con él.
     *
     */
    class Mouse : public Strategy
    {
    public:
	Mouse(PhyloTree *tree, Viewing *viewing);

	VecXf pos() const;
	VecXf mov() const;

	bool leftClick() const;
	bool changedActualNode() const;
	PhyloNode* actualNode() const;

	bool changed() const;

	void setLeftClick(bool click);
	void setPos(VecXf pos);
	void move(VecXf delta);

	void clean();

    protected:
	void _init();
	void _step();

    private:
	Viewing *_viewing;
	PhyloTree *_tree;

	bool _leftClick;
	bool _clean;
	VecXf _pos;
	VecXf _mov;

	bool _changed;

	PhyloNode *_actual;
	bool _changedActual;
    };
}

#endif
