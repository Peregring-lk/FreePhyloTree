#ifndef _CLADE_VIEWER_
#define _CLADE_VIEWER_

#include "Clade.hpp"

namespace FreePhyloTree
{
  class CladeViewer
  {
  public:
    CladeViewer(Clade *clade)
      : _clade(clade) {}

    virtual ~CladeViewer() {}

    virtual void initSignal() = 0;
    virtual void flowStage() = 0;
    virtual void killSignal() = 0;

    virtual void moveCamera(float dx, float dy, float dz) = 0;

  protected:
    Clade *_clade;
  };
}

#endif
