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
#include "Scene.hpp"

// Activate namespace
using namespace std;
using namespace FreePhyloTree;

Scene::Scene(PhyloTree *tree, Camera *cam, QGLContext *context)
    : _tree(tree)
    , _cam(cam)
    , _context(context)
{
    /// 1st.- Setup OpenGL context
    _context->makeCurrent();
    /// 2nd.- Build the frame buffer object where the rendered scene will be stored
    _rttObject = new QGLFramebufferObject(1024, 1024);
}

Scene::~Scene()
{
}

void Scene::Render()
{
    /// 1st.- Set the context
    _context->makeCurrent();
    /// 2nd.- Draws the scene
    _rttObject->bind();
    Draw();
    _rttObject->release();
}

void Scene::Draw()
{
    // Setup the viewport
    glViewport(0, 0, (GLsizei) 1024, (GLsizei) 1024);
    // Enter on projection work space
    glMatrixMode(GL_PROJECTION);
    // Clear all previous transformation
    glLoadIdentity();
    // Make a really simplest orthodromic camera
    glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
    // We return to model work space
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Clean
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /** In the canvas we only need to draw one quad that
     * will use the scenes textures and a shader to compute
     * the screen output.
     */
    // Setup textures
    glBindTexture(GL_TEXTURE_2D, 0);
    glBegin(GL_QUADS);
        glColor4f(1.f,0.f,0.f,1.f);
        // Vertex as the limits of viewport (-1,-1, 1,1)
        glVertex3f(-0.5f, -0.5f, 0.f);
        glVertex3f( 0.5f, -0.5f, 0.f);
        glVertex3f( 0.5f,  0.5f, 0.f);
        glVertex3f(-0.5f,  0.5f, 0.f);
    glEnd();
    glLoadIdentity();
    gluLookAt( 0.2, 0.1,-0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
