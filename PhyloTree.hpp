#ifndef _DRAW_TREE_
#define _DRAW_TREE_

#include <FTGL/ftgl.h>

#include "Strategies/Alloc.hpp"
#include "Strategies/Coloring.hpp"

namespace FreePhyloTree
{
  class PhyloTree : public Tree
  {
  public:
    PhyloTree(Name name);
    ~PhyloTree();

    const Vec2f& centerPic() const;
    Vec2f infPic() const;
    Vec2f supPic() const;
    float sidePic() const;

    void initSignal();

    void gotoRoot();
    void lookAt(const Vec2f& rel);
    void allocMouse(const Vec2f& alloc);
    void cribNode(const Vec2f& alloc);
    
    void draw();

  private:
    GLuint textureid[3];

    SpringAlloc *_alloc;
    Coloring *_coloring;

    FTFont *_font;

    float _radiusNode;
    float _radiusBeam;
    float _radiusBloom;
    float _smoothBloom;

    Vec2f _relCamera;
    float _restSmoothCamera;
    const float _smoothCamera;

    Vec2f _allocMouse;
    Node *_nodeMouse;

    float _sidePic;
    Vec2f _centerPic;

    void _loadTextures();

    void _drawTree(Node *node);

    void _drawEdge(Node *begin, Node *end);
    void _drawNode(Node *node);
    void _setColor(Node *node);
    void _drawSquare(Node *node, float side, GLuint tex);

    void _reloadCamera();

    Node* _searchNode(const Vec2f& alloc);
    void _cribNode(Node *node);

    void _drawText();
  };
}

#endif
