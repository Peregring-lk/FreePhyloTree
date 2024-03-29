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

/*! \file LexerWiki.l
 *  \brief Analizador léxico de las consultas al \c WikiMedia-API de
 *  \a wikispecies.
 *
 *  La respuesta de las consultas al \c WikiMedia-API de \a
 *  wikispecies es, en general, una salida compleja. Hay que buscar
 *  dentro de dicha consulta donde se encuentran los subtaxones y para
 *  ello se hace uso de éste analizador léxico.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2011
 *  \version 0.7
 *  \since 0.7
 */

/*! \file ParserTree.cpp
 *  \brief Fichero que implementa a la clase \c fpt::ParserTree.
 *
 *  Para procesar el resultado de las consultas a \a wikispecies, se
 *  hace uso de \c flex. Véase \c LexerWiki.l.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2011
 *  \version 0.7
 *  \since 0.7
 */
#include <cstring>
#include <cstdio>
#include <vector>

#include "ParserTree.hpp"

using namespace fpt;
using namespace std;

std::string _buffer;

extern vector<string> _clades;
extern bool _found;
extern int yylex(void);
extern int yy_scan_string(const char*);

size_t _setBuffer(void *ptr, size_t size, size_t nmemb, void *stream)
{
    for (unsigned i = 0; i < nmemb; ++i)
	_buffer.push_back(((char*)ptr)[i]);

    return size * nmemb;
}

ParserTree::ParserTree(string wikiPath, unsigned levelsStep,
		       unsigned maxSons)
    : _wikiPath(wikiPath), _levelsStep(levelsStep), _maxSons(maxSons)
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

PhyloNode* ParserTree::expand(const string& name, const string& url)
{
    PhyloNode *node = new PhyloNode(name, url);

    if (expand(node))
	return node;
    else {
	delete node;

	return NULL;
    }
}

bool ParserTree::expand(PhyloNode *node)
{
    _actualNode = node;

    if (_curl)
	return _configQuery(node);
    else
	return false;
}

bool ParserTree::_configQuery(PhyloNode *node)
{
    if (node->degree() == 0) {
	CURLcode res;

	string query = _query + node->url();

	_buffer.clear();

	curl_easy_reset(_curl);
	curl_easy_setopt(_curl, CURLOPT_URL, query.c_str());
	curl_easy_setopt(_curl, CURLOPT_USERAGENT, _headerlist);
	curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, _setBuffer);

	res = curl_easy_perform(_curl);

	_buffer = "-clade=" + _buffer;

	yy_scan_string(_buffer.c_str());
	yylex();

	_buffer.clear();

	if (res == CURLE_OK && _found) {
	    /*
	     *
	     *  Extraemos clados.
	     *
	     */
	    for (unsigned i = 0; i < _clades.size(); ++i) {
		string clade = _clades[i];
		string url = _fix(clade);

		if (clade != node->name())
		    node->addChild(new PhyloNode(clade, url, node));
	    }

	    _clades.clear();
	}
	else
	    return false;
    }

    _subclades(node);

    return true;
}

void ParserTree::_subclades(PhyloNode *node)
{
    if ((node->level() - _actualNode->level()) < _levelsStep - 1)
	if (node->degree() < _maxSons)
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
    name.erase(name.size() - 2, 2);

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

    if (index != 7 && index != 3) {
	index = name.find('|');
	name.erase(index, 1);
	url = name;

	index = name.find('|');
	name[index] = ' ';
	url[index] = '_';
    }
    else
	url = name;

    return url;
}
