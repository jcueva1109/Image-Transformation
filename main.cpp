#include <iostream>
#include<opencv2\opencv.hpp>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include "CImg.h"
using namespace std;
using namespace cv;

#define length(x) (sizeof(x) / sizeof(x[0]))

//Prototipos
int Menu();
int cargarImagen();
int convolucion();
int filtroGauss(Mat);
int moda();
int histograma(Mat);
int leerImagen();
int guardarImagen();

int main() {

	//Menu();
	//leerImagen();
	
	//Fin del codigo
	system("pause > null");
	return 0;

}

int Menu() {

	int opcion = 0;

	while (opcion != 4) {

		cout << "			Bienvenido!" << endl;
		cout << "Selecciona la opcion a ejecutar: " << endl;
		cout << "1. Escala de Grises" << endl;
		cout << "2. Desplazamiento" << endl;
		cout << "3. Filtro Gaussiano" << endl;
		cout << "4. Salir" << endl;
		cin >> opcion;

		switch (opcion) {
		case 1:
			cargarImagen();
			break;
		case 2:
			cargarImagen();
			break;
		case 3:
			cargarImagen();
			break;
		case 4:
			cout << "Finalizando Ejecucion..." << endl;
			break;


		}

	}
	return 0;
}

/*
*	Objetivo de Cargar Imagen:
*		En esta el usuario ingresa la imagen a transformar y la muestra en pantalla
*		Seguidamente nos movemos a la funcion leer imagen
*/

int cargarImagen() {

	Mat imagen = imread("lena.jpg");
	imshow("Original", imagen);
	leerImagen();

	return 0;

}

int convolucion()
{
	int mitad, i, j, m, n, mm, nn, ii, jj, acumulador;

	// Defino Kernel
	int kernel[3][3] = {
						{1, 1, 1},
						{1, 1, 1},
						{1, 1, 1}
	};

	// Defino Imagen
	int image[7][7] = {
						{9, 2, 7, 8, 1, 6, 5},
						{5, 5, 6, 7, 8, 2, 5},
						{5, 5, 6, 7, 8, 2, 5},
						{5, 5, 6, 7, 8, 2, 5},
						{1, 4, 2, 4, 3, 8, 1},
						{8, 4, 9, 1, 3, 7, 3},
						{3, 6, 0, 4, 5, 8, 7}
	};

	// Defino Imagen resultante
	int result[7][7];

	// Hallar la mitad del kernel para posicionar la matriz desde ahi
	mitad = length(kernel) / 2;

	/* Proceso de convolucion
	 * Recorro la imagen en los dos primeros for, al igual que el kernel
	 * en la variable mm hallo el indice de la fila del kernel alrevez, al
	 * igual que la variable nn, almacena la columna del kernel alrevez,
	 * las variables ii,jj son para almacenar la posicion de las imagenes tomando
	 * en cuenta su limite exterior es decir i-1, j-1,la variable acumulador almacena el resultado
	 * que luego es asignado en la posicion de la imagen resultante
	 */

	for (i = 0; i < length(image); ++i) // Filas
	{
		for (j = 0; j < length(image); ++j) // Columnas
		{
			// Variable acumuladora
			acumulador = 0;

			for (m = 0; m < length(kernel); ++m) // Filas del Kernel
			{
				mm = length(kernel) - 1 - m; // Indice de la fila del kernel alrevez

				for (n = 0; n < length(kernel); ++n) // Columnas del kernel
				{
					nn = length(kernel) - 1 - n; // Indice de la columna del kernel alrevez


					ii = i + (m - mitad);
					jj = j + (n - mitad);

					// validar limites de la imagen 00000
					if (ii >= 0 && ii < length(image) && jj >= 0 && jj < length(image))
					{
						acumulador += image[ii][jj] * kernel[mm][nn];
					}
				}
			}
			result[i][j] = acumulador;
		}
	}

	// Muestro imagen final aplicando la convolucion
	cout << endl << endl << "Imagen Aplicando convolucion: " << endl;
	for (int i = 0; i < length(result); i++)
	{
		for (int j = 0; j < length(result); j++)
		{
			cout << " " << result[i][j];
		}
		cout << endl;
	}

	cout << endl;

	return 0;

}

int moda() {

	int array[256];
	int max = 0, moda, r = 0;
	int frec[256] = { 0 };

	Mat imagen = imread("lena.jpg");
	cout << "La imagen tiene: " << imagen.rows << " pixeles de alto x " << imagen.cols << " pixeles de ancho " << endl;

	for (int i = 0; i < imagen.rows; i++) {
		for (int j = 0; j < imagen.cols; j++) {

			uchar pixel = imagen.at<uchar>(i, j);

			for (int x = 0; x < 256; x++) {
				array[x] = pixel;
			}

			for (int y = 0; y <= 255; y++) {
				frec[array[y]]++;
			}

			for (int rango = 1; rango <= 255; rango++) {
				if (frec[rango] > max) {
					max = frec[rango];
					moda = rango;
					r++;
				}
			}

		}

	}

	cout << "La moda es: " << moda << " y se repite " << r << endl;
	waitKey(0);
	return 0;
}

int histograma(Mat m) {

	int colores[256];
	for (int i = 0; i < 256; i++) {

		colores[i] = 0;

	}

	for (int j = 0; j < m.rows; j++) {
		for (int i = 0; i < m.cols; i++) {

			int pixel = m.at<uchar>(j, i);
			colores[pixel]++;

		}
	}

	//Impresion de cantidad de colores
	cout << "Color = Cantidad" << endl;
	for (int i = 0; i < 256; i++) {
		if (colores[i] > 0) {
			cout << i << " = " << colores[i] << endl;
		}
	}

	return 0;
}

/*
*	Objetivo de Leer Imagen:
*		Obtener la matriz de la imagen 
*/

int leerImagen() {

	Mat image = imread("lena.jpg");

	for (size_t i = 0; i < image.rows; i++) {

		for (size_t j = 0; j < image.cols; j++) {

			Vec3b pixel = image.at<Vec3b>(i, j);

			uchar B = pixel[0];
			uchar G = pixel[1];
			uchar R = pixel[2];

		}

	}

	filtroGauss(image);
	//cout << "Matriz: \n" << format(image, Formatter::FMT_CSV) << endl;
	return 0;

}

int filtroGauss(Mat imagen) {

	//Variables a necesitar
	int mitad, i, j, m, n, mm, nn, ii, jj, acumulador;

	//Defino el kernel Filtro Gauss
	int kernel[5][5] = {

							{1,2,3,1,1},
							{2,7,11,7,2},
							{3,11,17,11,3},
							{2,7,11,7,1},
							{1,2,3,2,1}


	};

	//Defino Imagen Resultante
	int result[225][225];

	//Hallar la mitad del kernel para posicionar la matriz desde ahi
	mitad = length(kernel) / 2;

	/* Proceso de convolucion
	 * Recorro la imagen en los dos primeros for, al igual que el kernel
	 * en la variable mm hallo el indice de la fila del kernel alrevez, al
	 * igual que la variable nn, almacena la columna del kernel alrevez,
	 * las variables ii,jj son para almacenar la posicion de las imagenes tomando
	 * en cuenta su limite exterior es decir i-1, j-1,la variable acumulador almacena el resultado
	 * que luego es asignado en la posicion de la imagen resultante
	 */

	for (i = 0; i < imagen.rows; ++i) // Filas
	{
		for (j = 0; j < imagen.cols; ++j) // Columnas
		{
			// Variable acumuladora
			acumulador = 0;

			for (m = 0; m < length(kernel); ++m) // Filas del Kernel
			{
				mm = length(kernel) - 1 - m; // Indice de la fila del kernel alrevez

				for (n = 0; n < length(kernel); ++n) // Columnas del kernel
				{
					nn = length(kernel) - 1 - n; // Indice de la columna del kernel alrevez


					ii = i + (m - mitad);
					jj = j + (n - mitad);

					// validar limites de la imagen 00000
					if (ii >= 0 && ii < imagen.rows && jj >= 0 && jj < imagen.cols)
					{
						acumulador += imagen[ii][jj] * kernel[mm][nn];
					}
				}
			}
			result[i][j] = acumulador;
		}
	}


	return 0;

}

int guardarImagen() {

	Mat image;
	image = imread("night.jpg", 1);


	Mat gray_image;
	cvtColor(image, gray_image, CV_BGR2GRAY);

	imwrite("imagenProcesada-Gris.jpg", gray_image);

	namedWindow("", CV_WINDOW_AUTOSIZE);
	namedWindow("Gray image", CV_WINDOW_AUTOSIZE);

	imshow("night.jpg", image);
	imshow("Gray image", gray_image);

	waitKey(0);

	return 0;

}