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

#ifndef _TREE_
#define _TREE_

#include "Node.hpp"

namespace FreePhyloTree
{
  class Tree
  {
  public:
    Tree(const Name& name);

    Name name() const;

    const Nodes& nodes() const;
    const Edges& edges() const;
    const Edges& noAdjs() const;

    Node* root() const;
    Node* node(Label label) const;

    unsigned height() const;
    unsigned order() const;

    void setRoot(Node *root);
    void setChild(Node *father, Node *child);

  protected:
    Name _name;
    Node *_root;

    Nodes _nodes;
    Edges _edges;
    Edges _noAdjs;

    int _weight;

    void _newNode(Node *node, Node *father);
    void _moveEdge(Node *source, Node *target);
    bool _isNew(Node *node);

    Vec2f _rand(Node *father);
    void _rebootChildren(Node *father);

    void _initBloom(float bloom);
    void _reloadBloom(float bloom, float smooth);
  };
}

#endif
