#ifndef _FPT_EVENT_MANAGER_
#define _FPT_EVENT_MANAGER_

#include <OIS/OIS.h>
#include "CladeViewer.hpp"

namespace FreePhyloTree
{
  class EventManager : public OIS::KeyListener,
		       public OIS::MouseListener
  {
  public:
    EventManager(CladeViewer* _cladeViewer, size_t idWindow);
    ~EventManager();

    bool keyPressed(const OIS::KeyEvent &arg);
    bool keyReleased(const OIS::KeyEvent &arg);

    bool mouseMoved(const OIS::MouseEvent &arg);
    bool mousePressed(const OIS::MouseEvent &arg,
		      OIS::MouseButtonID id);
    bool mouseReleased(const OIS::MouseEvent &arg,
		       OIS::MouseButtonID id);

    void refresh();

  private:
    OIS::InputManager *_inputMgr;
    OIS::Keyboard *_keyboard;
    OIS::Mouse *_mouse;
    CladeViewer *_cladeViewer;

    OIS::MouseState _mouseState;
  };
}

#endif
