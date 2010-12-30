#include <iostream>
#include <GL/glu.h>
#include <SDL/SDL_image.h>

#include "PhyloTree.hpp"

using namespace std;
using namespace FreePhyloTree;

PhyloTree::PhyloTree(Name name) : Tree(name), _sidePic(150), _smoothCamera(0.08)
{
  _alloc = new SpringAlloc(3, 25, 80, 1);
  _coloring = new Coloring();

  _radiusNode = 5;
  _radiusBloom = 40;
  _radiusBeam = 2;

  _nodeMouse = NULL;

  _font = new FTGLTextureFont("Resources/FreeSans.ttf");
  _font->FaceSize(12);
}

PhyloTree::~PhyloTree()
{
  delete _alloc;
  delete _coloring;
}

Vec2f PhyloTree::infPic() const
{
  return (Vec2f(_centerPic.x() - _sidePic,
		_centerPic.y() + _sidePic));
}

Vec2f PhyloTree::supPic() const
{
  return (Vec2f(_centerPic.x() + _sidePic,
		_centerPic.y() - _sidePic));
}

const Vec2f& PhyloTree::centerPic() const
{
  return _centerPic;
}

float PhyloTree::sidePic() const
{
  return _sidePic;
}

void PhyloTree::initSignal()
{
  _loadTextures();
  _coloring->coloring(_root);

  glEnable(GL_TEXTURE_2D);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  Vec2f inf = infPic();
  Vec2f sup = supPic();

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(inf.x(), inf.y(), sup.x(), sup.y(), 1, -1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  lookAt(_root->alloc());
}

void PhyloTree::gotoRoot()
{
  _relCamera = _root->alloc() - _centerPic;

  _restSmoothCamera = _smoothCamera;
}

void PhyloTree::lookAt(const Vec2f& rel)
{
  _restSmoothCamera = _smoothCamera;

  _relCamera += rel;
}

void PhyloTree::allocMouse(const Vec2f& alloc)
{
  _allocMouse = alloc;
  _nodeMouse = _searchNode(alloc);
}

void PhyloTree::hideNode(const Vec2f& alloc)
{
  Node *node = _searchNode(alloc);

  if (node != NULL)
    node->setHide(!node->hide());
}

void PhyloTree::draw()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glPushMatrix();
  _drawTree(_root);
  _drawText();
  glPopMatrix();

  Vec2f allocRoot = _root->alloc();

  _alloc->reAlloc(this);
  lookAt(_root->alloc() - allocRoot);
  _reloadCamera();
}

void PhyloTree::_drawTree(Node *node)
{
  float l = 0;

  const Nodes& nodes = node->children(); 

  if (!node->hide())
    for (int i = 0; i < nodes.size(); ++i) {
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
  _drawSquare(node, _radiusBloom, textureid[0]);
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
    //    FTBBox box = _font->BBox(_nodeMouse->name().c_str());

    GLfloat dx = _nodeMouse->x() + 5;
    GLfloat dy = _nodeMouse->y() - 5;

    glColor3f(1, 1, 0);
    //_setColor(_nodeMouse);
    
    glTranslatef(dx, dy, 0);
    glScalef(1, -1, 1);

    _font->Render(_nodeMouse->name().c_str());

    glScalef(1, -1, 1);
    glTranslatef(-dx, -dy, 0);
  }
}

void PhyloTree::_reloadCamera()
{
  Vec2f rel = _relCamera * _restSmoothCamera;
  _restSmoothCamera /= 2;

  _centerPic += rel;
  _relCamera -= rel;

  glTranslatef(-rel.x(), -rel.y(), 0);
}

Node* PhyloTree::_searchNode(const Vec2f& alloc)
{
  for (int i = 0; i < _nodes.size(); ++i) {
    Node *target = _nodes[i];

    if (target->alloc().inRadius(alloc, _radiusNode))
      return target;
  }

  return NULL;
}

void PhyloTree::_loadTextures()
{
  SDL_Surface *textureBloom = IMG_Load("Resources/bloom.tga");
  SDL_Surface *textureBeam = IMG_Load("Resources/beam.png");
  SDL_Surface *textureNode = IMG_Load("Resources/file.png");

  glGenTextures(3, textureid);


  glBindTexture(GL_TEXTURE_2D, textureid[0]);
  gluBuild2DMipmaps(GL_TEXTURE_2D, 4,
		    textureBloom->w, textureBloom->h,
		    GL_RGBA, GL_UNSIGNED_BYTE,
		    (unsigned int*)textureBloom->pixels);

  glBindTexture(GL_TEXTURE_2D, textureid[1]);
  gluBuild2DMipmaps(GL_TEXTURE_2D, 4,
		    textureBeam->w, textureBeam->h,
		    GL_RGBA, GL_UNSIGNED_BYTE,
		    (unsigned int*)textureBeam->pixels);

  glBindTexture(GL_TEXTURE_2D, textureid[2]);
  gluBuild2DMipmaps(GL_TEXTURE_2D, 4,
		    textureNode->w, textureNode->h,
		    GL_RGBA, GL_UNSIGNED_BYTE,
		    (unsigned int*)textureNode->pixels);

  SDL_FreeSurface(textureBloom);
  SDL_FreeSurface(textureBeam);
  SDL_FreeSurface(textureNode);
}
