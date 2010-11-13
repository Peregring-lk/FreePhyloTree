#include "CladeViewer.hpp"
#include "GourceianMakeTree.hpp"

using namespace FreePhyloTree;

CladeViewer::CladeViewer(Clade *clade, DrawStrategy strategy)
  : _clade(clade), _continue(true)
{
  _engine = new Engine(this);

  if (strategy == GOURCEIAN)
    _strategy = new GourceianMakeTree();
}

CladeViewer::~CladeViewer()
{
  delete _engine;
  delete _strategy;
}

void CladeViewer::run()
{
  _engine->initSignal();
  _strategy->initSignal();

  while(_continue)
    _engine->flowStage();

  _engine->killSignal();
}

void CladeViewer::draw()
{
  _strategy->draw(_clade);
}

void CladeViewer::killSignal()
{
  _continue = false;
}
