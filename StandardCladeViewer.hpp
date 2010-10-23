#ifndef _STANDARD_CLADE_VIEWER_
#define _STANDARD_CLADE_VIEWER_

#include "CladeViewer.hpp"
#include "Engine.hpp"
#include "EventManager.hpp"

namespace FreePhyloTree
{
  class StandardCladeViewer : public CladeViewer
  {
  public:
    StandardCladeViewer(Clade *clade);
    ~StandardCladeViewer();

    void initSignal();
    void flowStage();
    void killSignal();

    void moveCamera(float dx, float dy, float dz);

  private:
    Engine *_engine;
    EventManager *_eventMgr;

    Ogre::SceneManager *_scene;
    Ogre::Camera *_camera;
    Ogre::Viewport *_vp;

    bool _continue;

    void _makeTreeClade(Clade *_clade, Ogre::SceneNode *sceneNode,
			float dx = 0, float dy = 0);

    Ogre::ManualObject* _createSphere(float r, int nRings = 16,
				      int nSegments = 16);
  };
}

#endif
