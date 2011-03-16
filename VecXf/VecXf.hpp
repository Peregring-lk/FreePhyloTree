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

#ifndef _FPT_VECXF_
#define _FPT_VECXF_

#include <iostream>

namespace fpt
{
    /*! \typedef Dim
     *  \brief Dimensión de un vector, usado para especificar
     *  coordenadas.
     */
    typedef unsigned Dim;

    /*! \class VecXf
     *  \brief Tipo vector de la aplicación.
     *
     *  Tipo vector, de 3 dimensiones, con sobrecarga de los
     *  operadores usuales para manejo de vector, y funciones para
     *  obtener otras propiedades comunes de los vectores, como su norma
     *  o el vector unitario.
     *
     *  \note Llamamos a ésta clase VecXf en vez de Vec3f porque
     *  originalmente la clase servía como vector abstracto para n
     *  dimensiones, usando el mecanismo de \c variadic \c templates
     *  de c++0x en la construcción. Se desechó dicha idea por
     *  cuestiones de eficiencia, aunque se conserva el nombre.
     */
    class VecXf
    {
    public:
	VecXf(const VecXf& center, float radius);
	VecXf(float x = 0, float y = 0, float z = 0);

	float norm() const;
	VecXf unit() const;

	float coord(Dim dim) const;

	float x() const;
	float y() const;
	float z() const;

	VecXf operator- () const;

	VecXf operator+ (const VecXf& vec) const;
	VecXf operator- (const VecXf& vec) const;

	VecXf operator+ (float k) const;
	VecXf operator- (float k) const;
	VecXf operator* (float k) const;
	VecXf operator/ (float k) const;

	bool inRadius(const VecXf& vec, float radius) const;

	VecXf& operator+= (const VecXf& vec);
	VecXf& operator-= (const VecXf& vec);

	VecXf& operator+= (float k);
	VecXf& operator-= (float k);
	VecXf& operator*= (float k);
	VecXf& operator/= (float k);

	void clear();

	void setX(float value);
	void setY(float value);
	void setZ(float value);

	void setCoord(Dim dim, float value);

    protected:
	float _x;
	float _y;
	float _z;

	mutable float _norm;

    private:
	mutable bool _upToDateNorm;

	void _calcNorm() const;
    };
}

#endif
