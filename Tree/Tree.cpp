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

#include <cstdlib>
#include "Tree.hpp"

using namespace std;
using namespace FreePhyloTree;

Tree::Tree(const Name& name) : _name(name)
{
  _root = NULL;

  srand(time(NULL));

  _weight = 25;
}

Name Tree::name() const
{
  return _name;
}

const Nodes& Tree::nodes() const
{
  return _nodes;
}

const Edges& Tree::edges() const
{
  return _edges;
}
 
const Edges& Tree::noAdjs() const
{
  return _noAdjs;
}

Node* Tree::root() const
{
  return _root;
}

Node* Tree::node(Label label) const
{
  return _nodes[label];
}

unsigned Tree::height() const
{
  return _root->height();
}

unsigned Tree::order() const
{
  return _nodes.size();
}

void Tree::setRoot(Node *root)
{
  if (_nodes.size() == 0) {
    _newNode(root, NULL);
    _root = root;
    _root->setCrib(true);
  }
}

void Tree::setChild(Node *father, Node *child)
{
  if (father != NULL && child != NULL) {
    _newNode(child, father);

    child->_father = father;
    child->_level = father->_level + 1;

    father->_children.push_back(child);
    father->_uploadHeight(child);

    _moveEdge(father, child);
  }
}

void Tree::_newNode(Node *node, Node *father)
{
  if (_isNew(node)) {

    Label l = _nodes.size();

    for (int i = 0; i < l; ++i) {
      Node *source = _nodes[i];

      _noAdjs.push_back(Edge(source, node, _weight));
    }

    node->_label = l;
    _nodes.push_back(node);
  }
}

void Tree::_moveEdge(Node *source, Node *target)
{
  for (Edges::iterator i = _noAdjs.begin(); i != _noAdjs.end(); ++i) {
    Edge edge = *i;

    if (edge.source() == source && edge.target() == target) {
      _noAdjs.erase(i);
      _edges.push_back(edge);
      return;
    }
  }
}

bool Tree::_isNew(Node *node)
{
  return node != NULL && node->_father == NULL && node != _root;
}

Vec2f Tree::_rand(Node *father)
{
  GLfloat nx = rand() / (GLfloat)RAND_MAX;
  GLfloat ny = rand() / (GLfloat)RAND_MAX;

  nx = 30 * (1 - 2 * nx);
  ny = 30 * (1 - 2 * ny);

  Vec2f alloc(nx, ny);

  if (father != NULL) {
    alloc *= _root->height() / (father->level() + 1); 
    alloc += father->alloc();
  }

  return alloc;
}

void Tree::_rebootChildren(Node *father)
{
  const Nodes& children = father->children();

  for (int i = 0; i < children.size(); ++i) {
    Node *node = children[i];

    node->_alloc = _rand(father);

    if (!node->crib())
      _rebootChildren(node);
  }
}

void Tree::_initBloom(float bloom)
{
  for (int i = 0; i < _nodes.size(); ++i)
    _nodes[i]->setBloom(bloom);
}

void Tree::_reloadBloom(float bloom, float smooth)
{
  for (int i = 0; i < _nodes.size(); ++i) {
    float nodeBloom = _nodes[i]->bloom();
    float difBloom = nodeBloom - bloom;

    _nodes[i]->setBloom(nodeBloom - difBloom * smooth);
  }
}
