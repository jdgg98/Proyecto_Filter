/*! 
 *  \file      pixelclass.hpp
 *  \brief     Este es el archivo que contiene la clase ConvertidorPixeles
 *  \details   En pixelclass.hpp se encuentra la clase que contiene el constructor para el objeto ConvertidorPixeles, además de la función ExportarImagen.
 *  \authors   Andres Corrales Vargas B72400
 *  \authors   Jafet Gutierrez Guevara B73558
 *  \version   1.0
 *  \date      03 de noviembre del 2019
 *  \bug       No hay bugs aqui
 *  \warning   El uso inapropiado de este programa provoca fallo general al mismo. Hacer caso a instrucciones.
 *  \copyright GNU Public License
 */

#include "ppmclass.hpp"
#include "pngclass.hpp"
#include "bmpclass.hpp"
#include "jpgclass.hpp"
#include "gifclass.hpp"

/*! \class ConvertidorPixeles pixelclass.hpp "incl/pixelclass.hpp"
*  \brief Esta clase tiene la función que convierte la matriz de pixeles de salida en una imagen.
*/
class ConvertidorPixeles
{
    public:
        ConvertidorPixeles(){};
        ~ConvertidorPixeles(){};

		/*! \fn void ExportarImagen() 
        *  \brief Esta función es la encargada convertir la matriz de pixeles, generada por la aplicación de uno de los filtros, en una imagen con el formato de salida definido por el usuario.
        *  \return Esta función no tiene valor de retorno.
        */
        void ExportarImagen(char* archivo_salida, char* formato_salida, int** matriz_de_pixeles, int ancho, int altura)
        {
            string out_format = formato_salida;

            if (out_format == "ppm")
            {
                PPM ppm(nullptr);
                ppm.matriz_de_pixeles = matriz_de_pixeles;
                ppm.ancho = ancho;
                ppm.altura = altura;
                ppm.Pixeles_a_PPM(archivo_salida);
            }

            else if (out_format == "png")
            {
                PNG png(nullptr);
                png.matriz_de_pixeles = matriz_de_pixeles;
                png.ancho = ancho;
                png.altura = altura;
                png.Pixeles_a_PNG(archivo_salida);
            }

            else if (out_format == "jpg")
            {
                JPG jpg(nullptr);
                jpg.matriz_de_pixeles = matriz_de_pixeles;
                jpg.ancho = ancho;
                jpg.altura = altura;
                jpg.Pixeles_a_JPG(archivo_salida);
            }

            else if (out_format == "bmp")
            {
                BMP bmp(nullptr);
                bmp.matriz_de_pixeles = matriz_de_pixeles;
                bmp.ancho = ancho;
                bmp.altura = altura;
                bmp.Pixeles_a_BMP(archivo_salida);
            }

            else if (out_format == "gif")
            {
                GIF gif(nullptr);
                gif.matriz_de_pixeles = matriz_de_pixeles;
                gif.ancho = ancho;
                gif.altura = altura;
                gif.Pixeles_a_GIF(archivo_salida);
            }

            else
            {
                cout << "ERROR 3: Formato de imagen de salida no válido. Abortando..." << endl;;
            }
        }
};