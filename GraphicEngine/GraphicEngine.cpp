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

// -------------------------------------------
// Main header file
// -------------------------------------------
#include "GraphicEngine.hpp"

// -------------------------------------------
// FreePhyloTree classes
// -------------------------------------------
#include "../FreePhyloTree.hpp"

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
    float aspectRatio = width()/height();
    _cam = new Camera(_tree, aspectRatio);
    _scenes = new Scene* [_N_SCENES_];
    _scenes[_NORMAL_SCENE_] = new Scene(width(), height(), _tree, _cam, (QGLContext*)context());
        _scenes[_NORMAL_SCENE_]->create();
    _font = new FTGLTextureFont("Resources/FreeSans.ttf");
    _font->FaceSize(12);

}

GraphicEngine::~GraphicEngine()
{
    delete _tree;
    delete _font;
    _font=0;
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
    _cam->resize();
    repaint();
    _tree->update();
}

void GraphicEngine::initializeGL()
{
    glEnable( GL_TEXTURE_2D );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, (GLsizei)width(), (GLsizei)height());
    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    _tree->initSignal();
}

void GraphicEngine::paintGL()
{
    // Call to draw the scenes and return the textures
    GLuint textures[_N_SCENES_];
    _scenes[_NORMAL_SCENE_]->render();
    textures[_NORMAL_SCENE_] = _scenes[_NORMAL_SCENE_]->texture();

    // Clean the screen otuput
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_BLEND);    // We don't want OpenGL make auto blend (alpha channel remains).

    /** In the GraphicEngine we only need to draw one quad that
     * will use the scenes textures and a shader to compute
     * the screen output.
     */
    glViewport(0, 0, (GLsizei) width(), (GLsizei) height());
    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-1.f,1.f,-1.f,1.f,-1.f,1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt( 0.f, 0.f,-0.5f, 0.f, 0.f, 0.f, 0.f, -1.f, 0.f);
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
    drawText();
    glLoadIdentity();
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

    float aspectRatio = (float)height/width;
    _cam->setAspectRatio(aspectRatio);
    for(int i=0; i < _N_SCENES_; i++) {
        _scenes[_NORMAL_SCENE_]->resize(width,height);
    }
}

void GraphicEngine::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Escape:
            _app->quit();
            break;
        default:
            break;
    }
}

void GraphicEngine::mouseDoubleClickEvent(QMouseEvent *event)
{
    switch(event->buttons())
    {
        case Qt::LeftButton:    // Translate camera
            _tree->cribNode(_tree->selectedNode());
            break;
        case Qt::RightButton:   // Rotate camera
            rotateCamera(event);
            break;
        default:                // Search & remarks nodes
            searchNode(event);
            break;
    }
}

void GraphicEngine::mouseMoveEvent(QMouseEvent *event)
{
    switch(event->buttons())
    {
        case Qt::LeftButton:    // Translate camera
            break;
        case Qt::RightButton:   // Rotate camera
            rotateCamera(event);
            break;
        default:                // Search & remarks nodes
            searchNode(event);
            break;
    }
    _lastMouseEvent = event->posF();
}

void GraphicEngine::rotateCamera(QMouseEvent *event)
{
    /** The movement of the camera is preformed in two parts,
     * ptiching in local coordinates, and heading in global
     * coordinates. The amount of rotation is selected with,
     * doing posible to rotate [-PI,PI] head angles, and [-PI/2,PI/2]
     * pitch angle in a single movement.
     */
    float head, pitch;
    QPointF pos = event->posF();
    Vec2f vec = Vec2f(pos.x() - _lastMouseEvent.x(), _lastMouseEvent.y() - pos.y());
    head = vec.x()/width();
    head *= M_PI;
    pitch = vec.y()/height();
    pitch *= M_PI;
    _cam->rotate(head,pitch);
}

void GraphicEngine::searchNode(QMouseEvent *event)
{
    // The position of mouse must be into [-1,1] range
    GLfloat x = 2.f*event->posF().x()/width() - 1.f;
    GLfloat y = 2.f*event->posF().y()/height() - 1.f;
    Vec3f pos = Vec3f(x, y, 0.f);

    /* ModelViewProjection matrix is capable to transform
     * 3D world-space coordinates of nodes into normalized
     * coordinates in camera space.
     */
    Mat4f modelViewProjMatrix = _cam->modelViewProjMatrix();
    _tree->setSelectedNode(0);
    _searchNode(_tree->root(), pos, modelViewProjMatrix);
}

void GraphicEngine::_searchNode(Node *node, Vec3f pos, Mat4f modelViewProjMatrix)
{
    Node* SelectedNode=_tree->selectedNode();
    const Nodes& nodes = node->children();

    // Recursive method
    if (!node->crib()) {
        for (int i = 0; i < (int)nodes.size(); ++i) {
            Node *child = nodes[i];
            _searchNode(child, pos, modelViewProjMatrix);
        }
    }
    // Active node
    Vec3f nodePos(node->x(), node->y(), node->z());
    Vec3f camSpacePos = modelViewProjMatrix*nodePos;
    /* Commented because w is ever equal 1 (Don't erase in order posibles changes)
        GLfloat w = viewProjMatrix[3][0] + viewProjMatrix[3][1] + viewProjMatrix[3][2] + viewProjMatrix[3][3];
        camSpacePos /= w;
    */
    Vec3f nodeToMouse = pos-camSpacePos;
    // If exist selected node, compare it
    if(SelectedNode) {
        nodePos = Vec3f(SelectedNode->x(), SelectedNode->y(), SelectedNode->z());
        camSpacePos = modelViewProjMatrix*nodePos;
        /* Commented because w is ever equal 1 (Don't erase in order posibles changes)
            w = viewProjMatrix[3][0] + viewProjMatrix[3][1] + viewProjMatrix[3][2] + viewProjMatrix[3][3];
            camSpacePos /= w;
        */
        Vec3f nodeToMouse2 = pos - camSpacePos;
        Vec2f nodeToMouse2D(nodeToMouse.x(), nodeToMouse.y());
        Vec2f nodeToMouse22D(nodeToMouse2.x(), nodeToMouse2.y());
        if(nodeToMouse22D.norm() > nodeToMouse2D.norm()) {
            _tree->setSelectedNode(node);
        }
    }
    // If not exist, we must analize it
    else {
        Vec2f nodeToMouse2D(nodeToMouse.x(), nodeToMouse.y());
        if(nodeToMouse2D.norm() < 40.f/width()){
            _tree->setSelectedNode(node);
        }
    }
}

void GraphicEngine::drawText()
{
    Node* _nodeMouse = _tree->selectedNode();
    if (_nodeMouse != NULL) {
        FTBBox box = _font->BBox(_nodeMouse->name().c_str());

        GLfloat dx = 2.f*(_lastMouseEvent.x()+16.f)/width() - 1.f;
        GLfloat dy = 2.f*(_lastMouseEvent.y()+16.f)/height() - 1.f;
        GLfloat dz = -0.1f;

        glColor3f(1.f, 1.f, 0.f);

        renderText(dx,dy,dz,_nodeMouse->name().c_str());
    }
}
