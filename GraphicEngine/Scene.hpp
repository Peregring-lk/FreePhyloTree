/*
  Copyright (C) 2011 Aarón Bueno Villares <abv150ci@gmail.com>

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

#ifndef _FPT_SCENE_
#define _FPT_SCENE_

#include <vector>
#include <GL/gl.h>
#include <FTGL/ftgl.h>

#include "../PhyloTree.hpp"
#include "Mouse.hpp"

namespace fpt
{
    /*! \class Scene
     *  \brief Clase que renderiza la escena completa.
     *
     *  Ésta clase, fundamentalmente, se dedica a renderizar el árbol
     *  (\c PhyloTree) y a mostrar el texto de los nodos señalados con
     *  el ratón.
     *
     *  \sa Viewing
     *  \sa Mouse
     *
     */
    class Scene : public Strategy
    {
    public:
	Scene(PhyloTree *tree, Mouse *_mouse);
	~Scene();

	bool changed() const;
	bool describedNodes() const;

	GLuint textureNode() const;
	GLuint textureGlow() const;
	GLuint textureEdge() const;

	void setTextureNode(GLuint id);
	void setTextureGlow(GLuint id);
	void setTextureEdge(GLuint id);

	void describeAllNodes(bool describe = true);

    protected:
	void _init();
	void _step();

    private:
	std::vector<PhyloNode*> _seenNodes;

	PhyloTree *_tree;
	Mouse *_mouse;

	FTFont *_font;

	GLuint _textureIDnode;
	GLuint _textureIDglow;
	GLuint _textureIDedge;

	bool _initTexNode;
	bool _initTexGlow;
	bool _initTexEdge;

	float _radiusNode;
	float _weightEdge;

	bool _describeNodes;
	bool _showHelp;

	void _drawTree();
	void _drawNode(PhyloNode *node);
	void _drawGlow(PhyloNode *node);
	void _drawEdge(PhyloNode *source, PhyloNode *target);

	void _drawSquare(PhyloNode *node, float side, GLuint tex);
	void _setColor(PhyloNode *node);

	void _drawText(PhyloNode *node);
	void _drawHelp();
    };
}

#endif
