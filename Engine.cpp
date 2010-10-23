#include <SDL/SDL.h>
#include "Engine.hpp"

using namespace Ogre;
using namespace FreePhyloTree;

Engine::Engine(CladeViewer *cladeViewer)
  : _cladeViewer(cladeViewer), _continue(true)
{
  _ogre = new Root;

  if (!_ogre->restoreConfig())
    _ogre->showConfigDialog();

  _ogre->initialise(false);

  _window = _ogre->createRenderWindow("FreePhyloTree", 400, 400,
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
  // Load resource paths from config file
  ConfigFile cf;
  cf.load("resources.cfg");

  // Go through all sections & settings in the file
  ConfigFile::SectionIterator seci = cf.getSectionIterator();
  String secName, typeName, archName;

  while(seci.hasMoreElements())
    {
      secName = seci.peekNextKey();

      ConfigFile::SettingsMultiMap *settings = seci.getNext();
      ConfigFile::SettingsMultiMap::iterator i;

      for (i = settings->begin(); i != settings->end(); ++i)
	{
	  typeName = i->first;
	  archName = i->second;

	  _ogre->addResourceLocation(archName, typeName, secName);
	}
    }

  ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}
