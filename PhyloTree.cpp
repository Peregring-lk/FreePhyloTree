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

using namespace FreePhyloTree;

PhyloTree::PhyloTree(Name name) : Tree(name)
{
  _alloc = new SpringAlloc(3, 25, 80, 1);
  _coloring = new Coloring();

  _radiusNode = 5;
  _radiusBeam = 2;

  _radiusBloom = 80;
  _smoothBloom = 0.05;

  _semisidePic = 200;
  _smoothCamera = 0.08;

  _nodeMouse = NULL;

  _font = new FTGLTextureFont("Resources/FreeSans.ttf");
  _font->FaceSize(12);
}

PhyloTree::~PhyloTree()
{
  delete _alloc;
  delete _coloring;
}

Vec3f PhyloTree::infPic() const
{
  return (Vec3f(_centerPic.x() - _semisidePic,
		_centerPic.y() - _semisidePic,
		0));
}

Vec3f PhyloTree::supPic() const
{
  return (Vec3f(_centerPic.x() + _semisidePic,
		_centerPic.y() + _semisidePic,
		0));
}

const Vec3f& PhyloTree::centerPic() const
{
  return _centerPic;
}

float PhyloTree::sidePic() const
{
  return _semisidePic * 2;
}

Node* PhyloTree::actualNode() const
{
  return _nodeMouse;
}

void PhyloTree::initSignal()
{
  _coloring->coloring(_root);
  _initBloom(_radiusBloom);
  cribNode(_root);
}

void PhyloTree::gotoRoot()
{
  _relCamera = _root->alloc() - _centerPic;

  _restSmoothCamera = _smoothCamera;
}

void PhyloTree::lookAt(const Vec3f& rel)
{
  _restSmoothCamera = _smoothCamera;
  _relCamera += rel;
}

void PhyloTree::allocMouse(const Vec3f& alloc)
{
  _allocMouse = alloc;
  _nodeMouse = _searchNode(alloc);
}

void PhyloTree::cribNode(Node *node)
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

void PhyloTree::setSelectedNode(Node* node)
{
    _nodeMouse=node;
}

Node* PhyloTree::selectedNode() const
{
    return _nodeMouse;
}

void PhyloTree::update()
{
    _alloc->reAlloc(this);
    _reloadBloom(_radiusBloom, _smoothBloom);
}

void PhyloTree::draw()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glPushMatrix();
  _drawTree(_root);
  _drawText();
  glPopMatrix();

  Vec3f allocRoot = _root->alloc();

  _alloc->reAlloc(this);
  lookAt(_root->alloc() - allocRoot);
  _reloadCamera();
  _reloadBloom(_radiusBloom, _smoothBloom);
}

void PhyloTree::_drawTree(Node *node)
{
  float l = 0;

  const Nodes& nodes = node->children();

  if (!node->crib())
    for (int i = 0; i < (int)nodes.size(); ++i) {
      Node *child = nodes[i];

      _drawEdge(node, child);
      _drawTree(child);
    }

  _drawNode(node);
}

void PhyloTree::_drawEdge(Node *source, Node *target)
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

void PhyloTree::_drawNode(Node *node)
{
    _setColor(node);
    _drawSquare(node, node->bloom(), textureid[0]);
    _drawSquare(node, _radiusNode, textureid[2]);
}

void PhyloTree::_setColor(Node *node)
{
  glColor3f(node->r(), node->g(), node->b());
}

void PhyloTree::_drawSquare(Node *node, float side, GLuint tex)
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
  Vec3f rel = _relCamera * _restSmoothCamera;
  _restSmoothCamera /= 2;

  _centerPic += rel;
  _relCamera -= rel;

  Vec3f inf = infPic();
  Vec3f sup = supPic();

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(inf.x(), sup.x(), inf.y(), sup.y(), 1, -1);

  glMatrixMode(GL_MODELVIEW);
}

Node* PhyloTree::_searchNode(const Vec3f& alloc)
{
  for (int i = 0; i < _nodes.size(); ++i) {
    Node *target = _nodes[i];

    if (target->alloc().inRadius(alloc, _radiusNode))
      return target;
  }

  return NULL;
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
