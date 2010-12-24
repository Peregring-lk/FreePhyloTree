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

    void draw(Node *node);

  private:
    GLuint textureid[3];

    void _loadTextures();

    void _drawTree(Node *node, float dx, float dy);

    void _drawEdge(Node *begin, Node *end, float xO, float yO,
		   float xD, float yD, float _thick);
    void _drawBloom(Node *node, float side, float x, float y);
    void _drawNode(Node *node, float side, float x, float y);

  };
}

#endif
