/*! 
 *  \file      imageclass.hpp
 *  \brief     Este es el archivo que contiene la clase Imagen, que representa a una imagen.
 *  \details   En imageclass.hpp se encuentra la clase que contiene el constructor para el objeto Imagen, además de los atributos que definen a una imagen.
 *  \authors   Andres Corrales Vargas B72400
 *  \authors   Jafet Gutierrez Guevara B73558
 *  \version   1.0
 *  \date      03 de noviembre del 2019
 *  \bug       No hay bugs aqui
 *  \warning   El uso inapropiado de este programa provoca fallo general al mismo. Hacer caso a instrucciones.
 *  \copyright GNU Public License
 */
 
#ifndef IMAGECLASS
#define IMAGECLASS

#include "ext_incl/includes.hpp"

/*! \class Imagen imageclass.hpp "incl/imageclass.hpp"
*  \brief Esta clase contiene el constructor del objeto Imagen, además de los atributos que caracterizan a una imagen.
*/
class Imagen
{
    public:
        int** matriz_de_pixeles; /*!< Atributo tipo int** que guarda una matriz con todos los pixeles de la imagen de entrada. */
        char* archivo_entrada; /*!< Atributo tipo char* que guarda el nombre de la imagen de entrada. */
        unsigned int ancho = 0; /*!< Este atributo unsigned int guardará el ancho de la matriz de pixeles de entrada. */
		unsigned int altura = 0; /*!< Este atributo unsigned int guardará la altura de la matriz de pixeles de entrada. */

        Imagen(){};
        ~Imagen(){};
};

#endif