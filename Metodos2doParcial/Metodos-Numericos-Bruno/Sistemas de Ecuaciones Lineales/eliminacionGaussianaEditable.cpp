#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FILAS 100
#define COLUMNAS 101

void fileReader(double m[FILAS][COLUMNAS], int* filas, int* columnas);
void matrizA(double a[FILAS][COLUMNAS], double m[FILAS][COLUMNAS], int filas, int columnas);
void matrizB(double b[FILAS], double m[FILAS][COLUMNAS], int filas, int columnas);
void triangulacion(double a[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int filas, int columnas);
void retrostutitucion(double a[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int filas);
void pivot(double a[FILAS][COLUMNAS], double b[FILAS], int filas, int i);
double determinante(double a[FILAS][COLUMNAS], int filas);

int main(int argc, char* argv[]) {
	double m[FILAS][COLUMNAS];
	double a[FILAS][COLUMNAS];
	double b[FILAS];
	int filas = 100, columnas = 101;
	
	// Lectura del archivo
	fileReader(m, &filas, &columnas);
	matrizA(a, m, filas, columnas);
	matrizB(b, m, filas, columnas);
	
	// Llamar a la funci�n de triangulaci�n
	double* x = (double*)malloc(filas * sizeof(double));
	triangulacion(a, b, x, filas, columnas);
	
	// Liberar la memoria de x
	free(x);
	
	return 0;
}

void fileReader(double m[FILAS][COLUMNAS], int* filas, int* columnas) {
	FILE *fp = fopen("data.txt", "r");
	if (fp == NULL) {
		printf("No se puede abrir el archivo\n");
		exit(1); // Termina el programa si no se puede abrir el archivo
	}
	
	int fila = 0, columna = 0;
	int max_columnas = 0;
	double valor;
	
	// Leer el archivo l�nea por l�nea y n�mero por n�mero
	while (fscanf(fp, "%lf", &valor) != EOF) {
		m[fila][columna] = valor;
		columna++;
		
		// Si encontramos un salto de l�nea, avanzamos a la siguiente fila
		char next_char = fgetc(fp);
		if (next_char == '\n' || next_char == EOF) {
			fila++;
			if (columna > max_columnas) {
				max_columnas = columna;  // Actualizamos el m�ximo de columnas
			}
			columna = 0;  // Reiniciamos las columnas para la siguiente fila
		}
	}
	
	fclose(fp);
	
	*filas = fila;
	*columnas = max_columnas;
}

void matrizA(double a[FILAS][COLUMNAS], double m[FILAS][COLUMNAS], int filas, int columnas) {
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas - 1; j++) {
			a[i][j] = m[i][j];
		}
	}
}

void matrizB(double b[FILAS], double m[FILAS][COLUMNAS], int filas, int columnas) {
	for (int i = 0; i < filas; i++) {
		b[i] = m[i][columnas - 1];
	}
}

void triangulacion(double a[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int filas, int columnas) {
	for (int i = 0; i < (filas - 1); i++) {
		pivot(a, b, filas, i);
		for (int j = i + 1; j < filas; j++) {
			double factor = -a[j][i] / a[i][i];
			for (int k = 0; k < columnas - 1; ++k) { // Usar columnas - 1
				a[j][k] = a[i][k] * factor + a[j][k];
			}
			b[j] = b[i] * factor + b[j];
		}
	}
	
	double norma = determinante(a, filas);
	if (norma == 0.0) {
		printf("\n\nMatriz singular\n");
	} else {
		retrostutitucion(a, b, x, filas);
	}
}

void retrostutitucion(double a[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int filas) {
	double value = 0;
	value = b[filas - 1] / a[filas - 1][filas - 1];
	x[filas - 1] = value;
	for (int i = filas - 2; i >= 0; --i) {
		double sum = 0;
		for (int j = i + 1; j < filas; ++j) {
			sum = sum + a[i][j] * x[j];
		}
		value = (b[i] - sum) / a[i][i];
		x[i] = value;
	}
	
	printf("Conjunto soluci�n: \n");
	for (int i = 0; i < filas; ++i) {
		printf("x%d = %lf\n", i + 1, x[i]);
	}
}

void pivot(double a[FILAS][COLUMNAS], double b[FILAS], int filas, int i) {
	if (fabs(a[i][i]) < 0.0001) {
		for (int j = i + 1; j < filas; j++) {
			if (fabs(a[j][i]) > fabs(a[i][i])) {
				for (int k = i; k < filas; ++k) {
					printf("Se realiz� pivoteo\n");
					double swap = a[i][k];
					a[i][k] = a[j][k];
					a[j][k] = swap;
				}
				double swap = b[i];
				b[i] = b[j];
				b[j] = swap;
			}
		}
	}
}

double determinante(double a[FILAS][COLUMNAS], int filas) {
	double norma = 1;
	for (int i = 0; i < filas; i++) {
		norma = norma * a[i][i];
	}
	printf("\nLa norma es: %lf\n", norma);
	return norma;
}
