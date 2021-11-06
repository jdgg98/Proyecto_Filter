/*! 
 *  \file      ppmclass.hpp
 *  \brief     Este es el archivo que contiene la clase PPM, que representa a una imagen con formato ppm.
 *  \details   En ppmclass.hpp se encuentra la clase que contiene el constructor para el objeto PPM, además de las funciones Procesar_Archivo_PPM y Pixeles_a_PPM.
 *  \authors   Andres Corrales Vargas B72400
 *  \authors   Jafet Gutierrez Guevara B73558
 *  \version   1.0
 *  \date      03 de noviembre del 2019
 *  \bug       No hay bugs aqui
 *  \warning   El uso inapropiado de este programa provoca fallo general al mismo. Hacer caso a instrucciones.
 *  \copyright GNU Public License
 */
 
#ifndef PPMCLASS
#define PPMCLASS

#include "imageclass.hpp"
#include <stdexcept>

/*! \class PPM ppmclass.hpp "incl/ppmclass.hpp"
*  \brief Esta clase tiene los atributos y métodos para definir a una imagen con formato ppm.
*/
class PPM : public Imagen
{
    private:
        char crtr; /*!< Este atributo tipo char corresponde al carácter leyendose del archivo PPM. */
        string param; /*!< Este string guarda el tipo de archivo ppm de la imagen. Este puede ser P3 o P6. */
        int cont_param; /*!< Este atributo tipo int funciona como contador de parámetros. Sirve para definir cuantos datos (no caracteres) han sido leídos del archivo ppm. */
        int pixel = 0; /*!< Este atributo tipo int determina en que posición de la matriz de pixeles debe meterse la información de canal que se está leyendo de la imagen ppm. */
		int canal_color = 0; /*!< Este atributo tipo int determina en que posición del pixel, en la matriz de pixeles, debe meterse la información de un canal. */
        bool ignorar_comentario = false; /*!< En las imágenes ppm se puede poner un comentario. Para que el procesador no crea que se trata de información de la imagen, mientras este atributo tipo bool tenga el valor de true, el programa ignora cualquier lectura de archivo. Porque de hacerlo estaría leyendo un comentario. */
        bool esBin = false; /*!< Este atributo tipo bool sirve para que el programa determine si el archivo ppm es P3 (true) o P6 (false). */
        int i; /*!< Variable multipropósito. */
		int o; /*!< Variable multipropósito. */

    public:
        PPM(char* input_file)
        {
            this->archivo_entrada = input_file;
        };

        ~PPM()
        {
            if (archivo_entrada != nullptr)
            {
                for (int i = 0; i < (ancho*altura); i++)
                {
                    delete[] matriz_de_pixeles[i];
                }
                delete matriz_de_pixeles;
            }
        }

		/*! \fn void Procesar_Archivo_PPM() 
        *  \brief Esta función es la encargada de procesar las imagenes ppm y generar la matriz de pixeles que la define.
        *  \return Esta función no tiene valor de retorno.
        */	
        void Procesar_Archivo_PPM()
        {
            cout << "Procesando imagen PPM... ";
            ifstream imagen(archivo_entrada, ifstream::binary);

            while(!imagen.eof())
            {
                imagen.get(crtr);

                if (ignorar_comentario)
                {
                    if (crtr == '\n'){ignorar_comentario = false;}
                }

                else
                {
                    if (crtr == ' ' || crtr == '\n')
                    {
                        cont_param++;
                        if (cont_param == 1)
                        {
                            if (param == "P3"){esBin = true;}
                        }
                        else if (cont_param == 2)
                        {
                            try{ancho = stoi(param);}
                            catch(invalid_argument& i){Procesar_Archivo_PPM();}
                        }
                        else if (cont_param == 3)
                        {
                            try{altura = stoi(param);}
                            catch(invalid_argument& i){Procesar_Archivo_PPM();}
                        }

                        else if (cont_param == 4){param = ""; break;}
                        param = "";
                    }
                    else if (crtr == '#'){ignorar_comentario = true;}
                    else{param += crtr;}
                }
            }

            matriz_de_pixeles = new int*[(ancho*altura)];
            for (i = 0; i < (ancho*altura); i++)
            {
                matriz_de_pixeles[i] = new int[3];
            }

            while(!imagen.eof())
            {
                imagen.get(crtr);

                if (ignorar_comentario)
                {
                    if (crtr == '\n'){ignorar_comentario = false;}
                }

                else
                {
                    if (esBin == true)
                    {
                        if (crtr == ' ' || crtr == '\n' || imagen.eof())
                        {
                            cont_param++;
                            if (param != "")
                            {
                                matriz_de_pixeles[pixel][canal_color] = stoi(param);
                                canal_color++;
                                if(canal_color > 2){pixel++; canal_color = 0;}
                            }
                            param = "";
                        }

                        else if (crtr == '#'){ignorar_comentario = true;}

                        else{param += crtr;}
                    }

                    else
                    {
                        for (i = 0; i < 256; i++)
                        {
                            if (crtr == char(i))
                            {
                                if (pixel < ancho*altura)
                                {
                                    matriz_de_pixeles[pixel][canal_color] = i;
                                    canal_color++;
                                    if(canal_color > 2){pixel++; canal_color = 0;}
                                }
                            }
                        }
                    }
                }
            }
            imagen.close();
            cout << "Completado" << endl;
        }

		/*! \fn void Pixeles_a_PPM() 
        *  \brief Esta función es la encargada de procesar la matriz de pixeles de salida y crear una imagen con formato ppm a partir de ella.
        *  \return Esta función no tiene valor de retorno.
        */
        void Pixeles_a_PPM(char* archivo_salida)
        {
            cout << "Exportando imagen a PPM... " << endl << endl;
            ofstream imagen(archivo_salida);
            string texto;

            texto = "P3\n#Imagen creada usando PPMbyANCOVA para PROYECTO 0, GRUPO 1\n";
            texto += to_string(this->ancho) + " " + to_string(altura) + "\n255\n";

            for (int i = 0; i < (ancho*altura); i++)
            {
                for(int j = 0; j < 3; j++)
                {
                    texto += to_string(matriz_de_pixeles[i][j]) + "\n";
                }
            }
            imagen << texto;
            cout << "\aAVISO: Archivo PPM creado satisfactoriamente." << endl;
            imagen.close();
        }
};
#endif