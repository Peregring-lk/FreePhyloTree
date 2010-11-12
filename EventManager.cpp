#include <GL/glut.h>

#include "EventManager.hpp"

using namespace FreePhyloTree;

void EventManager::init()
{
  glutMouseFunc(mouse);
}

void EventManager::mouse(int button, int state, int x, int y)
{}

