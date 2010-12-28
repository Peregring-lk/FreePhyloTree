#include <cstdlib>
#include "Tree.hpp"

using namespace std;
using namespace FreePhyloTree;

Tree::Tree(const Name& name) : _name(name)
{
  _root = NULL;

  srand(time(NULL));
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
    _newNode(root);
    _root = root;
  }
}

void Tree::setChild(Node *father, Node *child)
{
  if (father != NULL && child != NULL) {
    _newNode(child);

    child->_father = father;
    child->_level = father->_level + 1;

    father->_children.push_back(child);
    father->_uploadHeight(child);

    _moveEdge(father, child);
  }
}

void Tree::_newNode(Node *node)
{
  if (_isNew(node)) {

    Label l = _nodes.size();

    for (int i = 0; i < l; ++i) {
      Node *source = _nodes[i];

      _noAdjs.push_back(make_pair(source, node));
    }

    node->_label = l;
    _nodes.push_back(node);

    node->_alloc.setAlloc(_rand(), _rand());
  }
}

void Tree::_moveEdge(Node *source, Node *target)
{
  for (Edges::iterator i = _noAdjs.begin(); i != _noAdjs.end(); ++i) {
    Edge edge = *i;

    if (edge.first == source && edge.second == target) {
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

float Tree::_rand()
{
  float n = rand();

  return 30 * (1 - 2 * n / (float)RAND_MAX);
}
