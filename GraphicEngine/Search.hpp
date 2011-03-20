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

#ifndef _FPT_SEARCH_
#define _FPT_SEARHC_

#include <string>
#include <QLineEdit>

#include "../Strategies/Smooth.hpp"

namespace fpt
{
    class Search : public QLineEdit, public Strategy
    {
    public:
	Search(QWidget *parent = NULL);
	Search(const QString& contents, QWidget *parent = NULL);

	bool newSearch() const;
	std::string actualSearch() const;
	std::string actualUrl() const;

	void reboot();
	void reactivate();
	void hide();

    protected:
	void _init();
	void _step();

	void mousePressEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);

    private:
	bool _first;
	bool _newSearch;

	Smooth _loc;

	std::string _actualSearch;
	std::string _actualUrl;

	void _toUrl();
    };
}

#endif
