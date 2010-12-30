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

    node->_alloc = _rand(father);
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

  if (father != NULL) {
    nx = father->x() + nx;
    ny = father->y() + ny;
  }

  return Vec2f(nx, ny);
}
