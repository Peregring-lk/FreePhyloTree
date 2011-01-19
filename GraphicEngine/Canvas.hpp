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

#ifndef CANVAS_HPP_INCLUDED
#define CANVAS_HPP_INCLUDED

// -------------------------------------------
// OpenGL libraries
// -------------------------------------------
//#include<GL/glu.h>

// -------------------------------------------
// Qt OpenGL libraries
// -------------------------------------------
#include <QApplication>
#include <QGLWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWebView>

// -------------------------------------------
// String libraries
// -------------------------------------------
#include <iostream>
#include <string>

// -------------------------------------------
// FreePhyloTree classes
// -------------------------------------------
#include "Camera.hpp"
#include "../PhyloTree.hpp"

namespace FreePhyloTree
{

    class GraphicEngine;

/** @class Canvas Canvas.h GraphicEngine/Canvas.h
 * @brief Esta clase es la salida por pantalla. Recibe la informacion
 * de las escenas renderizadas, y las compone en la salida por pantalla.
 * @note Clase empleada en el motor grafico 2.0.
 * @warning Don't forgive use the method Create after all scenes exist.
 */
class Canvas : public QGLWidget
{
    Q_OBJECT

public:
    /** Constructor.
     * @param ge Main graphic engine
     * @param tree Screen output tree
     * @param cam Main camera
     */
    Canvas(GraphicEngine *ge, PhyloTree *tree, Camera *cam);
    /// Destructor.
    ~Canvas();

    /** Returns the openGL window size.
     * @return Window size.
     */
    Vec2f GetSize(){return _size;}

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

    /// Main graphic engine
    GraphicEngine *_ge;
    /// Screen output tree
    PhyloTree *_tree;
    /// Main camera
    Camera *_cam;

    /// Widget size.
    Vec2f _size;

    /// Web viewer
    QWebView _webView;
    /// Web name
    const std::string _nameWeb;
};

}   // namespace FreePhyloTree


#endif // CANVAS_HPP_INCLUDED
