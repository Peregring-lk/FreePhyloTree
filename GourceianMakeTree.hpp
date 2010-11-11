#ifndef _GOURCEIAN_MAKE_TREE_
#define _GOURCEIAN_MAKE_TREE_

#include <OGRE/Ogre.h>
#include "StrategyMakeTree.hpp"

namespace FreePhyloTree
{
  class GourceianMakeTree : public StrategyMakeTree
  {
  public:
    GourceianMakeTree(Ogre::SceneManager *scene);

    void makeTreeClade(Clade *clade, Ogre::SceneNode *sceneNode);

  private:
    void _makeTreeClade(Clade *clade, Ogre::SceneNode *sceneNode,
			float dx, float dy);

    Ogre::Entity* _createNode(float side, Ogre::String);
  };
}

#endif
