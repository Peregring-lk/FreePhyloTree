#include <iostream>
#include "Viewer.hpp"

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

  tree->setRoot(hominina);
  tree->setChild(hominina, australopithecus);
  tree->setChild(hominina, paranthropus);
  tree->setChild(hominina, homo);
  tree->setChild(hominina, ardipithecus);

  Node *garhi = new Node("Garhi");
  Node *africanus = new Node("Africanus");
  Node *robustus = new Node("Robustus");

  tree->setChild(australopithecus, garhi);
  tree->setChild(australopithecus, africanus);
  tree->setChild(australopithecus, robustus);

  Node *habilis = new Node("Habilis");
  Node *ergaster = new Node("Ergaster");
  Node *sapiens = new Node("Sapiens");

  tree->setChild(homo, habilis);
  tree->setChild(homo, ergaster);
  tree->setChild(homo, sapiens);

  return (tree);
}

int main(int argc, char **argv)
{
  Viewer viewer(createClade());

  viewer.run();
}
