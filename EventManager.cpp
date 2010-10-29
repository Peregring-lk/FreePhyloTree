#include "EventManager.hpp"
#include "CladeViewer.hpp"
#include <sstream>

using namespace OIS;
using namespace FreePhyloTree;

EventManager::EventManager(CladeViewer *cladeViewer, size_t idWindow)
  : _cladeViewer(cladeViewer)
{
  ParamList plOIS;
  std::ostringstream idWndwStr;

  idWndwStr << idWindow;

  plOIS.insert(std::make_pair("WINDOW", idWndwStr.str()));
  plOIS.insert(std::make_pair("x11_keyboard_grab", "false"));
  plOIS.insert(std::make_pair("x11_mouse_grab", "false"));
  plOIS.insert(std::make_pair("x11_mouse_hide", "false"));

  _inputMgr = InputManager::createInputSystem(plOIS);

  _keyboard = (Keyboard*)_inputMgr->createInputObject(OISKeyboard,
						      true);
  _mouse = (Mouse*)_inputMgr->createInputObject(OISMouse,
						true);

  _keyboard->setEventCallback(this);
  _mouse->setEventCallback(this);

  _mouseState = _mouse->getMouseState();
}

EventManager::~EventManager()
{
  _inputMgr->destroyInputObject(_keyboard);
  _inputMgr->destroyInputObject(_mouse);

  InputManager::destroyInputSystem(_inputMgr);
}

bool EventManager::keyPressed(const OIS::KeyEvent &arg)
{
  if (arg.key == KC_ESCAPE)
    _cladeViewer->killSignal();

  return (true);
}

bool EventManager::keyReleased(const OIS::KeyEvent &arg)
{}

bool EventManager::mouseMoved(const MouseEvent &arg)
{
  if (arg.state.buttonDown(MB_Left))
      _cladeViewer->moveCamera(arg.state.X.abs - _mouseState.X.abs,
			       arg.state.Y.abs - _mouseState.Y.abs,
			       arg.state.Z.abs - _mouseState.Z.abs);

  _mouseState = arg.state;
}

bool EventManager::mousePressed(const MouseEvent &arg, MouseButtonID id)
{}

bool EventManager::mouseReleased(const MouseEvent &arg, MouseButtonID id)
{}

void EventManager::refresh()
{
  _keyboard->capture();
  _mouse->capture();
}
