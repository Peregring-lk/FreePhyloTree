#include "GourceianMakeTree.hpp"

using namespace FreePhyloTree;
using namespace Ogre;

GourceianMakeTree::GourceianMakeTree(SceneManager *scene)
  : StrategyMakeTree(scene)
{}

void
GourceianMakeTree::makeTreeClade(Clade *clade, SceneNode *sceneNode)
{
  _scene->setAmbientLight(ColourValue::Red);
  _makeTreeClade(clade, sceneNode, 0, 0);
}

void
GourceianMakeTree::_makeTreeClade(Clade *clade, SceneNode *sceneNode,
				  float dx, float dy)
{
  SceneNode *nodeScene = sceneNode->createChildSceneNode();

  nodeScene->attachObject(_createNode(10, clade->getName()));
  nodeScene->translate(dx, dy, 0);

  const std::vector<Clade*>& subclades = clade->getSubclades();
  float l = 0;
  for (std::vector<Clade*>::const_iterator i = subclades.begin();
       i != subclades.end(); ++i)
    {
      _makeTreeClade(*i, nodeScene, dx + 20, dy + l);
      l -= 20;
    }
}

Entity*
GourceianMakeTree::_createNode(float side, String name)
{
  String namePlane = name + "Plane";

  MeshManager::getSingleton().createPlane(name + "Plane",
					  ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
					  Plane(0, 0, 1, 0),
					  side, side);//, 1, 1, true, 1,
  //					  1.0f, 1.0f, Vector3(0, 0, 1));

  Entity* node = _scene->createEntity(name, namePlane);
  node->setMaterialName("FreePhyloTree/matNode");
  node->setCastShadows(false);

  return (node);
  /*

  ManualObject *manual = _scene->createManualObject();

  manual->setCastShadows(false);
  manual->begin("FreePhyloTree/matNode", RenderOperation::OT_TRIANGLE_LIST);

  manual->position(0, 0, 0);
  manual->textureCoord(0, 0);

  manual->position(5, 0, 0);
  manual->textureCoord(1, 0);

  manual->position(5, 5, 0);
  manual->textureCoord(1, 1);

  manual->position(0, 5, 0);
  manual->textureCoord(0, 1);

  manual->triangle(0, 1, 2);
  manual->triangle(0, 2, 3);

  manual->end();

  return (manual);*/
}
