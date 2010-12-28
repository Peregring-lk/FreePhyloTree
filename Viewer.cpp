#include "Viewer.hpp"

#include "Engine.hpp"

using namespace FreePhyloTree;

Viewer::Viewer(PhyloTree *tree) : _tree(tree), _continue(true)
{
  _engine = new Engine(this);
}

Viewer::~Viewer()
{
  delete _engine;
  delete _tree;
}

PhyloTree* Viewer::tree() const
{
  return _tree;
}

void Viewer::run()
{
  _engine->initSignal();
  _tree->initSignal();
  SDL_Delay(200);

  while(_continue)
    _engine->flowStage();

  _engine->killSignal();
}

void Viewer::draw()
{
  _tree->draw();
}

void Viewer::killSignal()
{
  _continue = false;
}
