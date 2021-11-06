/*! 
 *  \file      bmpclass.hpp
 *  \brief     Este es el archivo que contiene la clase BMP, que representa a una imagen con formato bmp.
 *  \details   En bmpclass.hpp se encuentra la clase que contiene el constructor para el objeto BMP, además de las funciones Procesar_Archivo_BMP y Pixeles_a_BMP.
 *  \authors   Andres Corrales Vargas B72400
 *  \authors   Jafet Gutierrez Guevara B73558
 *  \version   1.0
 *  \date      03 de noviembre del 2019
 *  \bug       No hay bugs aqui
 *  \warning   El uso inapropiado de este programa provoca fallo general al mismo. Hacer caso a instrucciones.
 *  \copyright GNU Public License
 */

#ifndef BMPCLASS
#define BMPCLASS
#include "ext_incl/bitmap_image.hpp"
#include "imageclass.hpp"

/*! \class BMP bmpclass.hpp "incl/bmpclass.hpp"
*  \brief Esta clase tiene los atributos y métodos para definir a una imagen con formato bmp.
*/
class BMP : public Imagen
{
    private:
        char* archivo_entrada; /*!< Atributo tipo char* que guarda el nombre de la imagen de entrada. */
        int x = 0; /*!< Variable multipropósito. */
		int y = 0; /*!< Variable multipropósito. */
		int i = 0; /*!< Variable multipropósito. */

    public:
        BMP(char* input_file)
            {
                this->archivo_entrada = input_file;
            };

        ~BMP(){};

		/*! \fn void Procesar_Archivo_BMP() 
        *  \brief Esta función es la encargada de procesar las imagenes bmp y generar la matriz de pixeles que la define.
        *  \return Esta función no tiene valor de retorno.
        */	
        void Procesar_Archivo_BMP()
        {
            cout << "Procesando imagen BMP... ";
            bitmap_image imagen_bmp(archivo_entrada);
            ancho = imagen_bmp.width();
            altura = imagen_bmp.height();
            
            matriz_de_pixeles = new int*[(ancho*altura)];
            for (int i = 0; i < (ancho*altura); i++)
            {
                matriz_de_pixeles[i] = new int[3];
            }

            for (y = 0; y < altura; y++)
            {
                for (x = 0; x < ancho; x++)
                {
                    rgb_t color;
                    imagen_bmp.get_pixel(x, y, color);
                    matriz_de_pixeles[i][0] = color.red;
                    matriz_de_pixeles[i][1] = color.green;
                    matriz_de_pixeles[i][2] = color.blue;
                    i++;
                }
            }
            cout << "Completado" << endl;
        }

		/*! \fn void Pixeles_a_BMP() 
        *  \brief Esta función es la encargada de procesar la matriz de pixeles de salida y crear una imagen con formato jpg a partir de ella.
        *  \return Esta función no tiene valor de retorno.
        */
        void Pixeles_a_BMP(char* nom_archivo)
        {
            cout << "Exportando imagen a BMP... " << endl << endl;

            i = 0;
            bitmap_image imagen_bmp(ancho, altura);
            imagen_bmp.set_all_channels(255, 255, 255);

            for (y = 0; y < altura; y++)
            {
                for (x = 0; x < ancho; x++)
                {
                    imagen_bmp.set_pixel(x, y, matriz_de_pixeles[i][0], matriz_de_pixeles[i][1], matriz_de_pixeles[i][2]);
                    i++;
                }
            }
            imagen_bmp.save_image(nom_archivo);

            cout << "\aAVISO: Archivo BMP creado satisfactoriamente." << endl;
        }
};

#endif