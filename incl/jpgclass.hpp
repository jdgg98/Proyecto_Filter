/*! 
 *  \file      jpgclass.hpp
 *  \brief     Este es el archivo que contiene la clase JPG, que representa a una imagen con formato jpg.
 *  \details   En jpgclass.hpp se encuentra la clase que contiene el constructor para el objeto JPG, además de las funciones Procesar_Archivo_JPG y Pixeles_a_JPG.
 *  \authors   Andres Corrales Vargas B72400
 *  \authors   Jafet Gutierrez Guevara B73558
 *  \version   1.0
 *  \date      03 de noviembre del 2019
 *  \bug       No hay bugs aqui
 *  \warning   El uso inapropiado de este programa provoca fallo general al mismo. Hacer caso a instrucciones.
 *  \copyright GNU Public License
 */
 
#ifndef JPGCLASS
#define JPGCLASS
#include <jpeglib.h>
#include "imageclass.hpp"

/*! \class JPG jpgclass.hpp "incl/jpgclass.hpp"
*  \brief Esta clase tiene los atributos y métodos para definir a una imagen con formato jpg.
*/
class JPG :public Imagen
{
    private:
        JSAMPARRAY punteros_de_fila; /*!< Un arreglo de JSAMPLES. Los JSAMPLES son los canales (rgb) de cada píxel, por lo que punteros_de_fila en escencia es un arreglo conformado por los pixeles en una fila de la imagen. */
        jpeg_error_mgr jerr; /*!< Un lugar de memoria al que se salta, para poder guardar información en caso de que el programa caiga en un error al leer o escribir imágenes jpg. */
		int x; /*!< Variable multipropósito. */
		int y; /*!< Variable multipropósito. */
		int i = 0; /*!< Variable multipropósito. */
		int j = 0; /*!< Variable multipropósito. */
    public:
        JPG(char* input_file)
        {
            this->archivo_entrada = input_file;
        };

        ~JPG(){};

		/*! \fn void Procesar_Archivo_JPG() 
        *  \brief Esta función es la encargada de procesar las imagenes jpg y generar la matriz de pixeles que la define.
        *  \return Esta función no tiene valor de retorno.
        */	
        void Procesar_Archivo_JPG()
        {
            cout << "Procesando imagen JPG... ";
            FILE* imagen_jpg = fopen(archivo_entrada, "rb");

            jpeg_decompress_struct ptr_jpg;

            ptr_jpg.err = jpeg_std_error(&jerr);
            jpeg_create_decompress(&ptr_jpg);

            jpeg_stdio_src(&ptr_jpg, imagen_jpg);

            jpeg_read_header(&ptr_jpg, TRUE);
            jpeg_calc_output_dimensions(&ptr_jpg);

            ancho = ptr_jpg.output_width;
            altura = ptr_jpg.output_height;

            punteros_de_fila = new JSAMPROW[1];
            punteros_de_fila[0] = new JSAMPLE[ancho*3];

            matriz_de_pixeles = new int*[(ancho*altura)];
            for (y = 0; y < (ancho*altura); y++)
            {
                matriz_de_pixeles[y] = new int[3];
            }

            jpeg_start_decompress(&ptr_jpg);

            while(ptr_jpg.output_scanline < ptr_jpg.output_height)
            {
                jpeg_read_scanlines(&ptr_jpg, punteros_de_fila, 1);
                for (y = 0; y < ancho*3; y++)
                {
                    matriz_de_pixeles[i][j] = int(punteros_de_fila[0][y]);
                    j++;
                    if (j >= 3){j = 0; i++;}
                }
            }
            
            jpeg_finish_decompress(&ptr_jpg);

            jpeg_destroy_decompress(&ptr_jpg);
            fclose(imagen_jpg);

            cout << "Completado" << endl;
        }

		/*! \fn void Pixeles_a_JPG() 
        *  \brief Esta función es la encargada de procesar la matriz de pixeles de salida y crear una imagen con formato jpg a partir de ella.
        *  \return Esta función no tiene valor de retorno.
        */
        void Pixeles_a_JPG(char* nom_archivo)
        {
            cout << "Exportando imagen a JPG... " << endl;
            cout << "Digite la calidad de la imagen de salida (Valores entre 0 y 100): ";

            int calidad_de_imagen;
            cin >> calidad_de_imagen;

            if (calidad_de_imagen < 0 || calidad_de_imagen > 100){calidad_de_imagen = 50;}

            FILE* ptr_archivo = fopen(nom_archivo, "wb");
            
            jpeg_compress_struct ptr_jpg;
            
            ptr_jpg.err = jpeg_std_error(&jerr);
            jpeg_create_compress(&ptr_jpg);

            jpeg_stdio_dest(&ptr_jpg, ptr_archivo);

            ptr_jpg.image_width = ancho;
            ptr_jpg.image_height = altura;
            ptr_jpg.input_components = 3;
            ptr_jpg.in_color_space = JCS_RGB;

            jpeg_set_defaults(&ptr_jpg);
            jpeg_set_quality(&ptr_jpg, calidad_de_imagen, TRUE);

            punteros_de_fila = new JSAMPROW[altura];

            for (int y = 0; y < altura; y++)
            {
                punteros_de_fila[y] = new JSAMPLE[ancho*3];
                for (int x = 0; x < ancho*3; x++)
                {
                    punteros_de_fila[y][x] = matriz_de_pixeles[i][j];
                    j++;
                    if (j >= 3){j = 0; i++;}
                }
            }

            jpeg_start_compress(&ptr_jpg, TRUE);
            
            jpeg_write_scanlines(&ptr_jpg, punteros_de_fila, altura);

            jpeg_finish_compress(&ptr_jpg);

            jpeg_destroy_compress(&ptr_jpg);
            fclose(ptr_archivo);

            cout << endl << "\aAVISO: Archivo JPG creado satisfactoriamente." << endl;
        }
};

#endif