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
// String libraries
// -------------------------------------------
#include <string>

// -------------------------------------------
// FreePhyloTree classes
// -------------------------------------------
#include "../PhyloTree.hpp"
#include "../Tree/Vec.hpp"

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
     */
    Camera(PhyloTree *tree);
    /// Destructor.
    ~Camera();

    /** Set viewport size
     * @param size Viewport size.
     */
    void SetSize(Vec2f size){_size = size;}
    /** Get viewport size
     * @return Viewport size.
     */
    Vec2f GetSize(){return _size;}

    /** Set camera position.
     * @param pos Position of the camera.
     */
    void SetPosition(Vec3f pos){_pos = pos;}
    /** Set camera view point.
     * @param aim Camera view point.
     * @note If any point is provided, center of scene
     * (0,0,0) sill be selected.
     */
    void SetAimingPoint(Vec3f aim=Vec3f(0.f,0.f,0.f)){_aim = aim;}
    /** Return camera position.
     * @return Position of the camera.
     */
    Vec3f GetPosition(){return _pos;}
    /** Return camera view point.
     * @return Camera view point.
     */
    Vec3f GetAimingPoint(){return _aim;}



private:
    /// Screen output tree
    PhyloTree *_tree;

    /// Viewport size
    Vec2f _size;

    /// Camera position
    Vec3f _pos;
    /// Camera direction
    Vec3f _aim;
};

}   // namespace FreePhyloTree

#endif // CAMERA_HPP_INCLUDED