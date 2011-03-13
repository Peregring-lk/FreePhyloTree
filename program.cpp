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

// This lines is only for Doxygen documentation
/** @mainpage
 * FreePhyloTree by Aarón Bueno Villares <abv150ci@gmail.com>.\n
 * A free phylogenetic trees editor. Please, visit the
 * <a href="http://freephylotree.blogspot.com/" >blog (Spanish)</a>
 * to learn more about FreePhyloTree.
 * This web page contains the developers info.\n
 * The entry point of the program is the main.cpp,
 * but this function just boots the application object,
 * QFreePhyloTree.\n
 */

#include <iostream>
#include "FreePhyloTree.hpp"

using namespace fpt;

/** \brief
 * Entry point of the program, just boots the application object.
 *   @param  argc Number of terminal arguments
 *   @param  argv Array of terminal arguments
 *   @return Error id, 0 if any error happens.
 */
int main(int argc, char **argv)
{
    QFreePhyloTree fpt(argc, argv);

    fpt.run();

    return fpt.exec();
}
