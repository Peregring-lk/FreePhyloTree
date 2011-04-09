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

/*! \file Viewing.hpp
 *  \brief Fichero que define la clase fpt::Viewing.
 *
 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
 *  \date 04/2011
 *  \version 0.7
 *  \since 0.7
 */

#ifndef _FPT_VIEWING_
#define _FPT_VIEWING_

#include "../PhyloTree.hpp"

#include <GL/gl.h>

namespace fpt
{
    /*! \class Viewing
     *  \brief Clase de visionado de la aplicación.
     *
     *  Ésta clase se encarga de controlar el cuadro de visionado y
     *  los movimientos de la cámara.
     *
     *  \note No se ha llamado clase \c Camera, porque no solo trata
     *  la cámara, sino también el \a viewport.
     *
     *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
     *  \date 04/2011
     *  \version 0.7
     *  \since 0.7
     */
    class Viewing : public Strategy
    {
    public:
	/*! \fn Viewing(PhyloTree *tree, GLsizei width, GLsizei
	 *  height, float minRatio, float maxRatio)
	 *  \brief Constructor de la clase.
	 *
	 *  \param tree Árbol taxonómico.
	 *  \param width Ancho del viewport inicial.
	 *  \param height Alto del viewport inicial.
	 *  \param minRatio Ratio mínimo de visualización de un nodo.
	 *  \param maxRatio Ratio máximo de visualización de un nodo.
	 *
	 *  Los ratios indican cómo de grande o chico podrá verse un
	 *  nodo. Contra más lejos esté la cámara, más pequeño se verá
	 *  cada nodo. El ratio mínimo evita que la cámara se aleje
	 *  demasiado. El ratio máximo evita que la cámara se acerce
	 *  demasiado.
	 *
	 *  En realidad, no hay ningún mecanismo de zoom
	 *  involucrado. Lo único que hacemos es seleccionar el área
	 *  visible. Éste área siempre intenta ajustarse al tamaño del
	 *  árbol. A árboles pequeños, áreas pequeñas y a árboles
	 *  grandes, mayores áres visibles. El centro del área siempre
	 *  es el centro del árbol, a no ser que se pida un
	 *  desplazamiento (\c Viewing::moveCamera).
	 *
	 *  Cuándo el árbol es demasiado pequeño, los nodos se ven
	 *  muy grandes. Por ejemplo, para un árbol de un solo nodo,
	 *  el área «de mundo» que ocupará la ventana entera es el área
	 *  que ocupa solamente ese nodo, por lo tanto, el nodo se
	 *  verá muy grande. El ratio máximo evita elegir superficies
	 *  muy pequeñas, ya que indica como de grande, como máximo,
	 *  podrá verse cada nodo.
	 *
	 *  Igualmente, si el árbol es muy grande (cien nodos, por
	 *  ejemplo) cada nodo se verá muy pequeño en la pantalla, y
	 *  el ratio mínimo lo evita poniendo un límite en el tamaño
	 *  mínimo de visualizado de cada nodo.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	Viewing(PhyloTree *tree, GLsizei width, GLsizei height,
		float minRatio = 10.0f / 7,
		float maxRatio = 10.0f / 12);

        /*! \fn VecXf center() const
	 *  \brief Devuelve el centro (en coordenadas de mundo) del
	 *  área de visionado.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	VecXf center() const;

        /*! \fn VecXf distance() const
	 *  \brief Devuelve la distancia (en coordenadas de mundo)
	 *  entre el centro y las esquinas del área de visionado.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	VecXf distance() const;

        /*! \fn bool changed() const
	 *  \brief Devuelve si el área de visionado ha cambiado.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	bool changed() const;

        /*! \fn void sizeViewport(GLsizei width, GLsizei height)
	 *  \brief Indica un nuevo tamaño para el viewport.
	 *
	 *  \param width Ancho del nuevo viewport.
	 *  \param height Alto del nuevo viewport.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	void sizeViewport(GLsizei width, GLsizei height);

        /*! \fn void moveCamera(const VecXf& delta)
	 *  \brief Desplaza el centro de la cámara.
	 *
	 *  \param delta Desplazamiento a efectuar.
	 *
	 *  Ésta función solo desplaza el área de visionado de modo
	 *  que el nuevo centro sea \c center += \c delta.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	void moveCamera(const VecXf& delta);

        /*! \fn void centering()
	 *  \brief Centra la cámara.
	 *
	 *  Elimina todo desplazamiento efectuado y coloca el centro
	 *  del área en el centro del árbol.
	 *
	 *  \sa moveCamera.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	void centering();

    protected:
	void _init();
	void _step();

    private:
	/*! \var PhyloTree *_tree
	 *  \brief Referencia al árbol taxonómico.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	PhyloTree *_tree;

	/*! \var GLsizei _width
	 *  \brief Ancho actual del viewport.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	GLsizei _width;

	/*! \var GLsizei _height
	 *  \brief Alto actual del viewport.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	GLsizei _height;

	/*! \var VecXf _delta
	 *  \brief Desplazamiento acumulado de la cámara.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	VecXf _delta;

	/*! \var Smooth _center
	 *  \brief Centro de la cámara.
	 *
	 *  La cámara suaviza su movimiento haciendo que el área de
	 *  visionado se controle mediante variables \c Smooth.
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	Smooth _center;

	/*! \var Smooth _distance
	 *  \brief Distancia de las esquinas del área de visionado al
	 *  centro de la cámara.
	 *
	 *  \sa _center
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	Smooth _distance;

	/*! \var const float _minRatio
	 *  \brief Ratio mínimo de visualizado de nodos.
	 *
	 *  \sa Viewing()
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	const float _minRatio;

	/*! \var const float _maxRatio
	 *  \brief Ratio máximo de visualizado de nodos.
	 *
	 *  \sa Viewing()
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	const float _maxRatio;

	/*! \var const float _border
	 *  \brief Borde del área de visionado.
	 *
	 *  Para evitar que el área de visionado esté demasiado pegado
	 *  a la ventana, y que los nodos acaben dibujandose en los
	 *  bordes de la ventana, al área de visionado se le suman
	 *  unos márgenes. Ésta variable indica cuál será el ancho de
	 *  éstos margenes.
	 *
	 *  Está configurado a 1.2
	 *
	 *  \author Aarón Bueno Villares, <abv150ci@gmail.com>
	 *  \date 04/2011
	 *  \version 0.7
	 *  \since 0.7
	 */
	const float _border;

	bool _changeViewport;

	void _calcOrtho();
	void _project();
	void _uploadProj();
    };
}

#endif
