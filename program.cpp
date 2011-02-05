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
using namespace FreePhyloTree;

PhyloTree* createClade()
{
  PhyloTree *tree = new PhyloTree("Hominina");

  PhyloNode *hominina = new PhyloNode("Hominina");

  PhyloNode *australopithecus = new PhyloNode("Australopithecus");
  PhyloNode *paranthropus = new PhyloNode("Paranthropus");
  PhyloNode *homo = new PhyloNode("Homo");
  PhyloNode *ardipithecus = new PhyloNode("Ardipithecus");
  PhyloNode *sahelanthropus = new PhyloNode("Sahelanthropus");
  PhyloNode *orrorin = new PhyloNode("Orrorin");
  PhyloNode *kenyanthropus = new PhyloNode("Kenyanthropus");

  tree->setRoot(hominina);
  tree->setChild(hominina, australopithecus);
  tree->setChild(hominina, paranthropus);
  tree->setChild(hominina, homo);
  tree->setChild(hominina, ardipithecus);
  tree->setChild(hominina, sahelanthropus);
  tree->setChild(hominina, orrorin);
  tree->setChild(hominina, kenyanthropus);

  PhyloNode *ramidus = new PhyloNode("Ardipithecus ramidus");
  PhyloNode *kadabba = new PhyloNode("Ardipithecus kadabba");

  tree->setChild(ardipithecus, ramidus);
  tree->setChild(ardipithecus, kadabba);

  PhyloNode *garhi = new PhyloNode("Australopithecus garhi");
  PhyloNode *africanus = new PhyloNode("Australopithecus africanus");
  PhyloNode *bahrelghazali = new PhyloNode("Australopithecus bahrelghazali");
  PhyloNode *sediba = new PhyloNode("Australopithecus sediba");
  PhyloNode *anamensis = new PhyloNode("Australopithecus anamensis");
  PhyloNode *afarensis = new PhyloNode("Australopithecus afarensis");

  tree->setChild(australopithecus, garhi);
  tree->setChild(australopithecus, africanus);
  tree->setChild(australopithecus, bahrelghazali);
  tree->setChild(australopithecus, anamensis);
  tree->setChild(australopithecus, sediba);
  tree->setChild(australopithecus, afarensis);

  PhyloNode *boisei = new PhyloNode("Paranthropus boisei");
  PhyloNode *robustus = new PhyloNode("Paranthropus robustus");
  PhyloNode *aethiopicus = new PhyloNode("Paranthropus aethiopicus");

  tree->setChild(paranthropus, aethiopicus);
  tree->setChild(paranthropus, boisei);
  tree->setChild(paranthropus, robustus);

  PhyloNode *habilis = new PhyloNode("Homo habilis");
  PhyloNode *ergaster = new PhyloNode("Homo ergaster");
  PhyloNode *sapiens = new PhyloNode("Homo sapiens");
  PhyloNode *erectus = new PhyloNode("Homo erectus");
  PhyloNode *antecessor = new PhyloNode("Homo antecessor");
  PhyloNode *neanderthalensis = new PhyloNode("Homo neanderthalensis");
  PhyloNode *heidelbergensis = new PhyloNode("Homo heidelbergensis");
  PhyloNode *georgicus = new PhyloNode("Homo georgicus");
  PhyloNode *rhodesiensis = new PhyloNode("Homo rhodesiensis");
  PhyloNode *rudolfensis = new PhyloNode("Homo rudolfensis");
  PhyloNode *cepranensis = new PhyloNode("Homo cepranensis");
  PhyloNode *floresiensis = new PhyloNode("Homo floresiensis");
  PhyloNode *gautengensis = new PhyloNode("Homo gautengensis");

  tree->setChild(homo, habilis);
  tree->setChild(homo, ergaster);
  tree->setChild(homo, sapiens);
  tree->setChild(homo, erectus);
  tree->setChild(homo, antecessor);
  tree->setChild(homo, neanderthalensis);
  tree->setChild(homo, heidelbergensis);
  tree->setChild(homo, georgicus);
  tree->setChild(homo, rhodesiensis);
  tree->setChild(homo, rudolfensis);
  tree->setChild(homo, cepranensis);
  tree->setChild(homo, floresiensis);
  tree->setChild(homo, gautengensis);

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
