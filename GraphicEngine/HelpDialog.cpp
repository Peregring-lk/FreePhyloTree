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

#include "HelpDialog.hpp"

using namespace fpt;

HelpDialog::HelpDialog(Viewing *viewing, float factor)
    : _viewing(viewing), _factor(factor)
{
    _show = false;
}

GLuint HelpDialog::texture() const
{
    return _texture;
}

bool HelpDialog::isVisible() const
{
    return _show;
}

void HelpDialog::setTexture(GLuint texture)
{
    _texture = texture;
}

void HelpDialog::setShow(bool show)
{
    if (show == false && _show == true) {
	VecXf source = _loc.target();
	source.setX(700);

	_loc.changeSource(source);
    }

    _show = show;
}

void HelpDialog::_init()
{
    VecXf center = _viewing->center();
    VecXf distance = _viewing->distance();

    VecXf source = center;
    VecXf target = center;

    source.setX(700);
    center.setX(center.x() - distance.x() + 2);

    _loc.changeSource(source);
    _loc.changeTarget(target);
    _loc.changeSmooth(0.1);

    _loc.init();
}

void HelpDialog::_step()
{
    if (isVisible()) {
	if (_viewing->changed()) {
	    VecXf center = _viewing->center();
	    VecXf distance = _viewing->distance();

	    center.setX(center.x() - distance.x() + 2);

	    _loc.changeTarget(center);
	}

	float x = _loc.x() + 2;
	float y = _loc.y();

	float dx = 230 * _factor;
	float dy = 230 * _factor;

	glBindTexture(GL_TEXTURE_2D, _texture);

	glColor3f(1, 1, 0);
	glBegin(GL_QUADS); {
	    glTexCoord2f(1, 1);
	    glVertex2f(x + dx, y + dy);

	    glTexCoord2f(1, 0);
	    glVertex2f(x + dx, y - dy);

	    glTexCoord2f(0, 0);
	    glVertex2f(x, y - dy);

	    glTexCoord2f(0, 1);
	    glVertex2f(x, y + dy);
	} glEnd();

	_loc.step();
    }
}
