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

HelpDialog::HelpDialog(Viewing *viewing) : _viewing(viewing)
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
    _show = show;
}

void HelpDialog::_step()
{
    if (isVisible()) {
	VecXf center = _viewing->center();
	VecXf distance = _viewing->distance();

	center.setX(center.x() - distance.x());

	float x = center.x() + 2;
	float y = center.y();

	float factor = 0.6;
	float dx = 200 * 0.6;
	float dy = 120 * 0.6;

	glBindTexture(GL_TEXTURE_2D, _texture);

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
    }
}
