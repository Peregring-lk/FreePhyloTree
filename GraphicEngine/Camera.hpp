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

#ifndef CAMERA_HPP_INCLUDED
#define CAMERA_HPP_INCLUDED

// -------------------------------------------
// Standar libraries
// -------------------------------------------
#include <string>
#include <math.h>

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
#include "../Tree/Vec.hpp"
#include "../Tree/Matrix.hpp"

namespace FreePhyloTree
{

/** @class Camera Camera.h GraphicEngine/Camera.h
 * @brief Esta clase controla la camara, entendiendo como tal
 * los parametros que la afectan (posicion, direccion, tamaño, etc.).
 * @note Clase empleada en el motor grafico 2.0.
 */
class Camera
{
public:
    /** Constructor.
     * @param tree Arbol a descargar en el visual
     * @param aspectRatio Aspect ratio of the OpenGL window.
     * @remarks Aspect ratio is defines as width / height.
     */
    Camera(PhyloTree *tree, float aspectRatio);
    /// Destructor.
    ~Camera();

    void initSignal();

    /** Set aspect ratio.
     * @param aspectRatio Aspect ratio of the OpenGL window.
     * @remarks Aspect ratio is defines as width / height.
     */
    void setAspectRatio(float aspectRatio);

    /** Get aspect ratio.
     * @return Aspect ratio of the OpenGL window.
     * @remarks Aspect ratio is defines as width / height.
     */
    float aspectRatio();

    /** Get viewport size
     * @return Viewport size.
     */
    Vec3f size();

    /** Set camera position.
     * @param pos Position of the camera.
     */
    void setPosition(Vec3f pos);
    /** Set camera view point.
     * @param aim Camera view point.
     * @note If any point is provided, center of scene
     * (0,0,0) sill be selected.
     */
    void setAimingPoint(Vec3f aim=Vec3f(0.f,0.f,0.f));
    /** Return camera position.
     * @return Position of the camera.
     */
    Vec3f position() const;
    /** Return camera view point.
     * @return Camera view point.
     */
    Vec3f aimingPoint() const;
    /** Return up vector of the camera.
     * @return Up vector.
     */
    Vec3f up() const;

    /** Return camera view direction.
     * @return Normalized view direction.
     */
    Vec3f viewDirection();

    /** Resize the viewport of the camera.
     */
    void resize();

    /** Rotate the camera.
     * @param head Heading angle (rad).
     * @param pitch Pitch angle (rad).
     * @note The rotation angle will be accumulated.
     */
     void rotate(float head, float pitch);

    /** Return view-projection matrix.
     * @return View-projection matrix.
     */
    Mat4f modelViewProjMatrix() const;
private:
    /** Setup model-view-projection matrix.
     * @param OpenGL If true, let OpenGL sets the matrix
     * (strongly recommended). \n
     * Otherwise the class try to calculate it.
     */
    void setupModelViewProjMatrix(bool OpenGL=true);
    /** OpenGL sets the model-view-projection matrix.
     */
    Mat4f getModelViewProjMatrix() const;
    /** Class recalculates model-view-projection matrix.
     */
    Mat4f recalcModelViewProjMatrix() const;


    /** Recalculates up vector
     */
    void reCalcUp();


    /// Screen output tree
    PhyloTree *_tree;

    /// Viewport size
    Vec3f _size;
    /// Aspect ratio
    float _aspectRatio;

    /// Camera position
    Vec3f _pos;
    /// Camera direction
    Vec3f _aim;
    /// Up viewer vector
    Vec3f _up;

    /// model-view-projection matrix
    Mat4f _modelViewProjMatrix;
};

}   // namespace FreePhyloTree

#endif // CAMERA_HPP_INCLUDED
