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

/*! \file Strategy.cpp
 *  \brief Fichero que implementa a la clase \c fpt::Strategy.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2011
 *  \version 0.7
 *  \since 0.7
 */

#include "Strategy.hpp"

using namespace fpt;

Strategy::Strategy() : _initialized(false)
{}

Strategy::~Strategy()
{}

bool Strategy::initialized() const
{
    return _initialized;
}

bool Strategy::changed() const
{
    return false;
}

void Strategy::init()
{
    _init();

    _initialized = true;
}

void Strategy::step()
{
    if (initialized())
	_step();
}

void Strategy::_init()
{}

void Strategy::_step()
{}
