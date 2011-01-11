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

  Node *ramidus = new Node("Ramidus");
  Node *kadabba = new Node("Kadabba");

  tree->setChild(ardipithecus, ramidus);
  tree->setChild(ardipithecus, kadabba);

  Node *garhi = new Node("Garhi");
  Node *africanus = new Node("Africanus");
  Node *bahrelghazali = new Node("Bahrelghazali");
  Node *sediba = new Node("Sediba");
  Node *anamensis = new Node("Anamensis");
  Node *afarensis = new Node("Afarensis");

  tree->setChild(australopithecus, garhi);
  tree->setChild(australopithecus, africanus);
  tree->setChild(australopithecus, bahrelghazali);
  tree->setChild(australopithecus, anamensis);
  tree->setChild(australopithecus, sediba);
  tree->setChild(australopithecus, afarensis);

  Node *boisei = new Node("Boisei");
  Node *robustus = new Node("Robustus");
  Node *aethiopicus = new Node("Aethiopicus");

  tree->setChild(paranthropus, aethiopicus);
  tree->setChild(paranthropus, boisei);
  tree->setChild(paranthropus, robustus);

  Node *habilis = new Node("Habilis");
  Node *ergaster = new Node("Ergaster");
  Node *sapiens = new Node("Sapiens");
  Node *erectus = new Node("Erectus");
  Node *antecessor = new Node("Antecessor");
  Node *neanderthalensis = new Node("Neanderthalensis");
  Node *heidelbergensis = new Node("Heidelbergensis");
  Node *georgicus = new Node("Georgicus");
  Node *rhodesiensis = new Node("Rhodesiensis");
  Node *rudolfensis = new Node("Rudolfensis");
  Node *cepranensis = new Node("Cepranensis");
  Node *floresiensis = new Node("Floresiensis");
  Node *gautengensis = new Node("Gautengensis");

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

int main(int argc, char **argv)
{
  QFreePhyloTree fpt(createClade(), argc, argv);

  fpt.run();

  return fpt.exec();
}
