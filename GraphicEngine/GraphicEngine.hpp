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
// OpenGL libraries
// -------------------------------------------
#include<GL/glu.h>

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
#include <string>

// -------------------------------------------
// FreePhyloTree classes
// -------------------------------------------
#include "../FreePhyloTree.hpp"
#include "../PhyloTree.hpp"
#include "Canvas.hpp"

namespace FreePhyloTree
{

/** @class GraphicEngine GraphicEngine.h GraphicEngine/GraphicEngine.h
 * @brief Graphic engine controla el apartado visual, gestionando las
 * escenas, las camaras, la composicion, y la salida por pantalla. \n
 * Para ello, esta clase alberga un conjunto de escenas que renderizan
 * a texturas, y un compositor que las compone y devuelve la salida por
 * pantalla.
 * @note Este motor es la version 2.0.
 */
class GraphicEngine
{
public:
    /** Constructor.
     * @param app Main application
     * @param tree Screen output tree
     */
    GraphicEngine(QFreePhyloTree *app, PhyloTree *tree);
    /// Destructor.
    ~GraphicEngine();

private:
    /// Main application
    QFreePhyloTree *_app;
    /// Screen output tree
    PhyloTree *_tree;
    /// Main camera
    Camera *_cam;
    /// Output canvas
    Canvas *_canvas;
};

}   // namespace FreePhyloTree

#endif // GRAPHICENGINE_HPP_INCLUDED
