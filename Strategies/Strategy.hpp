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

/*! \file Strategy.hpp
 *  \brief Fichero que define a la clase \c fpt::Strategy.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2011
 *  \version 0.7
 *  \since 0.7
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
     *  La clase consta, esencialmente, de dos funciones, una función
     *  \c init(), que inicializa al objeto, y una función \c step(),
     *  que ejecuta el siguiente paso de cómputo.
     *
     *  Si la fase de inicialización, no se ha ejecutado,
     *  las llamadas a la función step no tendrán efecto.
     *
     *  La clase ofrece dos funciones protegidas virtuales llamadas \c
     *  _init(), y \c _step(), cuya implementación es vacía, y que
     *  cada clase heredada deberá reimplementar.
     *
     *  Las funciones init y step (las públicas) solo manejan a la
     *  variable \c Strategy::_initialized, y acto seguido llaman a _init y
     *  _step respectivamente.
     *
     *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
     *  \date 04/2011
     *  \version 0.7
     *  \since 0.7
     */
    class Strategy
    {
    public:
	/*! \fn Strategy()
	 *  \brief Constructor de la clase.
	 *
	 *  Solo pone la variable \c Strategy::_initialized a false.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	Strategy();

        /*! \fn virtual ~Strategy()
	 *  \brief Destructor de la clase.
	 *
	 *  Destructor virtual, vacío pero necesario para una correcta
	 *  destrucción bajo un árbol de herencia.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	virtual ~Strategy();

	/*! \fn bool initialized() const
	 *  \brief Indica si el objeto está inicializado.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	bool initialized() const;

	/*! \fn virtual bool changed() const
	 *  \brief Indica si la última llamada a \c step() ha
	 *  provocado cambios en el objeto.
	 *
	 *  Esta función, por defecto, devuelve false, ya que la clase
	 *  no tiene ningún mecanismo para controlar si se producen o
	 *  no cambios, y cada clase heredada deberá implementar su
	 *  propia versión en caso de ser necesario.
	 *
	 *  \note La función no es abstracta, porque a veces no es
	 *  necesario implementarla.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	virtual bool changed() const;

	/*! \fn void init()
	 *  \brief Función de inicialización.
	 *
	 *  Inicializa al objeto. Solo actualiza la variable \c
	 *  Strategy::_initialized a \c true. Acto seguido llama a \c
	 *  _init().
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	void init();

	/*! \fn void step()
	 *  \brief Siguiente paso de cómputo.
	 *
	 *  Ejecuta el siguiente paso de cómputo del objeto. Si el
	 *  objeto está inicializado, llama a \c _step().
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	void step();

    protected:
	/*! \fn virtual void _init()
	 *  \brief Función protegida de inicialización.
	 *
	 *  Ésta función (originalmente vacía) es la que deben
	 *  implementar las clases heredadas para inicializarse
	 *  conforme a sus propias necesidades.
	 *
	 *  \note Ésta función no es abstracta para no obligar a
	 *  implementarla en caso de no ser necesario.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	virtual void _init();

	/*! \fn virtual void _step()
	 *  \brief Función protegida de siguiente paso de cómputo.
	 *
	 *  Ésta función (originalmente vacía) es la que deben
	 *  implementar las clases heredadas para implementar cada
	 *  paso de cómputo conforme a sus propias necesidades.
	 *
	 *  \note Ésta función no es abstracta para no obligar a
	 *  implementarla en caso de no ser necesario.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	virtual void _step();

    private:
        /*! \var bool _initialized
	 *  \brief Indica si el objeto se ha inicializado.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	bool _initialized;
    };
}

#endif
