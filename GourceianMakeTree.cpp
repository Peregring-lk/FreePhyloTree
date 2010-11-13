#include <GL/glu.h>
#include <SDL/SDL_image.h>
#include <iostream>

#include "GourceianMakeTree.hpp"

using namespace FreePhyloTree;
using namespace std;

typedef vector<Clade*>::const_iterator I;

void GourceianMakeTree::initSignal()
{
  _loadTextureNode();

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(0.0f, 400, 400, 0.0f, -1.0f, 1.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void GourceianMakeTree::draw(Clade *clade)
{
  glClear(GL_COLOR_BUFFER_BIT);

  glPushMatrix();
  _drawTreeClade(clade, 20, 20);
  glPopMatrix();
}

void
GourceianMakeTree::_drawTreeClade(Clade *clade, float dx, float dy)
{
  const vector<Clade*>& subclades = clade->getSubclades();
  float l = 0;

  for (I i = subclades.begin(); i != subclades.end(); ++i, l += 50) {
    float ddx = dx + 50;
    float ddy = dy + l;

    _drawEdge(dx, dy, ddx, ddy);
    _drawTreeClade(*i, ddx, ddy);
  }

  _drawBloom(60, dx, dy);
  _drawNode(10, dx, dy);
}

void
GourceianMakeTree::_drawEdge(float xO, float yO, float xD, float yD)
{
  glDisable(GL_TEXTURE_2D);

  glBegin(GL_LINES);
  glVertex2f(xO, yO);
  glVertex2f(xD, yD);
  glEnd();

  glEnable(GL_TEXTURE_2D);
}

void GourceianMakeTree::_drawBloom(float side, float x, float y)
{
  side /= 2;

  glBindTexture(GL_TEXTURE_2D, textureid[0]);

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

void GourceianMakeTree::_drawNode(float side, float x, float y)
{
  side /= 2;

  glBindTexture(GL_TEXTURE_2D, textureid[1]);

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


void GourceianMakeTree::_loadTextureNode()
{
  SDL_Surface *textureBloom = IMG_Load("Resources/bloom.tga");
  SDL_Surface *textureNode = IMG_Load("Resources/file.png");

  glGenTextures(3, textureid);


  glBindTexture(GL_TEXTURE_2D, textureid[0]);
  gluBuild2DMipmaps(GL_TEXTURE_2D, 4,
		    textureBloom->w, textureBloom->h,
		    GL_RGBA, GL_UNSIGNED_BYTE,
		    (unsigned int*)textureBloom->pixels);

  glBindTexture(GL_TEXTURE_2D, textureid[1]);
  gluBuild2DMipmaps(GL_TEXTURE_2D, 4,
		    textureNode->w, textureNode->h,
		    GL_RGBA, GL_UNSIGNED_BYTE,
		    (unsigned int*)textureNode->pixels);

  SDL_FreeSurface(textureBloom);
  SDL_FreeSurface(textureNode);
}
