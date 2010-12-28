#ifndef _ALLOC_
#define _ALLOC_

#include "../Tree/Tree.hpp"

namespace FreePhyloTree
{
  class SpringAlloc
  {
  public:
    SpringAlloc(float c1, float c2, float c3, float c4);

    void reAlloc(Tree *tree);

  private:
    float _c1;
    float _c2;
    float _c3;
    float _c4;

    typedef std::vector<Vec2f> _Moves;
    _Moves _moves;

    void _fa(Node *source, Node *target);
    void _fr(Node *source, Node *target);
  };
}

#endif
