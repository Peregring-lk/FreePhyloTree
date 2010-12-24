#include <GL/glu.h>
#include <SDL/SDL_image.h>
#include <iostream>

#include "GourceianMakeTree.hpp"

using namespace FreePhyloTree;
using namespace std;

void GourceianMakeTree::initSignal()
{
  _loadTextures();

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(0.0f, 400, 400, 0.0f, -1.0f, 1.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void GourceianMakeTree::draw(Node *node)
{
  glClear(GL_COLOR_BUFFER_BIT);

  glPushMatrix();
  _drawTree(node, 20, 20);
  glPopMatrix();
}

void
GourceianMakeTree::_drawTree(Node *node, float dx, float dy)
{
  const Children& children = node->getChildren();
  float l = 0;

  for (int i = 0; i < children.size(); ++i, l += 50) {
    float ddx = dx + 50;
    float ddy = dy + l;

    _drawEdge(node, children[i], dx, dy, ddx, ddy, 2);
    _drawTree(children[i], ddx, ddy);
  }

  _drawBloom(node, 60, dx, dy);
  _drawNode(node, 10, dx, dy);
}

void
GourceianMakeTree::_drawEdge(Node *begin, Node *end, float xO,
			     float yO, float xD, float yD,
			     float thick) 
{
  thick /= 2;

  glBindTexture(GL_TEXTURE_2D, textureid[1]);

  glColor3f(1, 1, 1);

  glBegin(GL_QUADS);

  glTexCoord2f(1, 0);
  glVertex2f(xO, yO - thick);
  glTexCoord2f(0, 0);
  glVertex2f(xO, yO + thick);
  glTexCoord2f(0, 0);
  glVertex2f(xD, yD + thick);
  glTexCoord2f(1, 0);
  glVertex2f(xD, yD - thick);

  glEnd();
}

void GourceianMakeTree::_drawBloom(Node *node, float side,
				   float x, float y)
{
  side /= 2;

  glBindTexture(GL_TEXTURE_2D, textureid[0]);

  Color color = node->getColor();
  glColor3f(color._color[0], color._color[1], color._color[2]);

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

void GourceianMakeTree::_drawNode(Node *node, float side,
				  float x, float y)
{
  side /= 2;

  glBindTexture(GL_TEXTURE_2D, textureid[2]);

  Color color = node->getColor();
  glColor3f(color._color[0], color._color[1], color._color[2]);

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


void GourceianMakeTree::_loadTextures()
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
}
