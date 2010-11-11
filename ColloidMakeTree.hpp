#ifndef _LIGHT_MAKE_TREE_
#define _LIGHT_MAKE_TREE_

#include "StrategyMakeTree.hpp"

namespace FreePhyloTree
{
  class ColloidMakeTree : public StrategyMakeTree
  {
  public:
    ColloidMakeTree(Ogre::SceneManager *scene);

    void makeTreeClade(Clade *clade, Ogre::SceneNode *sceneNode);

  private:
    void _makeTreeClade(Clade *clade, Ogre::SceneNode *sceneNode,
			float dx, float dy);

    Ogre::ManualObject* _makeColloid(float r, float density);
  };
}

#endif
