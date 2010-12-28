#ifndef _INTERVAL_
#define _INTERVAL_

#include "../Tree/Color.hpp"

namespace FreePhyloTree
{
  class Interval
  {
  public:
    Interval();
    Interval(const Color& inf, const Color& sup);

    Color inf() const;
    Color sup() const;

    Color center() const;

    void cut(TypeColor t, unsigned pieces, unsigned n);

  private:
    Color _inf;
    Color _sup;
  };
}

#endif
