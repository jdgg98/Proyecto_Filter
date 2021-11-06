/*! 
 *  \file      pngclass.hpp
 *  \brief     Este es el archivo que contiene la clase PNG, que representa a una imagen con formato png.
 *  \details   En pngclass.hpp se encuentra la clase que contiene el constructor para el objeto PNG, además de las funciones Procesar_Archivo_PNG y Pixeles_a_PNG.
 *  \authors   Andres Corrales Vargas B72400
 *  \authors   Jafet Gutierrez Guevara B73558
 *  \version   1.0
 *  \date      03 de noviembre del 2019
 *  \bug       No hay bugs aqui
 *  \warning   El uso inapropiado de este programa provoca fallo general al mismo. Hacer caso a instrucciones.
 *  \copyright GNU Public License
 */
 
#ifndef PNGCLASS
#define PNGCLASS

#include <png.h>
#include "imageclass.hpp"

/*! \class PNG pngclass.hpp "incl/pngclass.hpp"
*  \brief Esta clase tiene los atributos y métodos para definir a una imagen con formato png.
*/
class PNG : public Imagen
{
    private:
        png_byte tipo_color; /*!< Este dato contiene el tipo de color que tiene la imagen. Las imágenes png pueden ser de escala de grises, RGB o RGBA, entre otros. */
        png_byte prof_bit; /*!< Este atributo guarda la profundidad de bit. */
        png_structp ptr_png; /*!< Un puntero para alojar en memoria información de la imagen de entrada leída o de la imagen de salida a exportar. Entre la información que guarda de la imagen se encuentra su ancho, altura, datos de pixeles y tipo de color. */
        png_infop ptr_info; /*!< La información de cabecera de la imagen. */
        png_bytep * punteros_de_fila; /*!< Un arreglo conformado por los pixeles en una fila de la imagen. */
		int x; /*!< Variable multipropósito. */
		int y; /*!< Variable multipropósito. */
		int i = 0; /*!< Variable multipropósito. */

    public:
        PNG(char* input_file)
        {
            this->archivo_entrada = input_file;
        };

        ~PNG(){};

		/*! \fn void Procesar_Archivo_PNG() 
        *  \brief Esta función es la encargada de procesar las imagenes png y generar la matriz de pixeles que la define.
        *  \return Esta función no tiene valor de retorno.
        */	
        void Procesar_Archivo_PNG()
        {
            cout << "Procesando imagen PNG... ";
            FILE *imagen_png = fopen(archivo_entrada, "rb");

            ptr_png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
            ptr_info = png_create_info_struct(ptr_png);

            png_init_io(ptr_png, imagen_png);
            png_read_info(ptr_png, ptr_info);

            ancho = png_get_image_width(ptr_png, ptr_info);
            altura     = png_get_image_height(ptr_png, ptr_info);
            tipo_color = png_get_color_type(ptr_png, ptr_info);
            prof_bit  = png_get_bit_depth(ptr_png, ptr_info);

            if(prof_bit == 16){png_set_strip_16(ptr_png);}

            if(tipo_color == PNG_COLOR_TYPE_PALETTE){png_set_palette_to_rgb(ptr_png);}

            if(tipo_color == PNG_COLOR_TYPE_GRAY && prof_bit < 8)
            {png_set_expand_gray_1_2_4_to_8(ptr_png);}

            if(png_get_valid(ptr_png, ptr_info, PNG_INFO_tRNS))
                png_set_tRNS_to_alpha(ptr_png);

            if(tipo_color == PNG_COLOR_TYPE_RGB || tipo_color == PNG_COLOR_TYPE_GRAY || tipo_color == PNG_COLOR_TYPE_PALETTE)
            {png_set_filler(ptr_png, 255, PNG_FILLER_AFTER);}
                
            if(tipo_color == PNG_COLOR_TYPE_GRAY || tipo_color == PNG_COLOR_TYPE_GRAY_ALPHA){png_set_gray_to_rgb(ptr_png);}
                
            png_read_update_info(ptr_png, ptr_info);

            punteros_de_fila = (png_bytep*)malloc(sizeof(png_bytep) * altura);

            for(int y = 0; y < altura; y++)
            {
                punteros_de_fila[y] = (png_byte*)malloc(png_get_rowbytes(ptr_png, ptr_info));
            }

            png_read_image(ptr_png, punteros_de_fila);

            fclose(imagen_png);
            png_destroy_read_struct(&ptr_png, &ptr_info, NULL);
            
            matriz_de_pixeles = new int*[(ancho*altura)];
            for (int i = 0; i < (ancho*altura); i++)
            {
                matriz_de_pixeles[i] = new int[3];
            }

            for(y = 0; y < altura; y++)
            {
                png_bytep fila = punteros_de_fila[y];
                for(int x = 0; x < ancho; x++)
                {
                    png_bytep canal = &(fila[x * 4]);
                    matriz_de_pixeles[i][0] = int(canal[0]);
                    matriz_de_pixeles[i][1] = int(canal[1]);
                    matriz_de_pixeles[i][2] = int(canal[2]);
                    i++;
                }
            }

            cout << "Completado" << endl;
        }

		/*! \fn void Pixeles_a_PNG() 
        *  \brief Esta función es la encargada de procesar la matriz de pixeles de salida y crear una imagen con formato png a partir de ella.
        *  \return Esta función no tiene valor de retorno.
        */
        void Pixeles_a_PNG(char* nom_archivo)
        {
            cout << "Exportando imagen a PNG... " << endl << endl;
            FILE* ptr_archivo = fopen(nom_archivo, "wb");
            png_structp ptr_png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
            ptr_info = png_create_info_struct(ptr_png);
            png_init_io(ptr_png, ptr_archivo);

            punteros_de_fila = (png_bytep*) malloc(sizeof(png_bytep) * altura);

            for (y = 0; y < altura; y++)
            {
                punteros_de_fila[y] = (png_bytep) malloc(ancho * sizeof(png_bytep));
            }

            for (y=0; y < altura; y++)
            {
                png_bytep fila = punteros_de_fila[y];
                for (x = 0; x < ancho; x++)
                {
                    png_bytep ptr = &(fila[x*4]);
                    ptr[0] = this->matriz_de_pixeles[i][0];
                    ptr[1] = this->matriz_de_pixeles[i][1];
                    ptr[2] = this->matriz_de_pixeles[i][2];
                    ptr[3] = 255;
                    i++;
                }
            }
            png_set_IHDR(ptr_png, ptr_info, this->ancho, this->altura, 8, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
            png_write_info(ptr_png, ptr_info);
            png_write_image(ptr_png, punteros_de_fila);
            png_write_end(ptr_png, NULL);

            for (y = 0; y < altura; y++)
            {
                free(punteros_de_fila[y]);
            }
            free(punteros_de_fila);
            png_destroy_write_struct(&ptr_png, &ptr_info);

            cout << "\aAVISO: Archivo PNG creado satisfactoriamente." << endl;
        }
};
#endif
