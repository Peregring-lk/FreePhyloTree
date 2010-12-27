#include <GL/glu.h>
#include <SDL/SDL_image.h>

#include "PhyloTree.hpp"

using namespace FreePhyloTree;

PhyloTree::PhyloTree(Name name) : Tree(name)
{
  _alloc = new SpringAlloc(2, 25, 70, 2);
}

PhyloTree::~PhyloTree()
{
  delete _alloc;
}

void PhyloTree::initSignal()
{
  _loadTextures();

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(-150, 150, 150, -150, 1, -1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void PhyloTree::draw()
{
  glClear(GL_COLOR_BUFFER_BIT);

  glPushMatrix();
  _drawTree(_root);
  glPopMatrix();

  _alloc->reAlloc(this);
}

void PhyloTree::_drawTree(Node *node)
{
  float l = 0;

  const Nodes& nodes = node->children(); 

  for (int i = 0; i < nodes.size(); ++i) {
    Node *child = nodes[i];

    _drawEdge(node, child, 5);
    _drawTree(child);
  }

  _drawNode(node, 80, 10);
}

void PhyloTree::_drawEdge(Node *source, Node *target, float thick) 
{
  thick /= 2;

  glBindTexture(GL_TEXTURE_2D, textureid[1]);

  glColor3f(1, 1, 1);

  float xs = source->x();
  float ys = source->y();
  float xt = target->x();
  float yt = target->y();


  glBegin(GL_QUADS);

  glTexCoord2f(1, 0);
  glVertex2f(xs, ys - thick);
  glTexCoord2f(0, 0);
  glVertex2f(xs, ys + thick);
  glTexCoord2f(0, 0);
  glVertex2f(xt, yt + thick);
  glTexCoord2f(1, 0);
  glVertex2f(xt, yt - thick);

  glEnd();
}

void PhyloTree::_drawNode(Node *node, float bloom, float side)
{
  _selectColor(node);
  _drawSquare(node, bloom, textureid[0]);
  _drawSquare(node, side, textureid[2]);
}

void PhyloTree::_selectColor(Node *node)
{
  glColor3f(node->r(), node->g(), node->b());
}

void PhyloTree::_drawSquare(Node *node, float side, GLuint tex)
{
  side /= 2;

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
