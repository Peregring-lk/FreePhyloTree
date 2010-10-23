#include <SDL/SDL.h>
#include <sstream>
#include "StandardCladeViewer.hpp"

using namespace std;
using namespace Ogre;
using namespace FreePhyloTree;
using namespace OIS;

StandardCladeViewer::StandardCladeViewer(Clade *clade)
  : CladeViewer(clade), _continue(true)
{
  _engine = new Engine(this);
  _eventMgr = new EventManager(this, _engine->getIDWindow());

  _scene = _engine->getOgre()->createSceneManager(ST_GENERIC,
						  "CladesWorld");

  _camera = _scene->createCamera("Camera");
  _camera->setPosition(Ogre::Vector3(0,0,400));
  _camera->setNearClipDistance(5);
  _camera->setFarClipDistance(1000);

  _vp = _engine->getWindow()->addViewport(_camera);

  _createSphereMesh("meshNodeClade", 10);
  _makeTreeClade(_clade, _scene->getRootSceneNode(), "meshNodeClade");
}

StandardCladeViewer::~StandardCladeViewer()
{
  delete _engine;
  delete _eventMgr;
}

void StandardCladeViewer::initSignal()
{
  _engine->initEngine();
}

void StandardCladeViewer::flowStage()
{
  _eventMgr->refresh();
}

void StandardCladeViewer::killSignal()
{
  _engine->killEngine();
}

void StandardCladeViewer::moveCamera(float dx, float dy, float dz)
{
  _camera->move(Ogre::Vector3(dx, dy, dx));
}

void StandardCladeViewer::_makeTreeClade(Clade *clade, SceneNode *sceneNode,
				 string mesh, float dx, float dy)
{
  SceneNode *nodeScene = sceneNode->createChildSceneNode();
  Entity *nodeTree = _scene->createEntity(clade->getName(), mesh);

  nodeScene->attachObject(nodeTree);
  nodeScene->translate(dx, dy, 0);

  const std::vector<Clade*>& subclades = clade->getSubclades();
  float l = 0;
  for (std::vector<Clade*>::const_iterator i = subclades.begin();
       i != subclades.end(); ++i)
    {
      _makeTreeClade(*i, nodeScene, mesh, dx + 30, dy + l);
      l -= 30;
    }
}

void StandardCladeViewer::_createSphereMesh(string strName, float r,
					   int nRings, int nSegments)
{
  ManualObject * manual = _scene->createManualObject(strName);
  manual->begin("BaseWhiteNoLighting", RenderOperation::OT_TRIANGLE_LIST);

  float fDeltaRingAngle = (Math::PI / nRings);
  float fDeltaSegAngle = (2 * Math::PI / nSegments);
  unsigned short wVerticeIndex = 0 ;

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
	  manual->position( x0, y0, z0);
	  manual->normal(Ogre::Vector3(x0, y0, z0).normalisedCopy());
	  manual->textureCoord((float) seg / (float) nSegments,
			       (float) ring / (float) nRings);

	  if (ring != nRings)
	    {
	      // each vertex (except the last) has six indicies pointing to it
	      manual->index(wVerticeIndex + nSegments + 1);
	      manual->index(wVerticeIndex);
	      manual->index(wVerticeIndex + nSegments);
	      manual->index(wVerticeIndex + nSegments + 1);
	      manual->index(wVerticeIndex + 1);
	      manual->index(wVerticeIndex);
	      wVerticeIndex ++;
	    }
	}; // end for seg
    } // end for ring
   manual->end();

   MeshPtr mesh = manual->convertToMesh(strName);
   mesh->_setBounds(AxisAlignedBox(Ogre::Vector3(-r, -r, -r),
				   Ogre::Vector3(r, r, r)),
		    false);

   mesh->_setBoundingSphereRadius(r);

   unsigned short src, dest;
   if (!mesh->suggestTangentVectorBuildParams(VES_TANGENT, src, dest))
     mesh->buildTangentVectors(VES_TANGENT, src, dest);
}
