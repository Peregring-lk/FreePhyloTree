#include "CladeViewer.hpp"

using namespace FreePhyloTree;

Clade* createClade()
{
  Clade *life = new Clade("Life");
  Clade *carnivora = new Clade("Carnivora");

  Clade *primate = new Clade("Primate");
  Clade *hominina = new Clade("Hominina");
  Clade *panina = new Clade("Panina");

  Clade *australopithecus = new Clade("Australopithecus");
  Clade *paranthropus = new Clade("Paranthropus");
  Clade *homo = new Clade("Homo");

  life->attachClade(carnivora);
  life->attachClade(primate);
  primate->attachClade(hominina);
  primate->attachClade(panina);

  hominina->attachClade(australopithecus);
  hominina->attachClade(paranthropus);
  hominina->attachClade(homo);

  return (life);
}

int main(int argc, char **argv)
{
  CladeViewer cladeViewer(createClade(), GOURCEIAN);

  cladeViewer.run();
}
