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
    typedef Smooth Loc;

    class LocNode : virtual public Node, virtual public Strategy
    {
    public:
	LocNode(const Name& name, LocNode *father = NULL);

	LocNode* father() const;
	LocNode* child(unsigned i) const;

	float x() const;
	float y() const;
	float z() const;

	VecXf loc() const;
	VecXf locFather() const;
	const Loc& smoothLoc() const;

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
