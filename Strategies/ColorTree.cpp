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

#include "ColorTree.hpp"

using namespace fpt;

ColorTree::ColorTree(const Name& name) : Tree(name)
{}

void ColorTree::_initBloom(float bloom)
{
    for (int i = 0; i < _nodes.size(); ++i) {
	ColorNode *node = dynamic_cast<ColorNode*>(_nodes[i]);

	node->setBloom(bloom);
    }
}

void ColorTree::_reloadBloom(float bloom, float smooth)
{
    for (int i = 0; i < _nodes.size(); ++i) {
	ColorNode *node = dynamic_cast<ColorNode*>(_nodes[i]);

	float nodeBloom = node->bloom();
	float difBloom = nodeBloom - bloom;

	node->setBloom(nodeBloom - difBloom * smooth);
    }
}

