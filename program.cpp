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

/*! \mainpage
 * \a FreePhyloTree, proyecto llevado a cabo por Aarón Bueno Villares
 * <abv150ci@gmail.com>, en colaboración con Pepe Cullera.
 *
 * \a FreePhyloTree es un visualizador de árboles filogenéticos. Si
 * desea obtener más información, visite el <a
 * href="http://freephylotree.blogspot.com/" >blog</a> oficial del
 * proyecto, y así podrá estar al tanto de las novedades en el
 * proyecto.
 *
 * Esta web contiene información de principal interés para
 * desarrolladores. El punto de entrada de la aplicación es \c main.cpp,
 * que ejecuta a la clase principal del juego, \c QFreePhyloTree.\n
 *
 * \section sec Instalación de la aplicación
 *
 * Para instalar la aplicación, necesitas descargar el código fuente,
 * disponible <a
 * href="http://gitorious.org/freephylotree/freephylotree/archive-tarball/master">aquí</a>,
 * en donde se encuentra la última versión de desarrollo del proyecto
 * (inestable).
 *
 * Una vez descargado, y en consola, ejecuta: "$ cmake .", y luego
 * "$ make". Para generar la documentación (que posiblemente esté más
 * actualizada que ésta), "$ make doc". La documentación
 * se encuentra en "doc/html/index.html". Si todas las librerías éstan
 * correctamente instaladas, se compilará la aplicación exitósamente,
 * y ésta se podrá ejecutar escribiendo "$ ./FreePhyloTree". En caso
 * contrario, \a cmake avisará de las librerías no encontradas.
 *
 * El software solo funciona con acceso a internet.
 *
 * \subsection libs Dependencias y librerías necesarias:
 * \li <a href="http://flex.sourceforge.net/">Flex</a>
 * \li <a href="http://qt.nokia.com/">Qt4</a> (módulos adicionales:
 * QtWebKit y QtOpenGL)
 * \li <a href="http://curl.haxx.se/libcurl/">Curl</a>
 * \li <a href="http://www.mesa3d.org/">mesa</a>
 * \li <a href="http://sourceforge.net/projects/ftgl/develop">FTGL</a>
 * \li <a href="http://gcc.gnu.org/">gcc</a>
 * \li <a href="http://www.cmake.org/">cmake</a>
 * \li <a href="http://www.gnu.org/software/make/">make</a>
 * \li <a href="http://www.stack.nl/~dimitri/doxygen/">Doxygen</a>
 * (para generar la documentación).
 *
 * Todas éstas dependencias/librerías están disponibles en los
 * respositorios oficiales de \c Ubuntu, y son software libre, de
 * licencias GPL o compatibles con la GPL.
 *
 * \subsection err Errores encontrados
 * \li Se han encontrado inestabilidades en la ejecución de la
 * aplicación sobre máquinas con tarjeta gráfica ATI y SO Ubuntu, en
 * una, las páginas de wikipedia no se mostraban correctamente, y en
 * otra daba violación de segmento. Aún no se conocen los motivos ni
 * como solucionarlos.
 *
 * \section Uso de la aplicación
 * La aplicación funciona de la siguiente forma: cuando se lanza,
 * aparece un cladograma inicial de 2 niveles, cuya raíz es el clado
 * \a neomura, un clado que agrupa tanto a las arqueas (\a archaea),
 * que son un tipo de bacterias más emparentadas con nosotros que con
 * el resto de bacterias, y a \a eukarya, que son el grupo que agrupa
 * a los organismos con núcleo celular (como nosotros). Si se hace
 * doble click izquierdo en cualquier nodo del árbol, éste se amplia, mostrando
 * los subclados correspondientes. Si el nodo ya está ampliado,
 * entonces se contrae.
 *
 * Haciendo doble click derecho en cualquier nodo, se abre el
 * artículo correspondiente del clado/especie en wikipedia. Por
 * último, con Ctrl + doble click izquierdo en un nodo sólo queda en
 * pantalla su subárbol correspondiente, desapareciendo el resto del
 * árbol.
 */

#include <iostream>
#include "FreePhyloTree.hpp"

using namespace fpt;

int main(int argc, char **argv)
{
    QFreePhyloTree fpt(argc, argv);

    fpt.run();

    return fpt.exec();
}
