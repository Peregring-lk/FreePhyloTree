#ifndef _CLADE_VIEWER_
#define _CLADE_VIEWER_

#include "Engine.hpp"
#include "EventManager.hpp"
#include "Clade.hpp"
#include "StrategyMakeTree.hpp"

namespace FreePhyloTree
{
  enum BuildStrategy { SPHERE, COLLOID, GOURCEIAN };

  class CladeViewer
  {
  public:
    CladeViewer(Clade *clade, BuildStrategy strategy);
    ~CladeViewer();

    void initSignal();
    void flowStage();
    void killSignal();

    void moveCamera(float dx, float dy, float dz);

  private:
    Clade *_clade;

    Engine *_engine;
    EventManager *_eventMgr;

    StrategyMakeTree *_strategy;

    Ogre::SceneManager *_scene;
    Ogre::Camera *_camera;
    Ogre::Viewport *_vp;

    bool _continue;
  };
}

#endif
