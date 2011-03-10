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

#include "Scene.hpp"

using namespace fpt;

Scene::Scene(PhyloTree *tree) : _tree(tree)
{
    _initTexNode = false;
    _initTexGlow = false;
    _initTexEdge = false;

    _radiusNode = 5;
    _weightEdge = 2;
}

void Scene::setTextureNode(GLuint id)
{
    _textureIDnode = id;
    _initTexNode = true;
}

void Scene::setTextureGlow(GLuint id)
{
    _textureIDglow = id;
    _initTexGlow = true;
}

void Scene::setTextureEdge(GLuint id)
{
    _textureIDedge = id;
    _initTexEdge = true;
}

void Scene::_init()
{
    glEnable(GL_TEXTURE_2D);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Scene::_step()
{
    bool init = _initTexNode && _initTexGlow && _initTexEdge;

    if (init) {
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	_drawTree();
	glPopMatrix();
    }
}

void Scene::_drawTree()
{
    for (auto i = _tree->begin(); !i.end(); i.next())
	_drawGlow(i.node());

    for (auto i = _tree->begin(); !i.end(); i.next()) {
	PhyloNode *source = i.node();

	for (unsigned i = 0; i < source->degree(); ++i)
	    _drawEdge(source, source->child(i));
    }

    for (auto i = _tree->begin(); !i.end(); i.next())
	_drawNode(i.node());
}

void Scene::_drawNode(PhyloNode *node)
{
    _setColor(node);
    _drawSquare(node, _radiusNode, _textureIDnode);
}

void Scene::_drawGlow(PhyloNode *node)
{
    _setColor(node);
    _drawSquare(node, node->glow(), _textureIDglow);
}

void Scene::_drawEdge(PhyloNode *source, PhyloNode *target)
{
    glBindTexture(GL_TEXTURE_2D, _textureIDedge);

    glColor3f(.5, .5, .5);

    float xs = source->x();
    float ys = source->y();

    float xt = target->x();
    float yt = target->y();

    glBegin(GL_QUADS); {

	glTexCoord2f(1, 0);
	glVertex2f(xs, ys - _weightEdge);

	glTexCoord2f(0, 0);
	glVertex2f(xs, ys + _weightEdge);

	glTexCoord2f(0, 0);
	glVertex2f(xt, yt + _weightEdge);

	glTexCoord2f(1, 0);
	glVertex2f(xt, yt - _weightEdge);

    } glEnd();
}

void Scene::_drawSquare(PhyloNode *node, float side, GLuint tex)
{
    glBindTexture(GL_TEXTURE_2D, tex);

    float x = node->x();
    float y = node->y();

    glBegin(GL_QUADS); {

	glTexCoord2f(1, 1);
	glVertex2f(x + side, y + side);

	glTexCoord2f(1, 0);
	glVertex2f(x + side, y - side);

	glTexCoord2f(0, 0);
	glVertex2f(x - side, y - side);

	glTexCoord2f(0, 1);
	glVertex2f(x - side, y + side);

    } glEnd();
}

void Scene::_setColor(PhyloNode *node)
{
    glColor3f(node->r(), node->g(), node->b());
}
