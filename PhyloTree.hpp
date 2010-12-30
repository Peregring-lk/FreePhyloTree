/*
  Copyright (C) 2010 Aarón Bueno Villares <abv150ci@gmail.com>

  This file is part of FreePhyloTree.

  FreePhyloTree is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  GoM is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with FreePhyloTree.  If not, see <http://www.gnu.org/licenses/>.
*/

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
