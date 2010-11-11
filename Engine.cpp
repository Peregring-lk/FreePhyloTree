#include <SDL/SDL.h>
#include "Engine.hpp"
#include "CladeViewer.hpp"

using namespace Ogre;
using namespace FreePhyloTree;

Engine::Engine(CladeViewer *cladeViewer)
  : _cladeViewer(cladeViewer), _continue(true)
{
  _ogre = new Root;

  if (!_ogre->restoreConfig())
    _ogre->showConfigDialog();

  _ogre->initialise(false);

  _window = _ogre->createRenderWindow("FreePhyloTree", 560, 420,
				      false);

  _loadResources();

  _ogre->addFrameListener(this);
}

Engine::~Engine()
{
  delete _ogre;
}

Root* Engine::getOgre()
{
  return (_ogre);
}

RenderWindow* Engine::getWindow()
{
  return (_window);
}

size_t Engine::getIDWindow()
{
  size_t idWindow;

  _window->getCustomAttribute("WINDOW", &idWindow);

  return (idWindow);
}

void Engine::initEngine()
{
  _ogre->startRendering();
}

void Engine::killEngine()
{
  _continue = false;
}

bool Engine::frameStarted(const FrameEvent &evt)
{
  SDL_Delay(40);

  _cladeViewer->flowStage();

  if (_continue && _window->isClosed())
    _cladeViewer->killSignal();

  return (true);
}

bool Engine::frameEnded(const FrameEvent &evt)
{
  return (_continue);
}

void Engine::_loadResources()
{
  _ogre->addResourceLocation("./Resources", "FileSystem", "General");

  ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}
