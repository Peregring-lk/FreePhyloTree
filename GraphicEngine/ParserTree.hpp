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

size_t _saveQuery(void *txt, size_t size, size_t mem, FILE *file);
void _redirect();

namespace fpt
{
    class ParserTree : public Strategy
    {
    public:
	ParserTree(std::string wikiPath);
	PhyloTree* tree() const;

    protected:
	void _init();
	void _step();

    private:
	CURL *_curl;
	PhyloTree *_tree;

	struct curl_slist *_headerlist;

	std::string _wikiPath;
	std::string _query;
	std::string _rootClade;

	void _configQuery(std::string url, PhyloNode *node);
	void _searchSubclades(PhyloNode *node);

	std::string _fix(std::string& name);
	void _compound(std::string& name);
	void _quitBrackets(std::string& name);
	void _quitSpaces(std::string& name);
    };
}

#endif
