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

#ifndef _FPT_PHYLO_NODE_
#define _FPT_PHYLO_NODE_

#include "Strategies/Color/ColorNode.hpp"
#include "Strategies/Loc/LocNode.hpp"

namespace fpt
{
    class PhyloNode : public LocNode, public ColorNode
    {
    public:
	PhyloNode(const Name& name, const Name& url,
		  PhyloNode *father = NULL);

	const Name& url() const;

	PhyloNode* father() const;
	PhyloNode* child(unsigned i) const;

	VecXf proj() const;
	float projX() const;
	float projY() const;

	bool changed() const;

	void setProj(VecXf proj);
	void setUrl(const Name& url);

    protected:
	void _init();
	void _step();

    private:
	Name _url;
	VecXf _proj;

	void _uploadProj();
    };
}

#endif
