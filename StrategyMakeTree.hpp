#ifndef _STRATEGY_MAKE_TREE_
#define _STRATEGY_MAKE_TREE_

#include <OGRE/Ogre.h>
#include "Clade.hpp"

namespace FreePhyloTree
{
  class StrategyMakeTree
  {
  public:
    StrategyMakeTree(Ogre::SceneManager *scene) : _scene(scene) {};

    virtual void
    makeTreeClade(Clade *clade, Ogre::SceneNode *sceneNode) = 0;

  protected:
    Ogre::SceneManager *_scene;
  };
}

#endif
