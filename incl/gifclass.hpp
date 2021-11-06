/*! 
 *  \file      gifclass.hpp
 *  \brief     Este es el archivo que contiene la clase GIF, que representa a una imagen con formato gif.
 *  \details   En gifclass.hpp se encuentra la clase que contiene el constructor para el objeto GIF, además de las funciones Procesar_Archivo_GIF y Pixeles_a_GIF.
 *  \authors   Andres Corrales Vargas B72400
 *  \authors   Jafet Gutierrez Guevara B73558
 *  \version   1.0
 *  \date      03 de noviembre del 2019
 *  \bug       No hay bugs aqui
 *  \warning   El uso inapropiado de este programa provoca fallo general al mismo. Hacer caso a instrucciones.
 *  \copyright GNU Public License
 */

#ifndef GIFCLASS
#define GIFCLASS

#include "imageclass.hpp"
#include <gif_lib.h>
#include <unistd.h>

/*! \class GIF gifclass.hpp "incl/gifclass.hpp"
*  \brief Esta clase tiene los atributos y métodos para definir a una imagen con formato gif.
*/

class GIF :public Imagen
{
    private:
        int i, j;/*!< Variables multipropósito. */
        

    public:
        GIF(char* input_file)
        {
            this->archivo_entrada = input_file;
        };

        ~GIF(){};

        /*! \fn void Procesar_Archivo_GIF() 
        *  \brief Esta función es la encargada de procesar las imagenes gif y generar la matriz de pixeles que la define.
        *  \return Esta función no tiene valor de retorno.
        */


        void Procesar_Archivo_GIF()
        {
            cout << "Procesando imagen GIF... ";
            int* error;
            GifFileType* ptr_gif = DGifOpenFileName(archivo_entrada, error);
            *error = DGifSlurp(ptr_gif);

            ancho = ptr_gif->SWidth;
            altura = ptr_gif->SHeight;
            matriz_de_pixeles = new int*[(ancho*altura)];
            for (i = 0; i < (ancho*altura); i++)
            {
                matriz_de_pixeles[i] = new int[3];
            }

            SavedImage* imagen_gif = &ptr_gif->SavedImages[0];

            for (i = 0; i < (ancho*altura); i++)
            {
                j = imagen_gif->RasterBits[i];
                if (j != ptr_gif->SBackGroundColor)
                {
                    GifColorType canal_rgb = ptr_gif->SColorMap->Colors[j];
                    matriz_de_pixeles[i][0] = (int)canal_rgb.Red;
                    matriz_de_pixeles[i][1] = (int)canal_rgb.Green;
                    matriz_de_pixeles[i][2] = (int)canal_rgb.Blue;
                }
            }
            cout << "Completado" << endl;
        }

        /*! \fn void Pixeles_a_GIF() 
        *  \brief Esta función es la encargada de procesar la matriz de pixeles de salida y crear una imagen con formato gif a partir de ella.
        *  \return Esta función no tiene valor de retorno.
        */


        void Pixeles_a_GIF(char* nom_archivo)
        {
            cout << "Exportando imagen a GIF... " << endl << endl;
            int* error;
            int x = 0, y = 0, z = 0;
            
            GifColorType* colores = new GifColorType[ancho*altura];
            GifPixelType* pixeles = new GifPixelType[ancho*4];

            for (int i = 0; i < ancho*altura; i++)
            {
                colores[i].Red = (unsigned char)matriz_de_pixeles[i][0];
                colores[i].Green = (unsigned char)matriz_de_pixeles[i][1];
                colores[i].Blue = (unsigned char)matriz_de_pixeles[i][2];
            }
            ColorMapObject* mapa = GifMakeMapObject(256, colores);

            
            GifFileType* ptr_gif = EGifOpenFileName(nom_archivo, false, error);
            EGifGetGifVersion(ptr_gif);
            EGifSetGifVersion(ptr_gif, true);
            EGifPutScreenDesc(ptr_gif, ancho, altura, 256, 0, mapa);
            EGifPutComment(ptr_gif, "GIF creado por grupo 1");
            EGifPutImageDesc(ptr_gif, 0, 0, ancho, altura, false, mapa);

            for (i = 0; i < altura; i++)
            {
                z = 0;
                for (j = 0; j < ancho; j++)
                {
                    pixeles[j] = matriz_de_pixeles[x][0] + matriz_de_pixeles[x][1] + matriz_de_pixeles[x][2];

                    x++;
                }
                EGifPutLine(ptr_gif, pixeles, ancho);
            }
                        
            EGifCloseFile(ptr_gif, error);
            
            cout << "\aAVISO: Archivo GIF creado satisfactoriamente." << endl;
        }
};

#endif