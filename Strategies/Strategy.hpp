/*
  Copyright (C) 2010 Aarón Bueno Villares <abv150ci@gmail.com>

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

#ifndef _FPT_STRATEGY_
#define _FPT_STRATEGY_

namespace fpt
{
    /*! \class Strategy
     *  \brief Interfaz para procesos cuyo cálculo consta de una serie
     *  de pasos.
     *
     *  Ésta clase es la base para la mayoría de las clases de la
     *  aplicación, puesto que la arquitectura del proceso principal
     *  es una fase de inicialización seguida de una serie de pasos de
     *  cómputo.
     *
     */
    class Strategy
    {
    public:
	Strategy();
	virtual ~Strategy();

	bool initialized() const;
	virtual bool changed() const;

	void init();
	void step();

    protected:
	virtual void _init();
	virtual void _step();

	mutable bool _changed;

    private:
	bool _initialized;
    };
}

#endif
