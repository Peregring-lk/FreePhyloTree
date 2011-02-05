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

#ifndef _INTERVAL_
#define _INTERVAL_

#include "Color.hpp"

namespace FreePhyloTree
{
  class Interval
  {
  public:
    Interval();
    Interval(const Color& inf, const Color& sup);

    Color inf() const;
    Color sup() const;

    Color center() const;

    void cut(TypeColor t, unsigned pieces, unsigned n);

  private:
    Color _inf;
    Color _sup;
  };
}

#endif
