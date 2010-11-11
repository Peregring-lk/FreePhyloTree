#include <cmath>
#include <iostream>
#include "ColloidMakeTree.hpp"

using namespace FreePhyloTree;
using namespace Ogre;

ColloidMakeTree::ColloidMakeTree(SceneManager *scene)
  : StrategyMakeTree(scene)
{}

void ColloidMakeTree::makeTreeClade(Clade *clade,
				    Ogre::SceneNode *sceneNode)
{
  _scene->setAmbientLight(ColourValue::White);
  _makeTreeClade(clade, sceneNode, 0, 0);
}

void ColloidMakeTree::_makeTreeClade(Clade *clade, Ogre::SceneNode
				    *sceneNode, float dx, float dy)
{
  SceneNode *nodeScene = sceneNode->createChildSceneNode();

  Ogre::Light* pointLight = _scene->createLight();

  pointLight->setType(Light::LT_POINT);

  pointLight->setDiffuseColour(ColourValue::Green);
  pointLight->setSpecularColour(ColourValue::Green);

  nodeScene->attachObject(pointLight);
  nodeScene->attachObject(_makeColloid(500, 30));

  nodeScene->translate(dx, dy, 0);

  const std::vector<Clade*>& subclades = clade->getSubclades();
  float l = 0;
  for (std::vector<Clade*>::const_iterator i = subclades.begin();
       i != subclades.end(); ++i) {
    _makeTreeClade(*i, nodeScene, dx + 2000, dy + l);
    l -= 2000;
  }
}

ManualObject* ColloidMakeTree::_makeColloid(float r, float density)
{
  ManualObject *manual = _scene->createManualObject();
  manual->begin("BaseWhite", RenderOperation::OT_POINT_LIST);

  /*
  if (density < 0.01)
    density = 0.01;
  else if (density > 0.99)
     density = 0.99;
  */

  float rx = r;
  float step = density;

  for (float x = step - rx; x < rx; x += step) {
    float ry = sqrt(pow(rx, 2) - pow(abs(x), 2));

    for (float y = step - ry; y < ry; y += step) {
      float rz = sqrt(pow(ry, 2) - pow(abs(y), 2));

      for (float z = step - rz; z < rz; z += step)
	manual->position(x, y, z);
    }
  }

  manual->end();

  return (manual);
}
