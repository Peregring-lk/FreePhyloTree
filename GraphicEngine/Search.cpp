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

#include "Search.hpp"

#include <QKeyEvent>

using namespace std;
using namespace fpt;

Search::Search(QWidget *parent) : QLineEdit(parent)
{
    _first = false;
    _newSearch = false;
}

Search::Search(const QString& contents, QWidget *parent)
    : QLineEdit(contents, parent)
{
    _first = false;
    _newSearch = false;
}

string Search::actualSearch() const
{
    return _actualSearch;
}

string Search::actualUrl() const
{
    return _actualUrl;
}

bool Search::newSearch() const
{
    return _newSearch;
}

void Search::reboot()
{
    _actualSearch.clear();
    _actualUrl.clear();

    _newSearch = false;
}

void Search::reactivate()
{
    show();

    setFocus();
    selectAll();
}

void Search::hide()
{
    _loc.changeSource(VecXf(1000, 10));
    move(1000, 10);

    QLineEdit::hide();
}

void Search::_init()
{
    setFocus(Qt::MouseFocusReason);

    _loc.changeSource(VecXf(1000, 10));
    _loc.changeTarget(VecXf(20, 10));
    _loc.changeSmooth(0.1);

    _loc.init();

    show();
}

void Search::_step()
{
    if (isVisible()) {
	_loc.step();

	move(_loc.x(), _loc.y());
    }
}

void Search::mousePressEvent(QMouseEvent *event)
{
    if (!_first) {
	_first = true;
	clear();
    }

    QLineEdit::mousePressEvent(event);
}

void Search::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return) {
	_newSearch = true;

	QString actual = text();

	_actualSearch = actual.toStdString();
	_actualUrl = actual.replace(' ', '_').toStdString();
    }

    QLineEdit::keyPressEvent(event);
}
