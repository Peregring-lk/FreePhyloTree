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
    /*! \class ParserTree
     *  \brief Clase que contruye el árbol.
     *
     *  Ésta clase explora en el wiki \c wikispecies el cladograma a
     *  visualizar, parseando cada uno de los ártilos de wikispecies
     *  para extraer los subclados de un clado dado.
     *
     *  Cada vez que se pide expandir un nodo, el número niveles a
     *  expandir es controlado mediante parámetros, dado que construir
     *  el árbol entero es poco tratable, por cuestión de tiempo de
     *  inicialización y de comodidad/eficiencia en la interacción con
     *  el árbol. El árbol podría contener miles de nodos, cuando la
     *  mayoría de ellos al usuario no les interesan.
     *
     */
    class ParserTree
    {
    public:
	ParserTree(std::string wikiPath,
		   unsigned levelsStep = 2, unsigned maxSons = 20);
	~ParserTree();

	void expand(PhyloNode *node);

    private:
	CURL *_curl;
	Node *_actualNode;
	unsigned _levelsStep;
	unsigned _maxSons;

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
