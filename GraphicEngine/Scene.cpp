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

Scene::Scene(int width, int height, PhyloTree *tree, Camera *cam, QGLContext *context)
    : _width(width)
    , _height(height)
    , _tree(tree)
    , _cam(cam)
    , _context(context)
    , _textureid(0)
{
    /// 1st.- Setup OpenGL context
    _context->makeCurrent();
    /// 2nd.- Build the frame buffer object where the rendered scene will be stored
    _rttObject = new QGLFramebufferObject(_width, _height);

    _font = new FTGLTextureFont("Resources/FreeSans.ttf");
    _font->FaceSize(12);
}

Scene::~Scene()
{
    delete _textureid;
    _textureid=0;
}

void Scene::create()
{
    loadTextures();
}

void Scene::resize(int width, int height)
{
    _width = width;
    _height = height;
    delete _rttObject;
    _rttObject=0;
    _rttObject = new QGLFramebufferObject(_width, _height);
}

GLuint Scene::texture()
{
    return _rttObject->texture();
}

void Scene::render()
{
    /// 1st.- Set the context
    _context->makeCurrent();
    /// 2nd.- Draws the scene
    _rttObject->bind();
    draw();
    _rttObject->release();
}

void Scene::loadTextures()
{
    _textureid = new GLuint[3];
    QImage textureBloom("Resources/bloom.png");
    QImage textureBeam("Resources/beam.png");
    QImage textureNode("Resources/file.png");

    _textureid[0] = _context->bindTexture(textureBloom, GL_TEXTURE_2D,
                       QGLContext::MipmapBindOption);
    _textureid[1] = _context->bindTexture(textureBeam, GL_TEXTURE_2D,
                       QGLContext::MipmapBindOption);
    _textureid[2] = _context->bindTexture(textureNode, GL_TEXTURE_2D,
                       QGLContext::MipmapBindOption);
}

void Scene::draw()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    Vec3f camSize = _cam->size();
    glViewport(0, 0, (GLsizei) _width, (GLsizei) _height);
    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-camSize.x(),camSize.x(),-camSize.y(),camSize.y(),-camSize.z(),camSize.z());
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Position the camera
    Vec3f cameraPos = _cam->position();
    Vec3f cameraAim = _cam->aimingPoint();
    gluLookAt(  cameraPos.x(), cameraPos.y(), cameraPos.z(),
                cameraAim.x(), cameraAim.y(), cameraAim.z(),
                0.f,           1.f,           0.f);
    // Clean
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawTree(_tree->root());
    glLoadIdentity();

}

void Scene::drawTree(Node *node)
{
    const Nodes& nodes = node->children();

    if (!node->crib()) {
        for (int i = 0; i < (int)nodes.size(); ++i) {
          Node *child = nodes[i];
          drawEdge(node, child);
          drawTree(child);
        }
    }

    drawNode(node);
}

void Scene::drawEdge(Node *source, Node *target)
{
    Vec3f point;
    /* We must paint a plane that looks the camera. In this base
     * class, the camera is in the center point of Camera class
     */
    glBindTexture(GL_TEXTURE_2D, _textureid[1]);

    glColor4f(1.f, 1.f, 1.f, 1.f);

    Vec3f sourcePos = Vec3f(source->x(), source->y(), source->z());
    Vec3f targetPos = Vec3f(target->x(), target->y(), target->z());
    Vec3f diru = targetPos - sourcePos;
    diru /= diru.norm();
    Vec3f normal = _cam->viewDirection();
    Vec3f dirv = Vec3f( normal.y()*diru.z() - normal.z()*diru.y(),
                        normal.z()*diru.x() - normal.x()*diru.z(),
                        normal.x()*diru.y() - normal.y()*diru.x());
    dirv *= 2;

    glBegin(GL_QUADS);
        point = sourcePos - dirv;
        glTexCoord2f(1, 0);
        glVertex3f(point.x(), point.y(), point.z());
        glTexCoord2f(0, 0);
        point = sourcePos + dirv;
        glVertex3f(point.x(), point.y(), point.z());
        glTexCoord2f(0, 0);
        point = targetPos + dirv;
        glVertex3f(point.x(), point.y(), point.z());
        glTexCoord2f(1, 0);
        point = targetPos - dirv;
        glVertex3f(point.x(), point.y(), point.z());
    glEnd();
}

void Scene::drawNode(Node *node)
{
    glColor3f(node->r(), node->g(), node->b());
    drawPlane(node, node->bloom(), _textureid[0]);
    drawPlane(node, node->radius(), _textureid[2]);
}

void Scene::drawPlane(Node *node, float radius, GLuint tex)
{
    Vec3f point;
    /* We must paint a plane that looks the camera. In this base
     * class, the camera is in the center point of Camera class
     */
    Vec3f normal = _cam->viewDirection();
    Vec3f center = Vec3f(node->x(), node->y(), node->z());
    Vec3f diru = Vec3f(-normal.y(),normal.x(),0.f);  // Z=0 parallel vector
    float module = diru.norm();
    if( module < 0.0000001)
        diru = Vec3f(radius,0.f,0.f);
    else
        diru *= radius/module;
    Vec3f dirv = Vec3f( normal.y()*diru.z() - normal.z()*diru.y(),
                        normal.z()*diru.x() - normal.x()*diru.z(),
                        normal.x()*diru.y() - normal.y()*diru.x());

    glBindTexture(GL_TEXTURE_2D, tex);

    glBegin(GL_QUADS);
        point = center + diru + dirv;
        glTexCoord2f(1, 1);
        glVertex3f(point.x(), point.y(), point.z());
        point = center + diru - dirv;
        glTexCoord2f(1, 0);
        glVertex3f(point.x(), point.y(), point.z());
        point = center - diru - dirv;
        glTexCoord2f(0, 0);
        glVertex3f(point.x(), point.y(), point.z());
        point = center - diru + dirv;
        glTexCoord2f(0, 1);
        glVertex3f(point.x(), point.y(), point.z());
    glEnd();
}
