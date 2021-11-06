/*! 
 *  \brief     Este programa toma una imagen de entrada y le aplica uno, de una serie de filtros y operadores morfológicos. Después crea una imagen de salida con el filtro aplicado y el formato seleccionado por el usuario.
 *  \authors   Andres Corrales Vargas B72400
 *  \authors   Jafet Gutierrez Guevara B73558
 *  \version   1.0
 *  \date      03 de octubre del 2019
 *  \warning   El uso inapropiado de este programa provoca fallo general al mismo. Hacer caso a instrucciones.
 *  \copyright GNU Public License
 */

/*! \mainpage Pagina Principal del Proyecto 0: Efectos en imágenes digitales
 *
 * \section :: Descripcion del programa
 *
 * Este programa es un programa capaz de crear diferentes efectos en imágenes digitales
 */
 
#include "ppmclass.hpp"
#include "pngclass.hpp"
#include "bmpclass.hpp"
#include "jpgclass.hpp"
#include "gifclass.hpp"
#include "filterclass.hpp"

/*! \fn int main() 
*  \brief La función main ejecuta todos los métodos de las distintas clases por medio de la creación de objetos, para tomar la imagen de entrada, aplicarle el efecto y el cambio de formato seleccionados por el usuario y así crear una nueva imagen.
*  \return Esta funcion devuelve 0, siempre que su ejecución haya sido normal, sin errores.
*/

/*!
 *  \file      main.cpp
 *  \brief     Este es el archivo que contiene el programa principal, donde se crean todos los objetos y se ejecutan todos los métodos para aplicar cada filtro.
 *  \details   En main.cpp se encuentra la función main donde se ejecutan todas los métodos, se inicializan y crean los objetos necesarios para el funcionamiento del programa.
 *  \authors   Andres Corrales Vargas B72400
 *  \authors   Jafet Gutierrez Guevara B73558
 *  \version   1.0
 *  \date      03 de octubre del 2019
 *  \bug       No hay bugs aquí
 *  \warning   El uso inapropiado de este programa provoca fallo general al mismo. Hacer caso a instrucciones.
 *  \copyright GNU Public License supongo.
 */
 
int main(int argc, char* argv[])
{
    string nom_original = argv[1]; /*! @arg nom_original: Atributo tipo string que guarda el nombre de la imagen de entrada. */
    string formato = ""; /*! @arg formato: Este atributo tipo string tiene el formato de la imagen. */
    string nom_nuevo = nom_original + "." + argv[2] + "." + argv[3]; /*! @arg nom_nuevo: Atributo tipo string que contiene el nombre que tendrá la imagen de salida, junto con su extensión. */
    char* archivo_salida = &nom_nuevo[0]; /*! @arg archivo_salida: Atributo tipo char* que guarda el nombre de la imagen de salida. */

    ifstream img(argv[1]);
    if(!img.fail())
    {
        for(char& c : nom_original)
        {
            formato += c;
            if (c == '.'){formato = "";}
        }

        if (formato == "png")
        {
            PNG imagen(argv[1]);
            imagen.Procesar_Archivo_PNG();
            Filtros f(archivo_salida, argv[3], argv[2], imagen.matriz_de_pixeles, imagen.ancho, imagen.altura);
            f.Aplicar_Filtro();
        }

        else if (formato == "jpg")
        {
            JPG imagen(argv[1]);
            imagen.Procesar_Archivo_JPG();
            Filtros f(archivo_salida, argv[3], argv[2], imagen.matriz_de_pixeles, imagen.ancho, imagen.altura);
            f.Aplicar_Filtro();
        }

        else if (formato == "gif")
        {
            GIF imagen(argv[1]);
            imagen.Procesar_Archivo_GIF();
            Filtros f(archivo_salida, argv[3], argv[2], imagen.matriz_de_pixeles, imagen.ancho, imagen.altura);
            f.Aplicar_Filtro();
        }

        else if (formato == "bmp")
        {
            BMP imagen(argv[1]);
            imagen.Procesar_Archivo_BMP();
            Filtros f(archivo_salida, argv[3], argv[2], imagen.matriz_de_pixeles, imagen.ancho, imagen.altura);
            f.Aplicar_Filtro();
        }

        else if (formato == "ppm")
        {
            PPM imagen(argv[1]);
            imagen.Procesar_Archivo_PPM();
            Filtros f(archivo_salida, argv[3], argv[2], imagen.matriz_de_pixeles, imagen.ancho, imagen.altura);
            f.Aplicar_Filtro();
        }

        else{cout << "ERROR 0: El formato de la imagen de entrada no es compatible con este programa. Abortando..." << endl;}
    }

    else{cout << "ERROR 1: La imagen que desea abrir no existe. Abortando..." << endl;}
	
	return 0;
}