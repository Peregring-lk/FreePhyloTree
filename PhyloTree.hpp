#ifndef _DRAW_TREE_
#define _DRAW_TREE_

#include "Tree/Tree.hpp"
#include "Strategies/Alloc.hpp"

namespace FreePhyloTree
{
  class PhyloTree : public Tree
  {
  public:
    PhyloTree(Name name);
    ~PhyloTree();

    void initSignal();
    
    void draw();

  private:
    GLuint textureid[3];
    SpringAlloc *_alloc;

    void _loadTextures();

    void _drawTree(Node *node);

    void _drawEdge(Node *begin, Node *end, float _thick);
    void _drawNode(Node *node, float bloom, float side);
    void _selectColor(Node *node);
    void _drawSquare(Node *node, float side, GLuint tex);
  };
}

#endif
