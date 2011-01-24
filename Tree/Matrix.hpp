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

#ifndef MATRIX_HPP_INCLUDED
#define MATRIX_HPP_INCLUDED

// -------------------------------------------
// Standart libraries
// -------------------------------------------
#include <stdio.h>
#include <string>
#include <math.h>

// -------------------------------------------
// FreePhyloTree classes
// -------------------------------------------
#include "Vec.hpp"

namespace FreePhyloTree
{

/** @class Mat4f Matrix.h Tree/Matrix.h
 * @brief 4x4 float matrix, usefull for apply transformations
 * to objects. \n
 * i.e.- Used to find the selected node.
 * @note Applied in graphic engine 2.0.
 */
class Mat4f
{
public:
    /** Constructor.
     * @note Default constructor build identity matrix.
     */
    Mat4f(  GLfloat x00=1, GLfloat x01=0, GLfloat x02=0, GLfloat x03=0,
            GLfloat x10=0, GLfloat x11=1, GLfloat x12=0, GLfloat x13=0,
            GLfloat x20=0, GLfloat x21=0, GLfloat x22=1, GLfloat x23=0,
            GLfloat x30=0, GLfloat x31=0, GLfloat x32=0, GLfloat x33=1);
    /** Copy constructor.
     * @param mat Matrix to copy.
     */
    Mat4f(const Mat4f& mat);
    /// Destructor.
    ~Mat4f();

    /** Resturn data.
     * @param row Row index.
     */
    GLfloat* operator[] (const int& row) const;
    /** Assign operator.
     * @param mat Matrix to add.
     */
    void operator= (const Mat4f& mat) const;
    /** Operator to add matrix.
     * @param mat Matrix to add.
     * @return Resultant matrix.
     */
    Mat4f operator+ (const Mat4f& mat) const;
    /** Operator to substract matrix.
     * @param mat Matrix to substract.
     * @return Resultant matrix.
     */
    Mat4f operator- (const Mat4f& mat) const;
    /** Operator to multiply matrix.
     * @param mat Multiplier Matrix.
     * @return Resultant matrix.
     */
    Mat4f operator* (const Mat4f& mat) const;
    /** Operator to multiply by vector.
     * @param vec Multiplier vector.
     * @return Resultant Vector.
     * @remarks w component fo input/output vector
     * will be assumed as 1.
     */
    Vec3f operator* (const Vec3f& vec) const;

    /** Operator to add matrix.
     * @param mat Matrix to add.
     * @return Resultant matrix.
     */
    Mat4f operator+= (const Mat4f& mat) const;
    /** Operator to substract matrix.
     * @param mat Matrix to substract.
     * @return Resultant matrix.
     */
    Mat4f operator-= (const Mat4f& mat) const;
    /** Operator to multiply matrix.
     * @param mat Multiplier Matrix.
     */
    Mat4f operator*= (const Mat4f& mat) const;

    void debugprint();

private:
    /// Array of values
    GLfloat **m;
};

}   // namespace FreePhyloTree

#endif // MATRIX_HPP_INCLUDED
