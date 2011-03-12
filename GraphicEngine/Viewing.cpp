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

#include <iostream>
#include <GL/glu.h>

#include "Viewing.hpp"

using namespace fpt;

Viewing::Viewing(PhyloTree *tree, GLsizei width, GLsizei height,
		 float maxRatio)
    : _tree(tree), _maxRatio(maxRatio), _delta(2u)
{
    sizeViewport(width, height);
    _border = 1.2;
}

bool Viewing::changed() const
{
    return _center.changed() || _distance.changed();
}

void Viewing::sizeViewport(GLsizei width, GLsizei height)
{
    _width = width;
    _height = height;

    _changeViewport = true;
}

void Viewing::moveCamera(const VecXf& delta)
{
    _delta += delta;
    _center.changeTarget(_center.target() + delta);
}

void Viewing::centering()
{
    moveCamera(-_delta);
}

void Viewing::_init()
{
    _center.changeSource(_tree->center());
    _distance.changeSource(VecXf(2u, _tree->radius()));

    _center.changeSmooth(0.05);
    _distance.changeSmooth(0.05);

    _center.init();
    _distance.init();
}

void Viewing::_step()
{
    if (_tree->changed() || _changeViewport)
	_calcOrtho();

    _center.step();
    _distance.step();

    if (changed()) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	_project();

	if (_changeViewport) {
	    glViewport(0, 0, _width, _height);
	    _changeViewport = false;
	}

	glMatrixMode(GL_MODELVIEW);

	_uploadProj();
    }
}

void Viewing::_calcOrtho()
{
    VecXf center = _tree->center();
    float radius = _tree->radius();
    VecXf distance = VecXf(2u, radius);

    /*
     *
     *  Igualamos ratio de Viewport con quad.
     *
     */
    float vwRatio = (float)_width / _height;
    float lambda = vwRatio * radius;

    if (lambda > radius)
	distance.setX(lambda);
    else
	distance.setY(radius / vwRatio);

    /*
     *
     *  Reducimos el ratio coordenadas / píxel.
     *
     */
    if (2 * distance.x() / _width < _maxRatio) {
	distance.setX(_width * _maxRatio * 0.5);
	distance.setY(distance.x() / vwRatio);
    }

    /*
     *
     *  Desplazamos el centro
     *
     */
    center += _delta;

    _center.changeTarget(center);
    _distance.changeTarget(distance);

    _changed = true;
}

void Viewing::_project()
{
    VecXf inf = _center.source() -  _distance.source();
    VecXf sup = _center.source() +  _distance.source();

    glOrtho(inf.x(), sup.x(), inf.y(), sup.y(), -1, 1);
}

void Viewing::_uploadProj()
{
    GLdouble model[16];
    GLdouble proj[16];
    GLint viewport[4];
    GLdouble cx;
    GLdouble cy;
    GLdouble cz;

    glGetDoublev(GL_MODELVIEW_MATRIX, model);
    glGetDoublev(GL_PROJECTION_MATRIX, proj);
    glGetIntegerv(GL_VIEWPORT, viewport);

    for (auto i = _tree->begin(); !i.end(); i.next()) {
	PhyloNode *node = i.node();

	gluProject(node->x(), node->y(), 0, model, proj, viewport,
		       &cx, &cy, &cz);

	node->setProj(VecXf(cx, viewport[3] - cy));
    }
}
