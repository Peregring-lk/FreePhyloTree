#ifndef _GOURCEIAN_MAKE_TREE_
#define _GOURCEIAN_MAKE_TREE_

#include <GL/gl.h>

#include "StrategyMakeTree.hpp"

namespace FreePhyloTree
{
  class GourceianMakeTree : public StrategyMakeTree
  {
  public:
    void initSignal();

    void draw(Clade *clade);

  private:
    GLuint textureid[3];

    void _loadTextureNode();

    void _drawTreeClade(Clade *clade, float dx, float dy);

    void _drawEdge(float xO, float yO, float xD, float yD);
    void _drawBloom(float side, float x, float y);
    void _drawNode(float side, float x, float y);

  };
}

#endif
