#ifndef _CLADE_
#define _CLADE_

#include <string>
#include <vector>

namespace FreePhyloTree
{
  class Clade;
  typedef std::vector<Clade*> Subclades;

  class Clade
  {
  public:
    Clade(std::string name);

    std::string getName() const;

    const Subclades& getSubclades() const;
    Clade* getSuperclade() const;

    void attachClade(Clade *clade);

  private:
    std::string _name;

    Subclades _subclades;
    Clade* _superclade;

    void setSuperclade(Clade *clade);
  };
}

#endif
