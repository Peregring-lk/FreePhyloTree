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

#include <GL/glu.h>

#include "GLEngine.hpp"
#include "PhyloTree.hpp"

using namespace fpt;

PhyloTree::PhyloTree(Name name)
    : LocTree(name), ColorTree(name), Tree(name)
{
    _loc = new SpringLoc(3, 25, 80, 1);
    _coloring = new Coloring();

    _radiusNode = 5;
    _radiusBeam = 2;

    _radiusBloom = 40;
    _smoothBloom = 0.05;

    _semisidePic = 200;
    _smoothCamera = 0.08;

    _nodeMouse = NULL;

    _font = new FTGLTextureFont("Resources/FreeSans.ttf");
    _font->FaceSize(12);
}

PhyloTree::~PhyloTree()
{
    delete _loc;
    delete _coloring;
}

Vec2f PhyloTree::infPic() const
{
    return (Vec2f(_centerPic.x() - _semisidePic,
		  _centerPic.y() - _semisidePic));
}

Vec2f PhyloTree::supPic() const
{
    return (Vec2f(_centerPic.x() + _semisidePic,
		  _centerPic.y() + _semisidePic));
}

const Vec2f& PhyloTree::centerPic() const
{
    return _centerPic;
}

float PhyloTree::sidePic() const
{
    return _semisidePic * 2;
}

PhyloNode* PhyloTree::actualNode() const
{
    return _nodeMouse;
}

void PhyloTree::initSignal(GLEngine *glEngine)
{
    _loadTextures(glEngine);
    _coloring->coloring(dynamic_cast<ColorNode*>(_root));

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Vec2f inf = infPic();
    Vec2f sup = supPic();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(inf.x(), sup.x(), inf.y(), sup.y(), 1, -1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    _initBloom(_radiusBloom);

    PhyloNode *root = dynamic_cast<PhyloNode*>(_root);

    root->setCrib(true);
    _cribNode(root);

    lookAt(root->loc());
}

void PhyloTree::gotoRoot()
{
    PhyloNode *root = dynamic_cast<PhyloNode*>(_root);

    _relCamera = root->loc() - _centerPic;

    _restSmoothCamera = _smoothCamera;
}

void PhyloTree::lookAt(const Vec2f& rel)
{
    _restSmoothCamera = _smoothCamera;
    _relCamera += rel;
}

void PhyloTree::locMouse(const Vec2f& loc)
{
    _locMouse = loc;
    _nodeMouse = _searchNode(loc);
}

void PhyloTree::cribNode(const Vec2f& loc)
{
    PhyloNode *node = _searchNode(loc);

    _cribNode(node);
}

void PhyloTree::draw()
{
    PhyloNode *root = dynamic_cast<PhyloNode*>(_root);

    glClear(GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    _drawTree(root);
    _drawText();
    glPopMatrix();

    Vec2f locRoot = root->loc();
    _loc->reLoc(this);

    lookAt(root->loc() - locRoot);

    _reloadCamera();
    _reloadBloom(_radiusBloom, _smoothBloom);
}

void PhyloTree::_drawTree(PhyloNode *node)
{
    float l = 0;

    const Nodes& nodes = node->children();

    if (!node->crib())
	for (int i = 0; i < nodes.size(); ++i) {
	    PhyloNode *child = dynamic_cast<PhyloNode*>(nodes[i]);

	    _drawEdge(node, child);
	    _drawTree(child);
	}

    _drawNode(node);
}

void PhyloTree::_drawEdge(PhyloNode *source, PhyloNode *target)
{
    glBindTexture(GL_TEXTURE_2D, textureid[1]);

    glColor3f(1, 1, 1);

    float xs = source->x();
    float ys = source->y();
    float xt = target->x();
    float yt = target->y();

    glBegin(GL_QUADS);

    glTexCoord2f(1, 0);
    glVertex2f(xs, ys - _radiusBeam);
    glTexCoord2f(0, 0);
    glVertex2f(xs, ys + _radiusBeam);
    glTexCoord2f(0, 0);
    glVertex2f(xt, yt + _radiusBeam);
    glTexCoord2f(1, 0);
    glVertex2f(xt, yt - _radiusBeam);

    glEnd();
}

void PhyloTree::_drawNode(PhyloNode *node)
{
    _setColor(node);
    _drawSquare(node, node->bloom(), textureid[0]);
    _drawSquare(node, _radiusNode, textureid[2]);
}

void PhyloTree::_setColor(PhyloNode *node)
{
    glColor3f(node->r(), node->g(), node->b());
}

void PhyloTree::_drawSquare(PhyloNode *node, float side, GLuint tex)
{
    glBindTexture(GL_TEXTURE_2D, tex);

    float x = node->x();
    float y = node->y();

    glBegin(GL_QUADS);

    glTexCoord2f(1, 1);
    glVertex2f(x + side, y + side);
    glTexCoord2f(1, 0);
    glVertex2f(x + side, y - side);
    glTexCoord2f(0, 0);
    glVertex2f(x - side, y - side);
    glTexCoord2f(0, 1);
    glVertex2f(x - side, y + side);

    glEnd();
}

void PhyloTree::_drawText()
{
    if (_nodeMouse != NULL) {
	FTBBox box = _font->BBox(_nodeMouse->name().c_str());

	float heightBox = box.Upper().Y() - box.Lower().Y();

	GLfloat dx = _nodeMouse->x() + 7;
	GLfloat dy = _nodeMouse->y() - heightBox / 2;

	glColor3f(1, 1, 0);
	//_setColor(_nodeMouse);

	glTranslatef(dx, dy, 0);

	_font->Render(_nodeMouse->name().c_str());

	glTranslatef(-dx, -dy, 0);
    }
}

void PhyloTree::_reloadCamera()
{
    Vec2f rel = _relCamera * _restSmoothCamera;
    _restSmoothCamera /= 2;

    _centerPic += rel;
    _relCamera -= rel;

    Vec2f inf = infPic();
    Vec2f sup = supPic();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(inf.x(), sup.x(), inf.y(), sup.y(), 1, -1);

    glMatrixMode(GL_MODELVIEW);
}

PhyloNode* PhyloTree::_searchNode(const Vec2f& loc)
{
    for (int i = 0; i < _nodes.size(); ++i) {
	PhyloNode *target = dynamic_cast<PhyloNode*>(_nodes[i]);

	if (target->loc().inRadius(loc, _radiusNode))
	    return target;
    }

    return NULL;
}

void PhyloTree::_cribNode(PhyloNode *node)
{
    if (node != NULL) {
	bool crib = node->crib();

	node->setCrib(!crib);

	if (crib) {
	    node->setBloom(_radiusBloom * node->nodes());
	    _rebootChildren(node);
	}
    }
}

void PhyloTree::_loadTextures(GLEngine *glEngine)
{
    QImage textureBloom("Resources/bloom.png");
    QImage textureBeam("Resources/beam.png");
    QImage textureNode("Resources/file.png");

    textureid[0] = glEngine->bindTexture(textureBloom, GL_TEXTURE_2D,
					 QGLContext::MipmapBindOption);
    textureid[1] = glEngine->bindTexture(textureBeam, GL_TEXTURE_2D,
					 QGLContext::MipmapBindOption);
    textureid[2] = glEngine->bindTexture(textureNode, GL_TEXTURE_2D,
					 QGLContext::MipmapBindOption);
}
