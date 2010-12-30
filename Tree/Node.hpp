#ifndef _NODE_
#define _NODE_

#include <string>
#include <vector>

#include "Color.hpp"
#include "Vec2f.hpp"

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
    const Vec2f& alloc() const;

    Node* father() const;
    const Nodes& children() const;

    unsigned degree() const;
    unsigned level() const;
    unsigned height() const;

    Node* root();

    void setColor(const Color& color);
    void setAlloc(const Vec2f& alloc);
    void setBloom(float bloom);
    void setCrib(bool crib);

    void move(const Vec2f& delta);

    friend class Tree;

  private:
    Name _name;
    Color _color;
    Vec2f _alloc;
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
