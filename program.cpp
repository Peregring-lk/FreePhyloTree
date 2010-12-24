#include "CladeViewer.hpp"

using namespace std;
using namespace FreePhyloTree;

Clade* createClade()
{
  Clade *hominina = new Clade("Hominina");

  Clade *australopithecus = new Clade("Australopithecus");
  Clade *paranthropus = new Clade("Paranthropus");
  Clade *homo = new Clade("Homo");

  Clade *habilis = new Clade("Habilis");
  Clade *ergaster = new Clade("Ergaster");
  Clade *georgicus = new Clade("Georgicus");
  Clade *antecessor = new Clade("Antecessor");
  Clade *erectus = new Clade("Erectus");
  Clade *neanderthalensis = new Clade("Neanderthalensis");
  Clade *sapiens = new Clade("Sapiens");
  Clade *stupidus = new Clade("Stupidus");

  hominina->attachClade(australopithecus);
  hominina->attachClade(paranthropus);
  hominina->attachClade(homo);

  homo->attachClade(habilis);
  habilis->attachClade(georgicus);
  habilis->attachClade(ergaster);
  ergaster->attachClade(sapiens);
  georgicus->attachClade(stupidus);
  stupidus->attachClade(erectus);
  stupidus->attachClade(antecessor);
  antecessor->attachClade(neanderthalensis);

  return (hominina);
}

int main(int argc, char **argv)
{
  CladeViewer cladeViewer(createClade(), GOURCEIAN);

  cladeViewer.run();
}
