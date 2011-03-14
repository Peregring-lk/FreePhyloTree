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

#include <vector>

#include "ParserTree.hpp"

using namespace fpt;
using namespace std;

unsigned _search;
std::string _buffer;
bool _bredirect;

ParserTree::ParserTree(string wikiPath) : _wikiPath(wikiPath)
{
    _headerlist = NULL;

    _query = _wikiPath + "w/api.php?";
    _query += "action=query";
    _query += "&prop=revisions&rvprop=content&rvsection=0";
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
    if (_curl)
	_configQuery(node);
}

void ParserTree::_configQuery(PhyloNode *node)
{
    CURLcode res;

    string query = _query + node->url();

    curl_easy_reset(_curl);
    curl_easy_setopt(_curl, CURLOPT_URL, query.c_str());
    curl_easy_setopt(_curl, CURLOPT_USERAGENT, _headerlist);
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, _saveQuery);

    _buffer.clear();
    _search = 0;
    _bredirect = false;

    res = curl_easy_perform(_curl);

    if (res == CURLE_OK)
	if (_bredirect) {
	    node->setUrl(_buffer);
	    _buffer.clear();

	    _configQuery(node);
	}
	else
	    _searchSubclades(node);
}

size_t _saveQuery(void *txt, size_t size, size_t mem,
		  FILE *file)
{
    if (_search < 2) {
	for (int i = 0; i < mem; ++i)
	    _buffer.push_back(((char*)txt)[i]);

	_redirect();

	if (!_bredirect) {
	    if (_search == 0) {
		string str("subdivision =");
		string::size_type index = _buffer.find(str);

		if (index != string::npos) {
		    _search = 1;
		    index += str.size() + 1;
		    _buffer.erase(0, index + 1);
		}
		else
		    _buffer.clear();
	    }

	    if (_search == 1) {
		string::size_type index = _buffer.find("}}");

		if (index != string::npos) {
		    _search = 2;
		    _buffer.erase(index, _buffer.size() - index);
		}
	    }
	}
    }

    return size * mem;
}

void _redirect()
{
    string::size_type index = _buffer.find("#REDIREC");

    if (index != string::npos) {
	index = _buffer.find("[[", index);
	_buffer.erase(0, index + 2);

	index = _buffer.find("]]");
	_buffer.erase(index, _buffer.size() - index);

	_bredirect = true;
    }
}

void ParserTree::_searchSubclades(PhyloNode *node)
{
    /*
     *
     *  Extraemos clados.
     *
     */
    while (!_buffer.empty()) {
	string::size_type eol = _buffer.find('\n');
	string str = _buffer.substr(0, eol);

	_buffer.erase(0, eol + 1);

	string::size_type begin = str.find("[[") + 2;
	string::size_type end = str.find_last_of("]]");

	if (end != string::npos) {
	    string cladeName = str.substr(begin, end - begin - 1);
	    string url = _fix(cladeName);

	    node->addChild(new PhyloNode(cladeName, url, node));
	}
    }

    for (int i = 0; i < node->degree(); ++i)
	_configQuery(node->child(i));
}

string ParserTree::_fix(string& name)
{
    _compound(name);

    string url;
    string::size_type index = name.find("|");

    if (index != string::npos)
	name.erase(index, name.size() - index);

    url = name;

    _quitBrackets(name);
    _quitSpaces(url);

    return url;
}

void ParserTree::_compound(string& name)
{
    string::size_type index = name.find("†");

    if (index != string::npos) {
	if (index == name.size() - 3) {
	    index = name.find("]]");
	    name.erase(index, name.size() - index);
	}
	else {
	    index = name.find("[[");
	    name.erase(0, index + 2);
	}
    }
}

void ParserTree::_quitBrackets(string& name)
{
    string::size_type index = name.find("(");

    if (index != string::npos)
	name.erase(index - 1, name.size() - index + 1);
}

void ParserTree::_quitSpaces(string& name)
{
    for (unsigned i = 0; i < name.size(); ++i)
	if (name[i] == ' ')
	    name[i] = '_';
}
