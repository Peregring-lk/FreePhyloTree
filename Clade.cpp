#include "Clade.hpp"

using namespace std;
using namespace FreePhyloTree;

Clade::Clade(string name)
  :_name(name), _superclade(NULL)
{}

string Clade::getName() const
{
  return (_name);
}

const vector<Clade*>& Clade::getSubclades() const
{
  return (_subclades);
}

Clade* Clade::getSuperclade() const
{
  return (_superclade);
}

void Clade::attachClade(Clade *clade)
{
  _subclades.push_back(clade);

  clade->setSuperclade(this);
}

void Clade::setSuperclade(Clade *clade)
{
  _superclade = clade;
}
