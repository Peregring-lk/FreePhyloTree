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
 * desarrolladores, aunque ésta página de inicio es de interés para
 * todo aquel que quiera instalar y usar la aplicación. El punto de
 * entrada de la aplicación es \c main.cpp, que ejecuta a la clase
 * principal del juego, \c QFreePhyloTree.\n
 *
 * \section sec Instalación y ejecución de la aplicación
 *
 * Para instalar la aplicación, necesitas descargar el código fuente,
 * disponible <a
 * href="http://gitorious.org/freephylotree/freephylotree/archive-tarball/master">aquí</a>,
 * en donde se encuentra la última versión de desarrollo del proyecto
 * (inestable). Más abajo se muestran las dependencias necesarias.
 *
 * Una vez descargado, y en consola, ejecuta: "$ cmake .". Si no hay
 * ningún aviso de error, y todas las librerías se han encontrado
 * exitosamente, ejecuta: "$ make". Se habrá compilará la aplicación
 * exitósamente, y ésta se podrá ejecutar escribiendo: "$
 * ./FreePhyloTree. Para generar la documentación, "$ make doc". La
 * documentación se encuentra en "doc/html/index.html". Para ejecutar
 * la aplicación, es necesario aceleración 3D y conexión a internet.
 *
 * A continuación se muestra la lista de dependencias para poder
 * construir y compilar la aplicación. En éstas, se muestra primero la
 * dependencia con un enlace a su página web, seguido de la lista de
 * paquetes específicos necesarios, así como la versión
 * correspondiente. La versión indicada es, en concreto, la versión
 * instalada en mi máquina. Es de suponer que en cualquier versión
 * superior la aplicación debería correr perfectamente —especial
 * cuidado con las versiones de Qt.
 *
 * \subsection libcons Dependencias de construcción:
 * \li <a href="http://www.cmake.org/">cmake</a>, paquetes cmake,
 * cmake-data (versión 2.8.0-5).
 * \li <a href="http://www.gnu.org/software/make/">make</a>, paquete
 * make (versión 3.81-7).
 * \li <a href="http://gcc.gnu.org/">gcc</a>, paquete gcc (versión 4.4.3-4).
 *
 * \subsection libcomp Dependencias de compilación:
 * \li <a href="http://qt.nokia.com/">Qt4</a>, paquetes libqt4-dev, libqt4-opengl-dev, libqt4-webkit
 * (versión 4.6.2-0).
 * \li <a href="http://www.mesa3d.org/">mesa</a>, se instalata
 * automáticamente con el paquete opengl de Qt.
 * \li <a
 * href="http://sourceforge.net/projects/ftgl/develop">FTGL</a>,
 * paquete libftgl-dev (versión 2.1.3~rc5-3).
 * \li <a href="http://curl.haxx.se/libcurl/">Curl</a>, paquete
 * libcurl4-gnutls-dev (versión 7.19.7-1).
 * \li <a href="http://flex.sourceforge.net/">Flex</a>, paquete flex
 * (versión 2.5.35-9).
 *
 * \subsection libdoc Dependencias de documentación.
 * \li <a href="http://www.stack.nl/~dimitri/doxygen/">Doxygen</a>,
 * paquete doxygen (versión 1.6.3-1).
 *
 * Todas éstas dependencias/librerías están disponibles en los
 * respositorios oficiales de \c Ubuntu, y son software libre, de
 * licencias GPL o compatibles con la GPL.
 *
 * \section uso Uso de la aplicación
 * La aplicación funciona de la siguiente forma: cuando se lanza,
 * aparece un cladograma inicial de 2 niveles, cuya raíz es el clado
 * \a neomura, un clado que agrupa tanto a las arqueas (\a archaea),
 * que son un tipo de bacterias más emparentadas con nosotros que con
 * el resto de bacterias, y a \a eukarya, que son el grupo que agrupa
 * a los organismos con núcleo celular (como nosotros). Si se hace
 * doble click izquierdo en cualquier nodo del árbol, éste se amplia, mostrando
 * los subclados correspondientes. Si el nodo ya está ampliado,
 * entonces se contrae. Pulsando el botón F1 se muestra una pantalla
 * de ayuda con todos los controles de la aplicación.
 *
 * Haciendo doble click derecho en cualquier nodo, se abre el
 * artículo correspondiente del clado/especie en wikipedia. Para
 * cerrarlo, puedes pulsar la tecla ESC o hacer de nuevo doble click
 * derecho fuera del explorador (pero dentro de la aplicación).
 *
 * Con Ctrl + doble click izquierdo en un nodo sólo queda en
 * pantalla su subárbol correspondiente, desapareciendo el resto del
 * árbol (podado del árbol).
 *
 * Para realizar cualquier búsqueda, puedes pulsar Ctrl + F, y a
 * continuación escribir el nombre del clado a buscar. Pulsando F4 se
 * oculta el buscador. Con Ctrl + S se puede tomar una captura del
 * árbol actual, incluido el menú de ayuda si éste está abierto. Se
 * recomienda ocultar éste menú de ayuda con F1 para tomar una captura
 * solamente del árbol.
 *
 * Con Ctrl + A se muestran los nombres de todos los clados.
 *
 * \section err Errores y problemas encontrados
 * \li Violación de segmento en el arranque: Ésto, hasta ahora, pasa
 * en todas las arquitecturas de 64 bits probadas. Se soluciona
 * ejecutando la aplicación con sudo ($sudo ./FreePhyloTree). Igualmente,
 * sigue ocurriendo una violación de segmento en cuanto se haga click,
 * tanto en el buscador como en el explorador integrado
 * —específicamente, al soltar el ratón después de hacer click en
 * cualquier widget integrado, que por ahora son el buscador y el
 * explorador.
 * \li En algunas arquitecturas el árbol no se muestra, aunque
 * internamente está cargado y la aplicación corre normalmente. No se
 * conoce el motivo de ésta inestabilidad, pero parece ser que, de
 * alguna forma, las órdenes openGL dadas, se ejecutan, pero no se
 * envían correctamente a Qt, y por tanto no se renderizan en el
 * widget openGL. Para aquellos que le sucedan tal cosa, que me envíen
 * por correo (véase al principio de ésta página) datos sobre la
 * distribución, arquitectura y versión instalada de los paquetes
 * requeridos por la aplicación (véase arriba).
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
