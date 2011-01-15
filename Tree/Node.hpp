/*
  Copyright (C) 2010 Aarón Bueno Villares <abv150ci@gmail.com>

  This file is part of FreePhyloTree.

  FreePhyloTree is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  FreePhyloTree is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with FreePhyloTree.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _NODE_
#define _NODE_

#include <string>
#include <vector>

#include "Color.hpp"
#include "Vec.hpp"

namespace FreePhyloTree
{
  typedef std::string Name;

  class Node;

  typedef int Label;
  typedef std::vector<Node*> Nodes;

  class Edge
  {
  public:
    Edge(Node *source, Node *target, int weight);

    Node* source() const;
    Node *target() const;
    int weight() const;

  private:
    Node *_source;
    Node *_target;

    int _weight;
  };

  //  typedef std::pair<Node*, Node*> Edge;
  typedef std::vector<Edge> Edges;

  //class Tree;

  class Node
  {
  public:
    Node(const Name& name, bool hide = false);

    Name name() const;
    Label label() const;
    bool crib() const;
    bool hide() const;
    float bloom() const;

    GLfloat r() const;
    GLfloat g() const;
    GLfloat b() const;

    GLfloat x() const;
    GLfloat y() const;

    const Color& color() const;
    const Vec3f& alloc() const;

    Node* father() const;
    const Nodes& children() const;

    unsigned degree() const;
    unsigned level() const;
    unsigned height() const;
    unsigned nodes() const;

    Node* root();

    void setColor(const Color& color);
    void setAlloc(const Vec3f& alloc);
    void setBloom(float bloom);
    void setCrib(bool crib);

    void move(const Vec3f& delta);

    friend class Tree;

  private:
    Name _name;
    Color _color;
    Vec3f _alloc;
    Label _label;
    bool _crib;

    Node *_father;
    Nodes _children;

    unsigned _level;
    unsigned _height;

    float _bloom;

    void _uploadHeight(Node *node);
  };
}

#endif
