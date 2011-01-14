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

  Node *hominina = new Node("Hominina");

  Node *australopithecus = new Node("Australopithecus");
  Node *paranthropus = new Node("Paranthropus");
  Node *homo = new Node("Homo");
  Node *ardipithecus = new Node("Ardipithecus");
  Node *sahelanthropus = new Node("Sahelanthropus");
  Node *orrorin = new Node("Orrorin");
  Node *kenyanthropus = new Node("Kenyanthropus");

  tree->setRoot(hominina);
  tree->setChild(hominina, australopithecus);
  tree->setChild(hominina, paranthropus);
  tree->setChild(hominina, homo);
  tree->setChild(hominina, ardipithecus);
  tree->setChild(hominina, sahelanthropus);
  tree->setChild(hominina, orrorin);
  tree->setChild(hominina, kenyanthropus);

  Node *ramidus = new Node("Ardipithecus ramidus");
  Node *kadabba = new Node("Ardipithecus kadabba");

  tree->setChild(ardipithecus, ramidus);
  tree->setChild(ardipithecus, kadabba);

  Node *garhi = new Node("Australopithecus garhi");
  Node *africanus = new Node("Australopithecus africanus");
  Node *bahrelghazali = new Node("Australopithecus bahrelghazali");
  Node *sediba = new Node("Australopithecus sediba");
  Node *anamensis = new Node("Australopithecus anamensis");
  Node *afarensis = new Node("Australopithecus afarensis");

  tree->setChild(australopithecus, garhi);
  tree->setChild(australopithecus, africanus);
  tree->setChild(australopithecus, bahrelghazali);
  tree->setChild(australopithecus, anamensis);
  tree->setChild(australopithecus, sediba);
  tree->setChild(australopithecus, afarensis);

  Node *boisei = new Node("Paranthropus boisei");
  Node *robustus = new Node("Paranthropus robustus");
  Node *aethiopicus = new Node("Paranthropus aethiopicus");

  tree->setChild(paranthropus, aethiopicus);
  tree->setChild(paranthropus, boisei);
  tree->setChild(paranthropus, robustus);

  Node *habilis = new Node("Homo habilis");
  Node *ergaster = new Node("Homo ergaster");
  Node *sapiens = new Node("Homo sapiens");
  Node *erectus = new Node("Homo erectus");
  Node *antecessor = new Node("Homo antecessor");
  Node *neanderthalensis = new Node("Homo neanderthalensis");
  Node *heidelbergensis = new Node("Homo heidelbergensis");
  Node *georgicus = new Node("Homo georgicus");
  Node *rhodesiensis = new Node("Homo rhodesiensis");
  Node *rudolfensis = new Node("Homo rudolfensis");
  Node *cepranensis = new Node("Homo cepranensis");
  Node *floresiensis = new Node("Homo floresiensis");
  Node *gautengensis = new Node("Homo gautengensis");

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
