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

#include <GL/gl.h>
#include <GL/glu.h>

#include "PhyloTree.hpp"

using namespace fpt;

PhyloNode::PhyloNode(const Name& name, const Name& url, PhyloNode *father)
    : LocNode(name, father), ColorNode(name, father),
      Node(name, father), _url(url), _showedName(false)
{}

const Name& PhyloNode::url() const
{
    return _url;
}

bool PhyloNode::showedName() const
{
    return _showedName;
}

PhyloNode* PhyloNode::father() const
{
    return dynamic_cast<PhyloNode*>(Node::father());
}

PhyloNode* PhyloNode::child(unsigned i) const
{
    return dynamic_cast<PhyloNode*>(Node::child(i));
}

VecXf PhyloNode::proj() const
{
    return _proj;
}

float PhyloNode::projX() const
{
    return _proj.x();
}

float PhyloNode::projY() const
{
    return _proj.y();
}

bool PhyloNode::changed() const
{
    return ColorNode::changed() || LocNode::changed();
}

void PhyloNode::setProj(VecXf proj)
{
    _proj = proj;
}

void PhyloNode::setUrl(const Name& url)
{
    _url = url;
}

void PhyloNode::showName(bool show)
{
    _showedName = show;
}

void PhyloNode::_init()
{
    ColorNode::_init();
    LocNode::_init();
}

void PhyloNode::_step()
{
    ColorNode::_step();
    LocNode::_step();
}
