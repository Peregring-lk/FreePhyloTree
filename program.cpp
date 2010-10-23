#include "StandardCladeViewer.hpp"

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
  StandardCladeViewer cladeViewer(createClade());

  cladeViewer.initSignal();
}
