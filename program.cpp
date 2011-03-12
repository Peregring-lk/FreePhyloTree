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

using namespace std;
using namespace fpt;

PhyloTree* createClade()
{
    PhyloNode *hominina = new PhyloNode("Hominina");

    PhyloNode *australopithecus = new PhyloNode("Australopithecus",
						hominina);
    PhyloNode *paranthropus = new PhyloNode("Paranthropus", hominina);
    PhyloNode *homo = new PhyloNode("Homo", hominina);
    PhyloNode *ardipithecus = new PhyloNode("Ardipithecus", hominina);
    PhyloNode *sahelanthropus = new PhyloNode("Sahelanthropus",
					      hominina);
    PhyloNode *orrorin = new PhyloNode("Orrorin", hominina);
    PhyloNode *kenyanthropus = new PhyloNode("Kenyanthropus",
					     hominina);

    PhyloNode *ramidus = new PhyloNode("Ardipithecus ramidus",
				       ardipithecus);
    PhyloNode *kadabba = new PhyloNode("Ardipithecus kadabba",
				       ardipithecus);

    PhyloNode *garhi = new PhyloNode("Australopithecus garhi",
				     australopithecus);
    PhyloNode *africanus = new PhyloNode("Australopithecus africanus",
					 australopithecus);
    PhyloNode *bahrelghazali = new PhyloNode("Australopithecus bahrelghazali", australopithecus);
    PhyloNode *sediba = new PhyloNode("Australopithecus sediba",
				      australopithecus);
    PhyloNode *anamensis = new PhyloNode("Australopithecus anamensis",
					 australopithecus);
    PhyloNode *afarensis = new PhyloNode("Australopithecus afarensis",
					 australopithecus);

    PhyloNode *boisei = new PhyloNode("Paranthropus boisei", paranthropus);
    PhyloNode *robustus = new PhyloNode("Paranthropus robustus", paranthropus);
    PhyloNode *aethiopicus = new PhyloNode("Paranthropus aethiopicus",
					   paranthropus);


    PhyloNode *habilis = new PhyloNode("Homo habilis", homo);
    PhyloNode *ergaster = new PhyloNode("Homo ergaster", homo);
    PhyloNode *sapiens = new PhyloNode("Homo sapiens", homo);
    PhyloNode *erectus = new PhyloNode("Homo erectus", homo);
    PhyloNode *antecessor = new PhyloNode("Homo antecessor", homo);
    PhyloNode *neanderthalensis = new PhyloNode("Homo neanderthalensis", homo);
    PhyloNode *heidelbergensis = new PhyloNode("Homo heidelbergensis",
					       homo);
    PhyloNode *georgicus = new PhyloNode("Homo georgicus", homo);
    PhyloNode *rhodesiensis = new PhyloNode("Homo rhodesiensis", homo);
    PhyloNode *rudolfensis = new PhyloNode("Homo rudolfensis", homo);
    PhyloNode *cepranensis = new PhyloNode("Homo cepranensis", homo);
    PhyloNode *floresiensis = new PhyloNode("Homo floresiensis", homo);
    PhyloNode *gautengensis = new PhyloNode("Homo gautengensis",
    homo);

    PhyloTree *tree = new PhyloTree("Hominina", hominina,
				    3, 40, 200, 6);

    return (tree);
}

/** \brief
 * Entry point of the program, just boots the application object.
 *   @param  argc Number of terminal arguments
 *   @param  argv Array of terminal arguments
 *   @return Error id, 0 if any error happens.
 */
int main(int argc, char **argv)
{
    QFreePhyloTree fpt(createClade(), argc, argv);

    fpt.run();

    return fpt.exec();
}
