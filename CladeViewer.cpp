#include <SDL/SDL.h>
#include <sstream>
#include "CladeViewer.hpp"
#include "SphereMakeTree.hpp"
#include "ColloidMakeTree.hpp"
#include "GourceianMakeTree.hpp"

using namespace std;
using namespace Ogre;
using namespace FreePhyloTree;
using namespace OIS;

CladeViewer::CladeViewer(Clade *clade, BuildStrategy strategy)
  : _clade(clade), _continue(true)
{
  _engine = new Engine(this);
  _eventMgr = new EventManager(this, _engine->getIDWindow());

  _scene = _engine->getOgre()->createSceneManager(ST_GENERIC,
						  "CladesWorld");

  _camera = _scene->createCamera("Camera");
  _camera->setPosition(Ogre::Vector3(0, 0, 100));
  _camera->setNearClipDistance(5);
  _camera->setFarClipDistance(1000);

  _vp = _engine->getWindow()->addViewport(_camera);

  if (strategy == SPHERE)
    _strategy = new SphereMakeTree(_scene);
  else if (strategy == COLLOID)
    _strategy = new ColloidMakeTree(_scene);
  else if (strategy == GOURCEIAN)
    _strategy = new GourceianMakeTree(_scene);

  _strategy->makeTreeClade(_clade, _scene->getRootSceneNode());
}

CladeViewer::~CladeViewer()
{
  delete _eventMgr;
  delete _engine;
  delete _strategy;
}

void CladeViewer::initSignal()
{
  _engine->initEngine();
}

void CladeViewer::flowStage()
{
  _eventMgr->refresh();
}

void CladeViewer::killSignal()
{
  _engine->killEngine();
}

void CladeViewer::moveCamera(float dx, float dy, float dz)
{
  _camera->move(Ogre::Vector3(dx, dy, dx));
}
