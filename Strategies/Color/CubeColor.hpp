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

#include "../../VecXf/VecXf.hpp"

#ifndef _FPT_CUBE_COLOR_
#define _FPT_CUBE_COLOR_

namespace fpt
{
    typedef VecXf VecColor;
    typedef unsigned TypeC;

    class CubeColor
    {
    public:
	CubeColor();
	CubeColor(float r1, float g1, float b1,
		  float r2, float g2, float b2);
	CubeColor(const VecColor& inf, const VecColor& sup);

	const VecColor& inf() const;
	const VecColor& sup() const;

	VecColor center() const;

	void cut(TypeC color, unsigned pieces, unsigned n);

    private:
	VecColor _inf;
	VecColor _sup;
    };
}

#endif
