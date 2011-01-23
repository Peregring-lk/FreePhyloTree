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
 * una textura. Una vez construida la clase se debe llamar al metodo
 * create para completar el proceso.
 * @note Clase empleada en el motor grafico 2.0.
 * @remarks Esta clase se diseña para ser sobrecargada.
 */
class Scene
{
public:
    /** Constructor.
     * @param width Width of the canvas.
     * @param hegiht Hegiht of the canvas.
     * @param tree Screen output tree.
     * @param cam Main camera.
     * @param context Active context.
     * @remarks This method only construct the class,
     * you must call create method after calling this.
     */
    Scene(int width, int height, PhyloTree *tree, Camera *cam, QGLContext *context);
    /// Destructor.
    ~Scene();
    /** Method that finish the construction process.
     */
    void create();

    /** Resize the offscreen frame buffer.
     * @param width Width of the canvas.
     * @param hegiht Hegiht of the canvas.
     */
    void resize(int width, int height);

    /** Returns the rendered scene
     * @return Texture with rendered scene
     */
    GLuint texture();

    /** Renders the scene.
     * @warning This method Calls Draw function, that must
     * be overloaded in your class.
     */
    void render();

private:
    /** Load the textures.
     * @warning This method is virtual, but probably you don't need
     * overload it. Don't forgive construct the textures array.
     */
    virtual void loadTextures();

    /** Draws the scene.
     * @warning This method is pure virtual, so must
     * be overloaded in your class.
     * @note This method could be used to draw the tree with
     * normal orthodromic camera, only for development purposes.
     */
    virtual void draw();

    /** Draws a tree.
     * @warning This method is virtual, but probably you don't need
     * overload it.
     * @param node Tree root node.
     */
    virtual void drawTree(Node *node);

    /** Draws a union edge.
     * @warning This method is virtual, but probably you don't need
     * overload it.
     * @param source Origin node of the edge.
     * @param target End node of the edge.
     */
    virtual void drawEdge(Node *source, Node *target);

    /** Draws a node.
     * @warning This method is virtual, but probably you don't need
     * overload it.
     * @param node Node to draw.
     */
    virtual void drawNode(Node *node);

    /** Draws a squared plane.
     * @param node Node that contains info about the position.
     * @param radius Size of the plane to draw
     * @param tex Texture to use.
     */
    virtual void drawPlane(Node *node, float radius, GLuint tex);

    /** Draws text (selected node).
     * @warning This method is virtual, but probably you don't need
     * overload it.
     */
    virtual void drawText();

    /// Width of the canvas and offscreen buffer
    int _width;
    /// Height of the canvas and offscreen buffer
    int _height;
    /// Screen output tree
    PhyloTree *_tree;
    /// Main camera
    Camera *_cam;
    /// OpenGL context
    QGLContext *_context;
    /// Rendered scene object
    QGLFramebufferObject *_rttObject;

    /// Main text font
    FTFont *_font;

    /// Textures array
    GLuint *_textureid;
};

}   // namespace FreePhyloTree



#endif // SCENE_HPP_INCLUDED
