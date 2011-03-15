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

#include <cstring>
#include <cstdio>
#include <vector>

#include "ParserTree.hpp"

using namespace fpt;
using namespace std;

std::string _buffer;

extern vector<string> _clades;
extern int yylex(void);
extern int yy_scan_string(const char*);

size_t _setBuffer(void *ptr, size_t size, size_t nmemb, void *stream)
{
    for (unsigned i = 0; i < nmemb; ++i)
	_buffer.push_back(((char*)ptr)[i]);

    return size * nmemb;
}

ParserTree::ParserTree(string wikiPath, unsigned levelsStep)
    : _wikiPath(wikiPath), _levelsStep(levelsStep)
{
    _headerlist = NULL;

    _query = _wikiPath + "w/api.php?";
    _query += "action=query";
    _query += "&prop=revisions&rvprop=content&rvsection=1";
    _query += "&titles=";

    _curl = curl_easy_init();
    _headerlist = curl_slist_append(_headerlist, "User-Agent:");
}

ParserTree::~ParserTree()
{
    curl_easy_cleanup(_curl);
}

void ParserTree::expand(PhyloNode *node)
{
    _actualNode = node;

    if (_curl)
	_configQuery(node);
}

void ParserTree::_configQuery(PhyloNode *node)
{
    CURLcode res;

    string query = _query + node->url();

    _buffer.clear();

    curl_easy_reset(_curl);
    curl_easy_setopt(_curl, CURLOPT_URL, query.c_str());
    curl_easy_setopt(_curl, CURLOPT_USERAGENT, _headerlist);
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, _setBuffer);

    res = curl_easy_perform(_curl);

    yy_scan_string(_buffer.c_str());
    yylex();

    _buffer.clear();

    if (res == CURLE_OK)
	_subclades(node);
}

void ParserTree::_subclades(PhyloNode *node)
{
    /*
     *
     *  Extraemos clados.
     *
     */
    for (unsigned i = 0; i < _clades.size(); ++i) {
	string clade = _clades[i];
	string url = _fix(clade);

	node->addChild(new PhyloNode(clade, url, node));
    }

    _clades.clear();

    if ((node->level() - _actualNode->level()) < _levelsStep - 1)
	for (int i = 0; i < node->degree(); ++i)
	_configQuery(node->child(i));
}

string ParserTree::_fix(string& name)
{
    if (name[0] == '[')
	return _fixLink(name);
    else
	return _fixTemplate(name);
}

string ParserTree::_fixLink(string& name)
{
    string url;

    name.erase(0, 2);
    name.erase(name.size() -2, 2);

    string::size_type index = name.find('|');

    if (index != string::npos)
	name.erase(index, name.size() - index);

    url = name;

    for (unsigned i = 0; i < url.size(); ++i)
	if (url[i] == ' ')
	    url[i] = '_';

    return url;

}

string ParserTree::_fixTemplate(string& name)
{
    string url;

    name.erase(name.size() - 2, 2);

    string::size_type index = name.find('|');
    name.erase(0, index + 1);

    index = name.find('|');
    name.erase(index, 1);
    url = name;

    index = name.find('|');
    name[index] = ' ';
    url[index] = ' ';

    return url;
}
