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
    class Smooth : public Strategy
    {
    public:
	Smooth();
	Smooth(float smooth, float ssmoth = 1);

	VecXf source() const;
	VecXf target() const;

	float originalSmooth() const;
	float actualSmooth() const;

	void init();
	void step();

	void changeSource(const VecXf& source);
	void changeTarget(const VecXf& target);
	void changeSmooth(float smooth);

    private:
	VecXf _source;
	VecXf _target;

	VecXf _dir;

	float _originalSmooth;
	float _smooth;
	float _ssmooth;

	bool _initialized;
    };
}

#endif
