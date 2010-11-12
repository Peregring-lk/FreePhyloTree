#include <GL/glut.h>

#include "CladeViewer.hpp"
#include "GourceianMakeTree.hpp"

using namespace FreePhyloTree;

CladeViewer::CladeViewer(Clade *clade, BuildStrategy strategy)
  : _clade(clade)
{
  _engine = new Engine(this);
  _eventMgr = new EventManager(this);

  if (strategy == GOURCEIAN)
    _strategy = new GourceianMakeTree();
}

CladeViewer::~CladeViewer()
{
  delete _eventMgr;
  delete _engine;
  delete _strategy;
}

void CladeViewer::init(int argc, char **argv)
{
  _engine->init(argc, argv);
  _strategy->init();
  _eventMgr->init();

  glutMainLoop();
}

void CladeViewer::kill()
{
  _engine->kill();
}
