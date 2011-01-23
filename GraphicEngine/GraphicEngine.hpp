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

#ifndef GRAPHICENGINE_HPP_INCLUDED
#define GRAPHICENGINE_HPP_INCLUDED

// -------------------------------------------
// String libraries
// -------------------------------------------
#include <string>

// -------------------------------------------
// Qt OpenGL libraries
// -------------------------------------------
#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWebView>

// -------------------------------------------
// FreePhyloTree classes
// -------------------------------------------
#include "../PhyloTree.hpp"
#include "../Tree/Matrix.hpp"
#include "Scene.hpp"

// -------------------------------------------
// Defines for scenes
// -------------------------------------------
#ifndef _SCENES_DEFINES_
#define _SCENES_DEFINES_
    #define _N_SCENES_ 1
    #define _NORMAL_SCENE_ 0
#endif

namespace FreePhyloTree
{
  class QFreePhyloTree;

/** @class GraphicEngine GraphicEngine.h GraphicEngine/GraphicEngine.h
 * @brief Graphic engine controla el apartado visual, gestionando las
 * escenas, las camaras, la composicion, y la salida por pantalla. \n
 * Para ello, esta clase alberga un conjunto de escenas que renderizan
 * a texturas, y un compositor que las compone y devuelve la salida por
 * pantalla.
 * @note Este motor es la version 2.0.
 */
class GraphicEngine : public QGLWidget
{
    Q_OBJECT

public:
    /** Constructor.
     * @param app Main application
     * @param tree Screen output tree
     */
    GraphicEngine(QFreePhyloTree *app, PhyloTree *tree);
    /// Destructor.
    ~GraphicEngine();

    /** Returns the app
     * @return App
     */
    QFreePhyloTree* app();

    /** Returns a scene
     * @param id Identifier of the scene.
     * @return Scene.
     */
    Scene* scene(int id);

    /** Returns the openGL window size.
     * @return Window size.
     */
    Vec2f size();

public slots:
    /** Method called every frame in order to repaint the scene.
     */
    void animate();

private:
    /** Perform the initialization of the canvas.
     */
    void initializeGL();
    /** Perform canvas drawing
     */
    void paintGL();
    /** Resize the canvas.
     * @param width New width of the canvas.
     * @param height New height of the canvas.
     */
    void resizeGL(int width, int height);
    /** Answer the keyboard events.
     * @param event Keyboard event info.
     */
    void keyPressEvent(QKeyEvent *event);
    /** Answer the double click mouse events.
     * @param event double click mouse event info.
     */
    void mouseDoubleClickEvent(QMouseEvent *event);
    /** Answer the mouse move events.
     * @param event mouse move event info.
     */
    void mouseMoveEvent(QMouseEvent *event);

    /** Perform rotation camera by mouse.
     * @param event mouse move event info.
     */
    void rotateCamera(QMouseEvent *event);
    /** Look for selected node.
     * @param event mouse move event info.
     */
    void searchNode(QMouseEvent *event);
    /** Recursive method to look for the selected node.
     * @param node Tree root node.
     * @param pos Camera space position.
     * @param viewProjMatrix ModelViewProjection matrix.
     */
    Node* _searchNode(Node *node, Vec3f pos, Mat4f viewProjMatrix);

    /// Main application
    QFreePhyloTree *_app;
    /// Screen output tree
    PhyloTree *_tree;
    /// Main camera
    Camera *_cam;
    /// Scene
    Scene **_scenes;

    /// Widget size.
    Vec2f _size;

    /// Web viewer
    QWebView _webView;
    /// Web name
    const std::string _nameWeb;

    /// Preserve the last position of the mouse.
    QPointF _lastMouseEvent;
    /// Node selected
    Node* _nodeMouse;
};

}   // namespace FreePhyloTree

#endif // GRAPHICENGINE_HPP_INCLUDED
