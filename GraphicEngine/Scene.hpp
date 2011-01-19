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

#ifndef SCENE_HPP_INCLUDED
#define SCENE_HPP_INCLUDED

// -------------------------------------------
// OpenGL libraries
// -------------------------------------------
#include<GL/glu.h>

// -------------------------------------------
// Qt OpenGL libraries
// -------------------------------------------
#include <QGLFramebufferObject>

// -------------------------------------------
// String libraries
// -------------------------------------------
#include <string>

// -------------------------------------------
// FreePhyloTree classes
// -------------------------------------------
#include "Camera.hpp"
#include "../PhyloTree.hpp"

namespace FreePhyloTree
{

/** @class Scene Scene.h GraphicEngine/Scene.h
 * @brief Esta clase controla la escena, devolviendo la salida a
 * una textura.
 * @note Clase empleada en el motor grafico 2.0.
 * @remarks Esta clase se diseña para ser sobrecargada.
 */
class Scene
{
public:
    /** Constructor.
     * @param tree Screen output tree.
     * @param cam Main camera.
     * @param context Active context.
     */
    Scene(PhyloTree *tree, Camera *cam, QGLContext *context);
    /// Destructor.
    ~Scene();

    /** Returns the rendered scene
     * @return Texture with rendered scene
     */
    GLuint GetTexture(){return _rttObject->texture();}

    /** Renders the scene.
     * @warning This method Calls Draw function, that must
     * be overloaded in your class.
     */
    void Render();

private:
    /** Draws the scene.
     * @warning This method is pure virtual, so must
     * be overloaded in your class.
     * @note This method could be used to draw the tree with
     * normal orthodromic camera, only for development purposes.
     */
    virtual void Draw();


    /// Screen output tree
    PhyloTree *_tree;
    /// Main camera
    Camera *_cam;
    /// OpenGL context
    QGLContext *_context;
    /// Rendered scene object
    QGLFramebufferObject *_rttObject;
};

}   // namespace FreePhyloTree



#endif // SCENE_HPP_INCLUDED
