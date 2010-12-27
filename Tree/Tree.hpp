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

    void _newNode(Node *node);
    void _moveEdge(Node *source, Node *target);
    bool _isNew(Node *node);

    float _rand();
  };
}

#endif
