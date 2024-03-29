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

/*! \file FreePhyloTree.cpp
 *  \brief Implementación de la clase \c fpt::QFreePhyloTree.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2011
 *  \version 0.7
 *  \since 0.7
 */

#include "FreePhyloTree.hpp"

using namespace fpt;

QFreePhyloTree::QFreePhyloTree(int argc, char **argv)
    : QApplication(argc, argv), _qTimer(this)
{
    _glEngine = new GraphicEngine("Neomura");
}

QFreePhyloTree::~QFreePhyloTree()
{
    delete _glEngine;
}

void QFreePhyloTree::init()
{
    connect(&_qTimer, SIGNAL(timeout()), _glEngine, SLOT(animate()));
    _qTimer.start(40);

    _glEngine->show();
}
