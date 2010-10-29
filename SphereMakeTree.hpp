#ifndef _SPHERE_MAKE_TREE_
#define _SPHERE_MAKE_TREE_

#include "StrategyMakeTree.hpp"

namespace FreePhyloTree
{
  class SphereMakeTree : public StrategyMakeTree
  {
  public:
    SphereMakeTree(Ogre::SceneManager* scene);

    void makeTreeClade(Clade *clade, Ogre::SceneNode *sceneNode);

  private:
    void _makeTreeClade(Clade *clade, Ogre::SceneNode *sceneNode,
			float dx, float dy);

    Ogre::ManualObject* _createSphere(float r, int nRings = 16,
				      int nSegments = 16);
  };
}

#endif
