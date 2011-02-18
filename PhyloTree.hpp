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

#ifndef _FPT_PHYLO_TREE_
#define _FPT_PHYLO_TREE_

#include <FTGL/ftgl.h>

#include "PhyloNode.hpp"
#include "Strategies/SpringLoc.hpp"
#include "Strategies/Coloring.hpp"

/** @namespace FreePhyloTree Space to all classes of FreePhyloTree.
 */
namespace fpt
{
    class Viewing;
    class GraphicEngine;

    /** @class PhyloTree PhyloTree.hpp PhyloTree.hpp
     * @brief Class of any phylogenetic tree.
     * @note Hierarched of Tree class, don't forgive
     * look for Tree class documentation to learn more
     * about this class.
     */
    class PhyloTree : public LocTree, public ColorTree
    {
    public:
	/** Constructor (default constructor is not allowed).
	 * @param name Name of the tree.
	 */
	PhyloTree(Name name);
	/** Destructor.
	 */
	~PhyloTree();

	/** Returns the center of the tree.
	 * @return Center of the tree.
	 */
	const Vec3f& centerPic() const;
	/** Returns the inferior Pic of the tree.
	 * @return Inferior Pic position of the tree.
	 */
	Vec3f infPic() const;
	/** Returns the superior Pic of the tree.
	 * @return Superior Pic position of the tree.
	 */
	Vec3f supPic() const;
	/** Returns the width of the tree.
	 * @return Width of the tree.
	 */
	float sidePic() const;
	PhyloNode* actualNode() const;

	/** Call to prepare the render of the scene.
	 * @param glEngine Main graphic engine.
	 */
	void initSignal(GraphicEngine *glEngine);

	/** Situate camera over root node.
	 */
	void gotoRoot();
	/** Set the camera looking direction.
	 * @param rel Relative position of point to aim.
	 * @remarks Relative to camera point must be provided,
	 * take care to don't use absolute coordinates.
	 */
	void lookAt(const Vec3f& rel);
	/** Set the position of mouse (to reach mouse aimed Pic if exist).
	 * @param loc Mouse position.
	 */
	void locMouse(const Vec3f& loc);
	/** Lookfor the node into the view space provided position.
	 * @param loc Position to lookfor a Pic.
	 */
	void cribNode(const Vec3f& loc);

	/** Draws the scene.
	 */
	void draw(Viewing *viewing);

    private:
	/// Texture to use
	GLuint textureid[3];

	/// Springs union positions vector
	SpringLoc *_loc;
	/// Colours vector
	Coloring *_coloring;
	/// Active font
	FTFont *_font;

	/// Main radius of any node
	float _radiusNode;
	/// Width of the edges
	float _radiusBeam;
	/// 1st bloom effect radius
	float _radiusBloom;
	/// Smoothing the bloom factor
	float _smoothBloom;

	/// Relative position of the root node to the camera
	Vec3f _relCamera;
	float _restSmoothCamera;
	float _smoothCamera;

	Vec3f _locMouse;
	PhyloNode *_nodeMouse;

	float _semisidePic;
	Vec3f _centerPic;

	/** Load textures.
	 * @param glEngine Main graphic engine.
	 */
	void _loadTextures(GraphicEngine *glEngine);

	/** Draws a tree by their root node.
	 * @param node Root node of the tree.
	 */
	void _drawNodes(PhyloNode *node);
	void _drawBlooms(PhyloNode *node);

	/** Draws an union edge between nodes.
	 * @param begin Begining node of the union.
	 * @param end Ending node of the union.
	 */
	void _drawEdge(PhyloNode *begin, PhyloNode *end);
	/** Draws a simple node.
	 * @param node Node to draw.
	 */
	void _drawNode(PhyloNode *node);
	/** Set colour of node.
	 * @param node Node to set colour.
	 */
	void _setColor(PhyloNode *node);
	/** Draws an squared plane.
	 * @param node Node where the plane must be drawed.
	 * @param side Width of plane.
	 * @param tex Texture to use.
	 */
	void _drawSquare(PhyloNode *node, float side, GLuint tex);

	/** Relocates the camera.
	 * @note This method uses information provided
	 * by lookat method.
	 */
	void _reloadCamera(Viewing *viewing);

	/** Lookfor the node into the provided viewspace coordinates.
	 * @param Viewspace coordinates where lookfor the node.
	 * @return Node reached, NULL (0) if anyone.
	 */
	PhyloNode* _searchNode(const Vec3f& loc);
	/** Crib a node.
	 * @param node Node to crib.
	 */
	void _cribNode(PhyloNode *node);

	/** Draw the text if needed.
	 * @note This method uses the info
	 * returned by _searchNode method.
	 */
	void _drawText();
    };
}

#endif
