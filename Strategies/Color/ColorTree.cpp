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

#include <iostream>
#include "ColorTree.hpp"

using namespace fpt;

ColorTree::ColorTree(const Name& name, ColorNode *root,
		     float smoothColor, float smoothGlow)
    : Tree(name, root), _smoothColor(smoothColor),
      _smoothGlow(smoothGlow)
{}

ColorNode* ColorTree::root() const
{
    return dynamic_cast<ColorNode*>(Tree::root());
}

IteratorColorTree ColorTree::begin(ColorNode *node)
{
    if (node == NULL)
	node = root();

    return IteratorColorTree(node);
}

void ColorTree::_init()
{
    _initCubes(root(), CubeColor(0, 0, 0, 1, 1, 1), 0);

    for (auto i = begin(); !i.end(); i.next()) {
	ColorNode *node = i.node();
	VecXf color(node->fatherCubeColor().center(), 0.5f);
	node->setSourceColor(color.x(), color.y(), color.z());

	node->randSourceGlow(500 * node->order());
	node->setTargetGlow(70 * node->order());
	node->changeSmoothColor(_smoothColor);
	node->changeSmoothGlow(_smoothGlow);

	node->init();
    }

    _changed = true;
}

void ColorTree::_step()
{
    for (auto i = begin(); !i.end(); i.next()) {
	i.node()->step();

	if (i.node()->changed())
	    _changed = true;
    }
}

void ColorTree::_initCubes(ColorNode *node, CubeColor cube, TypeC t)
{
    TypeC newt = (t + 1) % 3;

    node->setCubeColor(cube);

    for (Dim i = 0; i < node->degree(); ++i) {

	CubeColor newCube(cube);
	newCube.cut(t, node->degree(), i);

	_initCubes(node->child(i), newCube, newt);
    }

}
