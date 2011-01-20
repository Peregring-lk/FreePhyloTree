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

// -------------------------------------------
// Main header file
// -------------------------------------------
#include "Canvas.hpp"

// -------------------------------------------
// FreePhyloTree classes
// -------------------------------------------
#include "GraphicEngine.hpp"

// Activate namespace
using namespace std;
using namespace FreePhyloTree;

Canvas::Canvas(GraphicEngine *ge, PhyloTree *tree, Camera *cam)
  : _ge(ge), _tree(tree), _cam(cam)
{
    /// 1st.- Activate mouse events
    setMouseTracking(true);
    /// 2nd.- Get canvas size
    _size = Vec2f(width(), height());
    //resizeGL(_size.x(), _size.y());

    _webView.hide();
}

Canvas::~Canvas()
{}

void Canvas::animate()
{
  repaint();
}

void Canvas::initializeGL()
{
  // General options
  glEnable( GL_TEXTURE_2D );
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Setup the viewport
  glViewport(0, 0, (GLsizei)width(), (GLsizei)height());
  // Enter on projection work space
  glMatrixMode(GL_PROJECTION);
  // Clear all previous transformation
  glLoadIdentity();
  // Make a really simplest orthodromic camera
  glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
  // We return to model work space
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Canvas::paintGL()
{
    // Call to draw the scenes and return the textures
    GLuint textures[_N_SCENES_];
    _ge->GetScene(_NORMAL_SCENE_)->Render();
    textures[_NORMAL_SCENE_] = _ge->GetScene(_NORMAL_SCENE_)->GetTexture();

    // Clean the screen otuput
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /** In the canvas we only need to draw one quad that
     * will use the scenes textures and a shader to compute
     * the screen output.
     */
    // Setup the viewport
    glViewport(0, 0, (GLsizei) width(), (GLsizei) height());
    // Enter on projection work space
    glMatrixMode(GL_PROJECTION);
    // Clear all previous transformation
    glLoadIdentity();
    // Make a really simplest orthodromic camera
    glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
    // We return to model work space
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Setup textures
    glBindTexture(GL_TEXTURE_2D, textures[_NORMAL_SCENE_]);
    glBegin(GL_QUADS);
        glColor4f(1.f,1.f,1.f,1.f);
        // Normal against the camera
        glNormal3f( 0.0f, 0.0f, 1.0f);
        // Vertex as the limits of viewport (-1,-1, 1,1)
        glTexCoord2f(0.f, 0.f); glVertex3f(-1.f, -1.f, 0.f);
        glTexCoord2f(1.f, 0.f); glVertex3f( 1.f, -1.f, 0.f);
        glTexCoord2f(1.f, 1.f); glVertex3f( 1.f,  1.f, 0.f);
        glTexCoord2f(0.f, 1.f); glVertex3f(-1.f,  1.f, 0.f);
    glEnd();
    glLoadIdentity();
    gluLookAt( 0.0, 0.0,-0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void Canvas::resizeGL(int width, int height)
{
    _size = Vec2f(width, height);

    // Setup the viewport
    // TODO: Segmentation fault in this line (with g++ compiler at
    // least)
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
    // Enter on projection work space
    glMatrixMode(GL_PROJECTION);
    // Clear all previous transformation
    glLoadIdentity();
    // Make a really simplest orthodromic camera
    glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
    // We return to model work space
    glMatrixMode(GL_MODELVIEW);
}

void Canvas::keyPressEvent(QKeyEvent *event)
{
}

void Canvas::mouseDoubleClickEvent(QMouseEvent *event)
{
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
}

