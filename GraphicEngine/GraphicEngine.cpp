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

#include "GraphicEngine.hpp"

// Activate namespace
using namespace std;
using namespace FreePhyloTree;

GraphicEngine::GraphicEngine(QFreePhyloTree *app, PhyloTree *tree)
  : _app(app)
  , _tree(tree)
{
    /// 1st.- Construct the OpenGL window
    setMouseTracking(true);
    _size = Vec2f(width(), height());
    _webView.hide();

    /// 2nd.- Construct entities
    _cam = new Camera(_tree);
    _scenes = new Scene* [_N_SCENES_];
    _scenes[_NORMAL_SCENE_] = new Scene(_tree, _cam, (QGLContext*)context());
}

GraphicEngine::~GraphicEngine()
{
    delete _tree;
}

QFreePhyloTree* GraphicEngine::app()
{
    return _app;
}

Scene* GraphicEngine::scene(int id)
{
    if ((id < 0) || (id >= _N_SCENES_))
        return 0;

    return _scenes[id];
}

Vec2f GraphicEngine::size()
{
    return _size;
}

void GraphicEngine::animate()
{
    repaint();
}

void GraphicEngine::initializeGL()
{
    glEnable( GL_TEXTURE_2D );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(0, 0, (GLsizei)width(), (GLsizei)height());
    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GraphicEngine::paintGL()
{
    // Call to draw the scenes and return the textures
    GLuint textures[_N_SCENES_];
    _scenes[_NORMAL_SCENE_]->Render();
    textures[_NORMAL_SCENE_] = _scenes[_NORMAL_SCENE_]->GetTexture();

    // Clean the screen otuput
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /** In the GraphicEngine we only need to draw one quad that
     * will use the scenes textures and a shader to compute
     * the screen output.
     */
    glViewport(0, 0, (GLsizei) width(), (GLsizei) height());
    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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

void GraphicEngine::resizeGL(int width, int height)
{
    /* Resizing the openGL window have two phases,
     * first the OpenGL viewport must be readdapted, and
     * secondly the scenes, and their offscreen object must be
     * rescaled.
     */
    _size = Vec2f(width, height);
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
}

void GraphicEngine::keyPressEvent(QKeyEvent *event)
{
}

void GraphicEngine::mouseDoubleClickEvent(QMouseEvent *event)
{
}

void GraphicEngine::mouseMoveEvent(QMouseEvent *event)
{
}

