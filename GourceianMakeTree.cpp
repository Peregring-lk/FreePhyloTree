#include <GL/gl.h>
#include <iostream>

#include "GourceianMakeTree.hpp"

using namespace FreePhyloTree;
using namespace std;

typedef vector<Clade*>::const_iterator I;

void GourceianMakeTree::initSignal()
{
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
  _drawNode(20, dx, dy);

  const vector<Clade*>& subclades = clade->getSubclades();
  float l = 0;

  for (I i = subclades.begin(); i != subclades.end(); ++i, l += 50) {
    float ddx = dx + 50;
    float ddy = dy + l;

    _drawEdge(dx, dy, ddx, ddy);
    _drawTreeClade(*i, ddx, ddy);
  }
}

void GourceianMakeTree::_drawNode(float side, float x, float y)
{
  side /= 2;
  glRectf(x - side, y - side, x + side, y + side);
}

void
GourceianMakeTree::_drawEdge(float xO, float yO, float xD, float yD)
{
  glBegin(GL_LINES);
  glVertex2f(xO, yO);
  glVertex2f(xD, yD);
  glEnd();
}
