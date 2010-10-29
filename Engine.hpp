#ifndef _FPT_ENGINE_
#define _FPT_ENGINE_

#include <OGRE/Ogre.h>

namespace FreePhyloTree
{
  class CladeViewer;

  class Engine : public Ogre::FrameListener
  {
  public:
    Engine(CladeViewer *cladeViewer);
    ~Engine();

    Ogre::Root* getOgre();
    Ogre::RenderWindow* getWindow();

    size_t getIDWindow();

    void initEngine();
    void killEngine();

    bool frameStarted(const Ogre::FrameEvent &evt);
    bool frameEnded(const Ogre::FrameEvent &evt);

  private:
    Ogre::Root *_ogre;
    Ogre::RenderWindow *_window;

    CladeViewer *_cladeViewer;

    bool _continue;

    void _loadResources();
  };
}

#endif
