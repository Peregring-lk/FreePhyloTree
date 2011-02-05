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
	Node(const Name& name);

	const Name& name() const;
	Label label() const;

	Node* father() const;
	const Nodes& children() const;

	virtual unsigned nodes() const;

/*
  unsigned degree() const;
  unsigned level() const;
  unsigned height() const;
*/

	Node* root();

	friend class Tree;

    protected:
	Name _name;
	Label _label;

	Node *_father;
	Nodes _children;

//    unsigned _level;
//    unsigned _height;

//    void _uploadHeight(Node *node);
    };
}

#endif
