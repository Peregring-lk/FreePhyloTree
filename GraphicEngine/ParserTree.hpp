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

#ifndef _FPT_PARSER_TREE_
#define _FPT_PARSER_TREE_

#include <curl/curl.h>
#include "../PhyloTree.hpp"

int input(void);

namespace fpt
{
    class ParserTree
    {
    public:
	ParserTree(std::string wikiPath, unsigned levelsStep = 3);
	~ParserTree();

	void expand(PhyloNode *node);

    private:
	CURL *_curl;
	Node *_actualNode;
	unsigned _levelsStep;

	struct curl_slist *_headerlist;

	std::string _wikiPath;
	std::string _query;
	std::string _rootClade;

	void _configQuery(PhyloNode *node);
	void _subclades(PhyloNode *node);
	std::string _fix(std::string& name);
	std::string _fixLink(std::string& name);
	std::string _fixTemplate(std::string& name);
    };
}

#endif
