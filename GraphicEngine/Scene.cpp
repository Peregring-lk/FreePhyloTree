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

/*! \file Scene.cpp
 *  \brief Fichero que implementa a la clase \c fpt::Scene.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2011
 *  \version 0.7
 *  \since 0.7
 */

#include <vector>

#include "Scene.hpp"

using namespace fpt;
using namespace std;

Scene::Scene(PhyloTree *tree, Mouse *mouse)
    : _tree(tree), _mouse(mouse)
{
    _initTexNode = false;
    _initTexGlow = false;
    _initTexEdge = false;

    _radiusNode = 5;
    _weightEdge = 1.5;

    _font = new FTGLTextureFont("Resources/FreeSans.ttf");
    _font->FaceSize(12);
}

Scene::~Scene()
{
    delete _font;
}

bool Scene::changed() const
{
    return _tree->changed();
}

bool Scene::describedNodes() const
{
    return _describeNodes;
}

GLuint Scene::textureNode() const
{
    return _textureIDnode;
}

GLuint Scene::textureGlow() const
{
    return _textureIDglow;
}

GLuint Scene::textureEdge() const
{
    return _textureIDedge;
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

void Scene::describeAllNodes(bool describe)
{
    _describeNodes = describe;
}

void Scene::_init()
{
    _describeNodes = false;

    glEnable(GL_TEXTURE_2D);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Scene::_step()
{
    bool init = _initTexNode && _initTexGlow &&
	_initTexEdge;

    if (init) {
	glClear(GL_COLOR_BUFFER_BIT);

	_drawTree();
    }
}

void Scene::_drawTree()
{
    vector<PhyloNode*> showedNames;

    for (auto i = _tree->begin(); !i.end(); i.next())
	_drawGlow(i.node());

    for (auto i = _tree->begin(); !i.end(); i.next()) {
	PhyloNode *source = i.node();

	for (unsigned i = 0; i < source->degree(); ++i)
	    _drawEdge(source, source->child(i));
    }

    for (auto i = _tree->begin(); !i.end(); i.next()) {
	PhyloNode *node = i.node();

	_drawNode(node);

	if (!describedNodes() && node->showedName())
	    showedNames.push_back(node);
    }

    if (describedNodes())
	for (auto i = _tree->begin(); !i.end(); i.next())
	    _drawText(i.node());
    else {
	PhyloNode *node = _mouse->actualNode();

	if (node != NULL && !node->showedName())
	    showedNames.push_back(node);

	for (int i = 0; i < showedNames.size(); ++i)
	    _drawText(showedNames[i]);
    }
}

void Scene::_drawNode(PhyloNode *node)
{
    _setColor(node);

    if (node->father() == NULL)
	_drawSquare(node, 1.5 * _radiusNode, _textureIDnode);
    else
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

    VecXf dir = target->loc() - source->loc();
    VecXf weight = VecXf(-dir.y(), dir.x()).unit() * _weightEdge;

    VecXf point;

    glBegin(GL_QUADS); {
	point = source->loc() + weight;
	_setColor(source);
	glTexCoord2f(1, 0);
	glVertex2f(point.x(), point.y());

	point = source->loc() - weight;
	glTexCoord2f(0, 0);
	glVertex2f(point.x(), point.y());

	_setColor(target);
	point = target->loc() - weight;
	glTexCoord2f(0, 0);
	glVertex2f(point.x(), point.y());

	point = target->loc() + weight;
	glTexCoord2f(1, 0);
	glVertex2f(point.x(), point.y());
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

void Scene::_drawText(PhyloNode *node)
{
    if (node != NULL) {
	FTBBox box = _font->BBox(node->name().c_str());
	float heightBox = box.Upper().Y() - box.Lower().Y();

	VecXf pos = node->loc() + VecXf(7.0f, - heightBox / 2);

	glColor3f(1, 1, 0);

	//_setColor(_nodeMouse);

	glTranslatef(pos.x(), pos.y(), 0);

	_font->Render(node->name().c_str());

	glTranslatef(-pos.x(), -pos.y(), 0);
    }
}
