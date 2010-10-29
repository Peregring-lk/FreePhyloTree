#include "CladeViewer.hpp"

using namespace FreePhyloTree;

Clade* createClade()
{
  Clade *life = new Clade("Life");
  Clade *primate = new Clade("Primate");
  Clade *carnivora = new Clade("Carnivora");

  life->attachClade(primate);
  life->attachClade(carnivora);

  return (life);
}

int main()
{
  CladeViewer cladeViewer(createClade(), SPHERE);

  cladeViewer.initSignal();
}
