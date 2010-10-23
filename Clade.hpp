#ifndef _CLADE_
#define _CLADE_

#include <string>
#include <vector>

namespace FreePhyloTree
{
  class Clade
  {
  public:
    Clade(std::string name);

    std::string getName() const;

    const std::vector<Clade*>& getSubclades() const;
    Clade* getSuperclade() const;

    void attachClade(Clade *clade);

  private:
    std::string _name;

    std::vector<Clade*> _subclades;
    Clade* _superclade;

    void setSuperclade(Clade *clade);
  };
}

#endif
