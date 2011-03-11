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

#include "ColorNode.hpp"

using namespace fpt;

ColorNode::ColorNode(const Name& name, ColorNode *father)
    : Node(name, father), _color(3), _glow(1)
{}

ColorNode* ColorNode::father() const
{
    return dynamic_cast<ColorNode*>(Node::father());
}

ColorNode* ColorNode::child(unsigned i) const
{
    return dynamic_cast<ColorNode*>(Node::child(i));
}

float ColorNode::r() const
{
    return _color.source().coord(0);
}

float ColorNode::g() const
{
    return _color.source().coord(1);
}

float ColorNode::b() const
{
    return _color.source().coord(2);
}

float ColorNode::glow() const
{
    return _glow.source().coord(0);
}

const Color& ColorNode::smoothColor() const
{
    return _color;
}

const Glow& ColorNode::smoothGlow() const
{
    return _glow;
}

CubeColor ColorNode::fatherCubeColor() const
{
    if (father() == NULL)
	return CubeColor();
    else
	return father()->cubeColor();
}

CubeColor ColorNode::cubeColor() const
{
    return _cube;
}

bool ColorNode::changed() const
{
    return _color.changed() || _glow.changed();
}

void ColorNode::randSourceGlow(float center, float radius)
{
    if (radius == 0)
	radius = center * 0.3;

    VecXf rand(VecXf(center), radius);

    setSourceGlow(rand.x());
}

void ColorNode::setSourceColor(float r, float g, float b)
{
    _color.changeSource(VecXf(r, g, b));
}

void ColorNode::setCubeColor(const CubeColor& cube)
{
    _cube = cube;
    _color.changeTarget(_cube.center());
}

void ColorNode::setSourceGlow(float glow)
{
    _glow.changeSource(VecXf(glow));
}

void ColorNode::setTargetGlow(float glow)
{
    _glow.changeTarget(VecXf(glow));
}

void ColorNode::changeSmoothColor(float smooth)
{
    _color.changeSmooth(smooth);
}

void ColorNode::changeSmoothGlow(float smooth)
{
    _glow.changeSmooth(smooth);
}

void ColorNode::_init()
{
    _color.init();
    _glow.init();
}

void ColorNode::_step()
{
    _color.step();
    _glow.step();
}
