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

#ifndef _FPT_SMOOTH_
#define _FPT_SMOOTH_

#include "Strategy.hpp"
#include "../VecXf/VecXf.hpp"

namespace fpt
{
    /*! \class Smooth
     *  \brief Suavizado de movimientos.
     *
     *  Ésta clase permite manejar objetos que, partiendo de un punto,
     *  se dirigen hacia otro punto, de forma suave, es decir,
     *  recorriendo el camino requerido según un ritmo especificado.
     */
    class Smooth : public Strategy
    {
    public:
	Smooth();
	Smooth(float gap, float smooth, float ssmoth = 1);

	float x() const;
	float y() const;
	float z() const;

	float gap() const;

	VecXf source() const;
	VecXf target() const;

	float originalSmooth() const;
	float actualSmooth() const;

	bool changed() const;

	void changeSource(const VecXf& source);
	void changeTarget(const VecXf& target);
	void changeSmooth(float smooth);

	float changeGap(float gap);

    protected:
	void _step();

    private:
	VecXf _source;
	VecXf _target;

	VecXf _dir;
	float _gap;

	float _originalSmooth;
	float _smooth;
	float _ssmooth;

	bool _changed;
    };
}

#endif
