#include "GLEngine.hpp"

using namespace FreePhyloTree;

GLEngine::GLEngine(PhyloTree *tree) : _tree(tree)
{}

GLEngine::~GLEngine()
{
  delete _tree;
}

void GLEngine::initializeGL()
{
  _tree->initSignal();
}

void GLEngine::paintGL()
{
  _tree->draw();
}
