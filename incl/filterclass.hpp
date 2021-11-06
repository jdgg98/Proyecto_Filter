/*! 
 *  \file      filterclass.hpp
 *  \brief     Este es el archivo que contiene la clase Filtros, en la cual se encuentran todos los posibles filtros que se le pueden aplicar a las imágenes.
 *  \details   En filterclass.hpp está la clase que contiene el constructor para el objeto Filtro, aquí se encuentran las funciones que aplican los distintos filtros a las imágenes.
 *  \authors   Andres Corrales Vargas B72400
 *  \authors   Jafet Gutierrez Guevara B73558
 *  \version   1.0
 *  \date      03 de noviembre del 2019
 *  \bug       No hay bugs aquí
 *  \warning   El uso inapropiado de este programa provoca fallo general al mismo. Hacer caso a instrucciones.
 *  \copyright GNU Public License
 */

#include "pixelclass.hpp"
#include <random>
#include <chrono>

/*! \class Filtros filterclass.hpp "incl/filterclass.hpp"
*  \brief Esta clase tiene los atributos que definen a un filtro.
*/
class Filtros
{
    private:
        int** matriz_de_pixeles; /*!< Atributo tipo int** que guarda una matriz con todos los pixeles de la imagen de entrada. */
        char* archivo_salida; /*!< Atributo tipo char* que guarda el nombre que tendrá la imagen de salida. */
        char* formato_salida; /*!< Atributo tipo char* que contiene el nombre del formato de salida. */
        string filtro_a_usar; /*!< Atributo tipo string que tendrá la abreviación de letras correspondiente al filtro que se desea aplicar. */
        int ancho; /*!< Este atributo guarda el ancho de la matriz de pixeles de entrada. */
		int altura; /*!< Este atributo guarda la altura de la matriz de pixeles de entrada. */
		int i = 0; /*!< Varible multipropósito. */
		bool aplicar_filtro = true; /*!< Atributo tipo bool que le permite al programa determinar si el filtro se aplicó correctamente. */
		int x; /*!< Varible multipropósito. */
 		int y; /*!< Varible multipropósito. */
		int a; /*!< Varible multipropósito. */
		int b; /*!< Varible multipropósito. */
		int c; /*!< Varible multipropósito. */
		int j; /*!< Varible multipropósito. */
		int e; /*!< Varible multipropósito. */
		/*!  */
    public:
        Filtros(char* output_file, char* output_format, char* filter, int** pixel_matrix, int width, int height)
        {
            this->archivo_salida = output_file;
            this->formato_salida = output_format;
            this->filtro_a_usar = filter;
            this->matriz_de_pixeles = pixel_matrix;
            this->ancho = width;
            this->altura = height;
        };

        ~Filtros(){}
		
		/*! \fn void Filtro_Gaussiano() 
        *  \brief Esta función aplica el Filtro Gaussiano a la matriz de pixeles de una imagen.
        *  \return Esta función no tiene valor de retorno.
        */		
		void Filtro_Gaussiano()
		{
			int** matriz_de_imagen = new int*[altura];
			cout << "Aplicando Filtro <<Filtro Gaussiano>>... " << endl;
			
			for (x = 0; x < altura; x++)
			{
				matriz_de_imagen[x] = new int[ancho];
				}
				
			for (x = 0; x < altura; x++)
			{
				for (y = 0; y < ancho; y++)
				{
					matriz_de_imagen[x][y] = i;
					i++;
				}
			}

			int** nueva_matriz_de_pixeles = new int*[(ancho*altura)];
			for (i = 0; i < (ancho*altura); i++)
			{
				nueva_matriz_de_pixeles[i] = new int[3];
				for (j = 0; j < 3; j++)
				{
					nueva_matriz_de_pixeles[i][j] = 0;
				}
			}
			
			int in;
			cout << "Digite la intensidad con la que desea aplicar el filtro gaussiano (Valores entre 1 y 100): ";
			cin >> in;
			for(e = 0; e != in; e++)
			{
				for (x = 0; x < altura; x++)
				{
					for (y = 0; y < ancho; y++)
					{
						for(i = 0; i < 3; i++)
						{
							if (x != 0 && y != 0 && x != altura-1 && y != ancho-1)
							{
								int pix[8];
								for (a = 0; a < 8; a++)
								{
									if (a == 0){b = 0; c = -1;}
									else if (a == 1){b = -1; c = -1;}
									else if (a == 2){b = -1; c = 0;}
									else if (a == 3){b = -1; c = 1;}
									else if (a == 4){b = 0; c = 1;}
									else if (a == 5){b = 1; c = 1;}
									else if (a == 6){b = 1; c = 0;}
									else if (a == 7){b = 1; c = -1;}

									pix[a] = matriz_de_pixeles[matriz_de_imagen[x+b][y+c]][i];
								}
								nueva_matriz_de_pixeles[matriz_de_imagen[x][y]][i] = (pix[0] + pix[1] + pix[2] + pix[3] + pix[4] + pix[5] + pix[6] + pix[7])/8;
							}
							else
							{
								nueva_matriz_de_pixeles[matriz_de_imagen[x][y]][i] = matriz_de_pixeles[matriz_de_imagen[x][y]][i];
							}
						}
					}
				}
				for (i = 0; i < (ancho*altura); i++)
				{
					for (j = 0; j < 3; j++)
					{
						matriz_de_pixeles[i][j] = nueva_matriz_de_pixeles[i][j];
					}
				}
			}
			for (i = 0; i < (ancho*altura); i++)
			{
				delete[] nueva_matriz_de_pixeles[i];
			}
			delete[] nueva_matriz_de_pixeles;
			for (i = 0; i < altura; i++)
			{
				delete[] matriz_de_imagen[i];
			}
			delete[] matriz_de_imagen;

			cout << "Completado" << endl;
		}
		
		/*! \fn void Filtro_Desviacion_Estandar() 
        *  \brief Esta función aplica el Filtro Desviación Estándar a la matriz de pixeles de una imagen.
        *  \return Esta función no tiene valor de retorno.
        */
		void Filtro_Desviacion_Estandar()
		{
			int** matriz_de_imagen = new int*[altura];
			cout << "Aplicando Filtro <<Desviación Estándar>>... " << endl;
			
			for (x = 0; x < altura; x++)
            {
                matriz_de_imagen[x] = new int[ancho];
            }
			
            for (x = 0; x < altura; x++)
            {
                for (y = 0; y < ancho; y++)
                {
                    matriz_de_imagen[x][y] = i;
                    i++;
                }
            }

			int** nueva_matriz_de_pixeles = new int*[(ancho*altura)];

            for (i = 0; i < (ancho*altura); i++)
            {
                nueva_matriz_de_pixeles[i] = new int[3];
                for (j = 0; j < 3; j++)
                {
                    nueva_matriz_de_pixeles[i][j] = 0;
                }
            }
			
			for (x = 0; x < altura; x++)
            {
                for (y = 0; y < ancho; y++)
                {
                    if (x != 0 && y != 0 && x != altura-1 && y != ancho-1)
                    {
						for(i = 0; i < 3; i++)
						{
							float prom = 0, desv2[9], sumatoria = 0;
							int pix[9];
							for (a = 0; a < 9; a++)
							{
								if (a == 0){b = 0; c = 0;} //centro
								else if (a == 1){b = 0; c = -1;} //izquierda
								else if (a == 2){b = -1; c = -1;} //esquina inferior izquierda
								else if (a == 3){b = -1; c = 0;} //abajo
								else if (a == 4){b = -1; c = 1;} //esquina inferior derecha
								else if (a == 5){b = 0; c = 1;} //derecha
								else if (a == 6){b = 1; c = 1;} //esquina superior derecha
								else if (a == 7){b = 1; c = 0;} //arriba
								else if (a == 8){b = 1; c = -1;} //esquina superior izquierda

								pix[a] = matriz_de_pixeles[matriz_de_imagen[x+b][y+c]][i];
							}
							prom = (pix[0] + pix[1] + pix[2] + pix[3] + pix[4] + pix[5] + pix[6] + pix[7] + pix[8])/9;
							for (a = 0; a < 9; a++)
							{
								desv2[a] = (pix[a] - prom)*(pix[a] - prom);
								sumatoria += desv2[a];
							}
							nueva_matriz_de_pixeles[matriz_de_imagen[x][y]][i] = sqrt(sumatoria/8);
						}
					}
                }
            }
			for (i = 0; i < (ancho*altura); i++)
            {
                for (j = 0; j < 3; j++)
                {
                    matriz_de_pixeles[i][j] = nueva_matriz_de_pixeles[i][j];
                }
            }
			
            for (i = 0; i < (ancho*altura); i++)
            {
                delete[] nueva_matriz_de_pixeles[i];
            }
            delete[] nueva_matriz_de_pixeles;

            for (i = 0; i < altura; i++)
            {
                delete[] matriz_de_imagen[i];
            }
            delete[] matriz_de_imagen;

            cout << "Completado" << endl;
		}

		/*! \fn void Filtro_Deteccion_de_Bordes() 
        *  \brief Esta función aplica el Filtro Detección de Bordes a la matriz de pixeles de una imagen.
        *  \return Esta función no tiene valor de retorno.
        */
        void Filtro_Deteccion_de_Bordes()
        {
            int** matriz_de_imagen = new int*[altura];
            int permisividad = 10;
            cout << "Aplicando Filtro <<Detección de Bordes>>... " << endl << "Digite factor de permisividad de color (Recomendado de 1 a 30): ";
            cin >> permisividad;

            for (x = 0; x < altura; x++)
            {
                matriz_de_imagen[x] = new int[ancho];
            }

            for (x = 0; x < altura; x++)
            {
                for (y = 0; y < ancho; y++)
                {
                    matriz_de_imagen[x][y] = i;
                    i++;
                }
            }

            int** nueva_matriz_de_pixeles = new int*[(ancho*altura)];

            for (i = 0; i < (ancho*altura); i++)
            {
                nueva_matriz_de_pixeles[i] = new int[3];
                for (j = 0; j < 3; j++)
                {
                    nueva_matriz_de_pixeles[i][j] = 0;
                }
            }
            cout << "Detectando bordes... ";
            for (x = 0; x < altura; x++)
            {
                for (y = 0; y < ancho; y++)
                {
                    if (x != 0 && y != 0 && x != altura-1 && y != ancho-1)
                    {
                        for (a = 0; a < 9; a++)
                        {
                            if (a == 0){b = 0; c = -1;}
                            else if (a == 1){b = 0; c = -1;}
                            else if (a == 2){b = -1; c = -1;}
                            else if (a == 3){b = -1; c = 0;}
                            else if (a == 4){b = -1; c = 1;}
                            else if (a == 5){b = 0; c = 1;}
                            else if (a == 6){b = 1; c = 1;}
                            else if (a == 7){b = 1; c = 0;}
                            else if (a == 8){b = 1; c = -1;}

                            if (matriz_de_pixeles[matriz_de_imagen[x][y]][0] > matriz_de_pixeles[matriz_de_imagen[x+b][y+c]][0] + permisividad || matriz_de_pixeles[matriz_de_imagen[x][y]][0] < matriz_de_pixeles[matriz_de_imagen[x+b][y+c]][0] - permisividad)
                            {
                                if (matriz_de_pixeles[matriz_de_imagen[x][y]][1] > matriz_de_pixeles[matriz_de_imagen[x+b][y+c]][1] + permisividad || matriz_de_pixeles[matriz_de_imagen[x][y]][1] < matriz_de_pixeles[matriz_de_imagen[x+b][y+c]][1] - permisividad)
                                {
                                    if (matriz_de_pixeles[matriz_de_imagen[x][y]][2] > matriz_de_pixeles[matriz_de_imagen[x+b][y+c]][2] + permisividad || matriz_de_pixeles[matriz_de_imagen[x][y]][2] < matriz_de_pixeles[matriz_de_imagen[x+b][y+c]][2] - permisividad)
                                    {
                                        for (j = 0; j < 3; j++)
                                        {
                                            nueva_matriz_de_pixeles[matriz_de_imagen[x][y]][j] = matriz_de_pixeles[matriz_de_imagen[x][y]][j];
                                        }
                                        break;
                                    }

                                    for (j = 0; j < 3; j++)
                                    {
                                        nueva_matriz_de_pixeles[matriz_de_imagen[x][y]][j] = matriz_de_pixeles[matriz_de_imagen[x][y]][j];
                                    }
                                    break;
                                }

                                for (j = 0; j < 3; j++)
                                {
                                    nueva_matriz_de_pixeles[matriz_de_imagen[x][y]][j] = matriz_de_pixeles[matriz_de_imagen[x][y]][j];
                                }
                                break;
                            }
                        }
                    }
                }
            }
            cout << "Detección de bordes completado" << endl;

            for (i = 0; i < (ancho*altura); i++)
            {
                for (j = 0; j < 3; j++)
                {
                    matriz_de_pixeles[i][j] = nueva_matriz_de_pixeles[i][j];
                }
            }

            for (i = 0; i < (ancho*altura); i++)
            {
                delete[] nueva_matriz_de_pixeles[i];
            }
            delete[] nueva_matriz_de_pixeles;

            for (i = 0; i < altura; i++)
            {
                delete[] matriz_de_imagen[i];
            }
            delete[] matriz_de_imagen;

            cout << "Completado" << endl;
        }

		/*! \fn void Filtro_Difuminado_de_Movimiento() 
        *  \brief Esta función aplica el Filtro Difuminado de Movimiento a la matriz de pixeles de una imagen.
        *  \return Esta función no tiene valor de retorno.
        */
		void Filtro_Difuminado_de_Movimiento()
		{
			int** matriz_de_imagen = new int*[altura];
			cout << "Aplicando Filtro <<Difuminado de Movimiento>>... " << endl;
			
			for (x = 0; x < altura; x++)
            {
                matriz_de_imagen[x] = new int[ancho];
            }

            for (x = 0; x < altura; x++)
            {
                for (y = 0; y < ancho; y++)
                {
                    matriz_de_imagen[x][y] = i;
                    i++;
                }
            }
			
			int** nueva_matriz_de_pixeles = new int*[(ancho*altura)];

            for (i = 0; i < (ancho*altura); i++)
            {
                nueva_matriz_de_pixeles[i] = new int[3];
                for (j = 0; j < 3; j++)
                {
                    nueva_matriz_de_pixeles[i][j] = 0;
                }
            }
			
			int in;
			cout << "Digite la intensidad de movimiento (Valores entre 1 y 100): ";
			cin >> in;
			
			for(e = 0; e != in; e++){
				for (x = 0; x < altura; x++)
				{
					for (y = 0; y < ancho; y++)
					{
						int izquierda;
						int derecha;
						for (a = 0; a < 3; a++)
						{
							if (y == 0 || y == ancho-1)
							{
								izquierda = matriz_de_pixeles[matriz_de_imagen[x][y]][a];
								derecha = izquierda;
							}	
							else
							{
								izquierda = matriz_de_pixeles[matriz_de_imagen[x][y-1]][a];
								derecha = matriz_de_pixeles[matriz_de_imagen[x][y+1]][a];
							}
							
							nueva_matriz_de_pixeles[matriz_de_imagen[x][y]][a] = (matriz_de_pixeles[matriz_de_imagen[x][y]][a] + izquierda + derecha)/3;
						}
					}
				}
				
				for (i = 0; i < (ancho*altura); i++)
				{
					for (j = 0; j < 3; j++)
					{
						matriz_de_pixeles[i][j] = nueva_matriz_de_pixeles[i][j];
					}
				}
			}

            for (i = 0; i < (ancho*altura); i++)
            {
                delete[] nueva_matriz_de_pixeles[i];
            }
            delete[] nueva_matriz_de_pixeles;

            for (i = 0; i < altura; i++)
            {
                delete[] matriz_de_imagen[i];
            }
            delete[] matriz_de_imagen;

            cout << "Completado" << endl;
		}
		
		/*! \fn void Filtro_Ruido_Sal_y_Pimienta() 
        *  \brief Esta función aplica el Filtro Ruido Sal y Pimienta a la matriz de pixeles de una imagen.
        *  \return Esta función no tiene valor de retorno.
        */
        void Filtro_Ruido_Sal_y_Pimienta()
        {
            cout << "Aplicando Filtro <<Ruido Sal y Pimienta>>... " << endl << "Digite la frecuencia de sal y pimienta (Valores entre 1 y 100): ";
            int frecuencia;
            cin >> frecuencia;
            if(frecuencia < 1 || frecuencia > 100){frecuencia = 50;}

            unsigned semilla = chrono::steady_clock::now().time_since_epoch().count();
            uniform_int_distribution<int> dist(0, 101 - frecuencia);
            default_random_engine generador(semilla);
            int num_aleatorio;

            for (i = 0; i < (ancho*altura); i++)
            {
                num_aleatorio = dist(generador);

                if (num_aleatorio == 0)
                {
                    matriz_de_pixeles[i][0] = 0;
                    matriz_de_pixeles[i][1] = 0;
                    matriz_de_pixeles[i][2] = 0;
                }

                else if (num_aleatorio == 1)
                {
                    matriz_de_pixeles[i][0] = 255;
                    matriz_de_pixeles[i][1] = 255;
                    matriz_de_pixeles[i][2] = 255;
                }
            }

            cout << "Completado" << endl;

        }

		/*! \fn void Filtro_Erosion() 
        *  \brief Esta función aplica el Filtro Erosion a la matriz de pixeles de una imagen.
        *  \return Esta función no tiene valor de retorno.
        */
        void Filtro_Erosion()
        {
			int** matriz_de_imagen = new int*[altura];
            int iteraciones = 1, num_pix, num_pix_comp;
            cout << "Aplicando Filtro <<Erosion>>... " << endl << "Digite cantidad de iteraciones (Máximo recomendado 30): ";
            cin >> iteraciones;

            if (iteraciones < 1){iteraciones = 1;}

            for (x = 0; x < altura; x++)
            {
                matriz_de_imagen[x] = new int[ancho];
            }

            for (x = 0; x < altura; x++)
            {
                for (y = 0; y < ancho; y++)
                {
                    matriz_de_imagen[x][y] = i;
                    i++;
                }
            }

            int** matriz_de_pixeles_original = new int*[(ancho*altura)];

            for (i = 0; i < (ancho*altura); i++)
            {
                matriz_de_pixeles_original[i] = new int[3];
            }

            for (e = 0; e < iteraciones; e++)
            {
                for (i = 0; i < (ancho*altura); i++)
                {
                    for (j = 0; j < 3; j++)
                    {
                        matriz_de_pixeles_original[i][j] = matriz_de_pixeles[i][j];
                    }
                }

                for (x = 0; x < altura; x++)
                {
                    for (y = 0; y < ancho; y++)
                    {
                        if (x != 0 && y != 0 && x != altura-1 && y != ancho-1)
                        {
                            for (a = 0; a < 9; a++)
                            {
                                if (a == 0){b = 0; c = -1;}
                                else if (a == 1){b = 0; c = -1;}
                                else if (a == 2){b = -1; c = -1;}
                                else if (a == 3){b = -1; c = 0;}
                                else if (a == 4){b = -1; c = 1;}
                                else if (a == 5){b = 0; c = 1;}
                                else if (a == 6){b = 1; c = 1;}
                                else if (a == 7){b = 1; c = 0;}
                                else if (a == 8){b = 1; c = -1;}

                                num_pix = (matriz_de_pixeles_original[matriz_de_imagen[x][y]][0] + matriz_de_pixeles_original[matriz_de_imagen[x][y]][1] + matriz_de_pixeles_original[matriz_de_imagen[x][y]][2])/3;
                                num_pix_comp = (matriz_de_pixeles_original[matriz_de_imagen[x+b][y+c]][0] + matriz_de_pixeles_original[matriz_de_imagen[x+b][y+c]][1] + matriz_de_pixeles_original[matriz_de_imagen[x+b][y+c]][2])/3;

                                if (num_pix <= num_pix_comp)
                                {
                                    matriz_de_pixeles[matriz_de_imagen[x+b][y+c]][0] = matriz_de_pixeles_original[matriz_de_imagen[x][y]][0];
                                    matriz_de_pixeles[matriz_de_imagen[x+b][y+c]][1] = matriz_de_pixeles_original[matriz_de_imagen[x][y]][1];
                                    matriz_de_pixeles[matriz_de_imagen[x+b][y+c]][2] = matriz_de_pixeles_original[matriz_de_imagen[x][y]][2];
                                }
                            }
                        }
                    }
                }
            }
			for(x = 0; x < altura; x++)
			{
				delete matriz_de_imagen[x];
			}
			delete[] matriz_de_imagen;
			for (i = 0; i < (ancho*altura); i++)
            {
                delete matriz_de_pixeles_original[i];
            }
			delete[] matriz_de_pixeles_original;
        }

		/*! \fn void Filtro_Dilatacion() 
        *  \brief Esta función aplica el Filtro Dilatacion a la matriz de pixeles de una imagen.
        *  \return Esta función no tiene valor de retorno.
        */
        void Filtro_Dilatacion()
        {
			int** matriz_de_imagen = new int*[altura];
            int iteraciones = 1, num_pix, num_pix_comp;
            cout << "Aplicando Filtro <<Dilatacion>>... " << endl << "Digite cantidad de iteraciones (Máximo recomendado 30): ";
            cin >> iteraciones;

            if (iteraciones < 1){iteraciones = 1;}

            for (x = 0; x < altura; x++)
            {
                matriz_de_imagen[x] = new int[ancho];
            }

            for (x = 0; x < altura; x++)
            {
                for (y = 0; y < ancho; y++)
                {
                    matriz_de_imagen[x][y] = i;
                    i++;
                }
            }

            int** matriz_de_pixeles_original = new int*[(ancho*altura)];

            for (i = 0; i < (ancho*altura); i++)
            {
                matriz_de_pixeles_original[i] = new int[3];
            }

            for (e = 0; e < iteraciones; e++)
            {
                for (i = 0; i < (ancho*altura); i++)
                {
                    for (j = 0; j < 3; j++)
                    {
                        matriz_de_pixeles_original[i][j] = matriz_de_pixeles[i][j];
                    }
                }

                for (x = 0; x < altura; x++)
                {
                    for (y = 0; y < ancho; y++)
                    {
                        if (x != 0 && y != 0 && x != altura-1 && y != ancho-1)
                        {
                            for (a = 0; a < 9; a++)
                            {
                                if (a == 0){b = 0; c = -1;}
                                else if (a == 1){b = 0; c = -1;}
                                else if (a == 2){b = -1; c = -1;}
                                else if (a == 3){b = -1; c = 0;}
                                else if (a == 4){b = -1; c = 1;}
                                else if (a == 5){b = 0; c = 1;}
                                else if (a == 6){b = 1; c = 1;}
                                else if (a == 7){b = 1; c = 0;}
                                else if (a == 8){b = 1; c = -1;}

                                num_pix = (matriz_de_pixeles_original[matriz_de_imagen[x][y]][0] + matriz_de_pixeles_original[matriz_de_imagen[x][y]][1] + matriz_de_pixeles_original[matriz_de_imagen[x][y]][2])/3;
                                num_pix_comp = (matriz_de_pixeles_original[matriz_de_imagen[x+b][y+c]][0] + matriz_de_pixeles_original[matriz_de_imagen[x+b][y+c]][1] + matriz_de_pixeles_original[matriz_de_imagen[x+b][y+c]][2])/3;

                                if (num_pix >= num_pix_comp)
                                {
                                    matriz_de_pixeles[matriz_de_imagen[x+b][y+c]][0] = matriz_de_pixeles_original[matriz_de_imagen[x][y]][0];
                                    matriz_de_pixeles[matriz_de_imagen[x+b][y+c]][1] = matriz_de_pixeles_original[matriz_de_imagen[x][y]][1];
                                    matriz_de_pixeles[matriz_de_imagen[x+b][y+c]][2] = matriz_de_pixeles_original[matriz_de_imagen[x][y]][2];
                                }
                            }
                        }
                    }
                }
            }
			for(x = 0; x < altura; x++)
			{
				delete matriz_de_imagen[x];
			}
			delete[] matriz_de_imagen;
			for (i = 0; i < (ancho*altura); i++)
            {
                delete matriz_de_pixeles_original[i];
            }
			delete[] matriz_de_pixeles_original;
        }

		/*! \fn void Filtro_Inversion() 
        *  \brief Esta función aplica el Filtro Inversión de Color a la matriz de pixeles de una imagen.
        *  \return Esta función no tiene valor de retorno.
        */
        void Filtro_Inversion()
        {
            cout << "Aplicando Filtro <<Inversión de Color>>... ";

            for (i = 0; i < (ancho*altura); i++)
            {
                matriz_de_pixeles[i][0] = (255 - matriz_de_pixeles[i][0]);
                matriz_de_pixeles[i][1] = (255 - matriz_de_pixeles[i][1]);
                matriz_de_pixeles[i][2] = (255 - matriz_de_pixeles[i][2]);
            }

            cout << "Completado" << endl;
        }

		/*! \fn void Filtro_Escala_de_Grises() 
        *  \brief Esta función aplica el Filtro Escala de Grises a la matriz de pixeles de una imagen.
        *  \return Esta función no tiene valor de retorno.
        */
        void Filtro_Escala_de_Grises()
        {
            cout << "Aplicando Filtro <<Transformación a Escala de Grises>>... ";

            for (i = 0; i < (ancho*altura); i++)
            {
                int escala = (matriz_de_pixeles[i][0] + matriz_de_pixeles[i][1] + matriz_de_pixeles[i][2])/3;
                matriz_de_pixeles[i][0] = escala;
                matriz_de_pixeles[i][1] = escala;
                matriz_de_pixeles[i][2] = escala;
            }

            cout << "Completado" << endl;
        }

		/*! \fn void Aplicar_Filtro() 
        *  \brief Esta función es la encargada de llamar a las demás funciones dependiendo del valor que guarde la variable filtro_a_usar.
        *  \return Esta función no tiene valor de retorno.
        */
        void Aplicar_Filtro()
        {
            if (filtro_a_usar == "fg" || filtro_a_usar == "FG"){Filtro_Gaussiano();}

            else if (filtro_a_usar == "fstd" || filtro_a_usar == "FSTD"){Filtro_Desviacion_Estandar();}
            
            else if (filtro_a_usar == "ed" || filtro_a_usar == "ED"){Filtro_Deteccion_de_Bordes();}

            else if (filtro_a_usar == "mb" || filtro_a_usar == "MB"){Filtro_Difuminado_de_Movimiento();}

            else if (filtro_a_usar == "syp" || filtro_a_usar == "SYP"){Filtro_Ruido_Sal_y_Pimienta();}

            else if (filtro_a_usar == "e" || filtro_a_usar == "E"){Filtro_Erosion();}

            else if (filtro_a_usar == "d" || filtro_a_usar == "D"){Filtro_Dilatacion();}

            else if (filtro_a_usar == "i" || filtro_a_usar == "I"){Filtro_Inversion();}

            else if (filtro_a_usar == "g" || filtro_a_usar == "G"){Filtro_Escala_de_Grises();}

            else if (filtro_a_usar == "n" || filtro_a_usar == "N"){cout << "No aplicando ningún filtro... Completado" << endl;}

            else
            {
                cout << "ERROR 2: No se ha detectado un filtro válido. Abortando..." << endl;
                this->aplicar_filtro = false;
            }

            if (aplicar_filtro)
            {
                ConvertidorPixeles cp;
                cp.ExportarImagen(archivo_salida, formato_salida, matriz_de_pixeles, ancho, altura);
            }
        }
};