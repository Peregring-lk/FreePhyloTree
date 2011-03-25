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

#ifndef _FPT_VIEWING_
#define _FPT_VIEWING_

#include "../PhyloTree.hpp"

#include <GL/gl.h>

namespace fpt
{
    /*! \class Viewing
     *  \brief Clase de visionado de la aplicación.
     *
     *  Ésta clase se encarga de controlar el cuadro de visionado y
     *  los movimientos de la cámara.
     *
     *  \note No la he llamado clase \c Camera, porque no solo trata
     *  la cámara, sino también el \a viewport.
     *
     */
    class Viewing : public Strategy
    {
    public:
	Viewing(PhyloTree *tree, GLsizei width, GLsizei height,
		float minRatio = 10.0f / 7,
		float maxRatio = 10.0f / 12);

	VecXf center() const;
	VecXf distance() const;

	bool changed() const;

	void sizeViewport(GLsizei width, GLsizei height);
	void moveCamera(const VecXf& delta);
	void centering();

    protected:
	void _init();
	void _step();

    private:
	PhyloTree *_tree;

	VecXf _convexQuad;
	GLsizei _width;
	GLsizei _height;

	VecXf _delta;
	Smooth _center;
	Smooth _distance;

	float _minRatio;
	float _maxRatio;
	float _border;

	bool _changeViewport;

	void _calcOrtho();
	void _project();
	void _uploadProj();
    };
}

#endif
