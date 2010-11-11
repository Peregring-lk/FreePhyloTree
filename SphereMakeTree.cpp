#include "SphereMakeTree.hpp"

using namespace FreePhyloTree;
using namespace Ogre;

SphereMakeTree::SphereMakeTree(SceneManager *scene)
  : StrategyMakeTree(scene)
{}

void SphereMakeTree::makeTreeClade(Clade *clade,
				   Ogre::SceneNode *sceneNode)
{
  _scene->setAmbientLight(ColourValue::Red);
  _makeTreeClade(clade, sceneNode, 0, 0);
}

void SphereMakeTree::_makeTreeClade(Clade *clade, Ogre::SceneNode
				    *sceneNode, float dx, float dy)
{
  SceneNode *nodeScene = sceneNode->createChildSceneNode();

  nodeScene->attachObject(_createSphere(10));
  nodeScene->translate(dx, dy, 0);

  const std::vector<Clade*>& subclades = clade->getSubclades();
  float l = 0;
  for (std::vector<Clade*>::const_iterator i = subclades.begin();
       i != subclades.end(); ++i)
    {
      _makeTreeClade(*i, nodeScene, dx + 30, dy + l);
      l -= 30;
    }
}

ManualObject*
SphereMakeTree::_createSphere(float r, int nRings, int nSegments)
{
  ManualObject *manual = _scene->createManualObject();
  manual->begin("BaseWhite", RenderOperation::OT_TRIANGLE_LIST);

  float fDeltaRingAngle = (Math::PI / nRings);
  float fDeltaSegAngle = (2 * Math::PI / nSegments);
  unsigned short wVerticeIndex = 0;

  // Generate the group of rings for the sphere
  for(int ring = 0; ring <= nRings; ring++)
    {
      float r0 = r * sinf (ring * fDeltaRingAngle);
      float y0 = r * cosf (ring * fDeltaRingAngle);

      // Generate the group of segments for the current ring
      for(int seg = 0; seg <= nSegments; seg++)
	{
	  float x0 = r0 * sinf(seg * fDeltaSegAngle);
	  float z0 = r0 * cosf(seg * fDeltaSegAngle);

	  // Add one vertex to the strip which makes up the sphere
	  manual->position(x0, y0, z0);
	  //	  manual->normal(Ogre::Vector3(x0, y0, z0));
	  //manual->textureCoord((float)seg / (float)nSegments,
	  //		       (float)ring / (float)nRings);

	  if (ring != nRings)
	    {
	      // each vertex (except the last) has six indicies pointing to it
	      manual->index(wVerticeIndex + nSegments + 1);
	      manual->index(wVerticeIndex);
	      manual->index(wVerticeIndex + nSegments);
	      manual->index(wVerticeIndex + nSegments + 1);
	      manual->index(wVerticeIndex + 1);
	      manual->index(wVerticeIndex);
	      wVerticeIndex++;
	    }
	}; // end for seg
    } // end for ring
  manual->end();

  return (manual);
}
