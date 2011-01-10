#include "FreePhyloTree.hpp"

using namespace FreePhyloTree;

QFreePhyloTree::QFreePhyloTree(PhyloTree *tree, int argc, char **argv)
  : QApplication(argc, argv), _glEngine(tree)
{}

void QFreePhyloTree::run()
{
  _glEngine.resize(400, 400);
  _glEngine.show();
}
