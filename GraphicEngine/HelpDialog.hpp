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

#ifndef _FPT_HELP_DIALOG_
#define _FPT_HELP_DIALOG_

#include <QGLWidget>
#include <FTGL/ftgl.h>

#include "Viewing.hpp"
#include "../Strategies/Strategy.hpp"
#include "../Strategies/Smooth.hpp"

namespace fpt
{
    class HelpDialog : public Strategy {
    public:
	HelpDialog(Viewing *viewing, float factor);

	GLuint texture() const;
	bool isVisible() const;

	void setTexture(GLuint texture);
	void setShow(bool show = true);

    protected:
	void _init();
	void _step();

    private:
	Viewing *_viewing;
	Smooth _loc;

	GLuint _texture;
	float _factor;

	bool _show;
    };
}

#endif
