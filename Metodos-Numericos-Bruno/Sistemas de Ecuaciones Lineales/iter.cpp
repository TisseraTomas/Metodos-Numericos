#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#define FILAS 20
#define COLUMNAS 20

void fileReader(double m[FILAS][COLUMNAS], int* filas, int* columnas);
void matrizA(double a[FILAS][COLUMNAS], double m[FILAS][COLUMNAS], int filas, int columnas);
void matrizB(double b[FILAS], double m[FILAS][COLUMNAS], int filas, int columnas);

void jacobi(double a[FILAS][COLUMNAS], double b[FILAS], int filas);
void gaussSeidel(double a[FILAS][COLUMNAS], double b[FILAS], int filas);
void relajacion(double a[FILAS][COLUMNAS], double b[FILAS], int filas);
bool diagonalmenteDominante(double a[FILAS][COLUMNAS], int filas);

int main() {
	double m[FILAS][COLUMNAS];
	double a[FILAS][COLUMNAS];
	double b[FILAS];
	int filas = 2, columnas = 3;
	fileReader(m, &filas, &columnas);
	matrizA(a, m, filas, columnas);
	matrizB(b, m, filas, columnas);
	
	int scanner;
	printf("Seleccione:\n 1 --> Jacobi \n 2 --> Gauss Seidel \n 3 --> Gauss Seidel con Relajacion\n");
	scanf("%d", &scanner);
	switch(scanner) {
	case 1:
		jacobi(a, b, filas);
		break;
	case 2:
		gaussSeidel(a, b, filas);
		break;
	case 3:
		relajacion(a, b, filas);
		break;
	default:
		printf("\n Se seleccionó mal la opción");
	}
	
	return 0;
}

void fileReader(double m[FILAS][COLUMNAS], int* filas, int* columnas) {
	FILE *fp;
	fp = fopen("data.txt", "r");
	if (fp == NULL) {
		printf("No se puede abrir el archivo\n");
		exit(1);
	}
	
	int fila = 0, columna = 0;
	double valor;
	
	// Leer datos de archivo
	while (fscanf(fp, "%lf", &valor) != EOF) {
		m[fila][columna] = valor;
		columna++;
		// Si alcanzamos el final de la fila
		if (columna >= *columnas - 1) {
			fila++;
			columna = 0;
		}
	}
	
	*filas = fila;
	*columnas = columna + 1;
	fclose(fp);
	
	// Imprimir la matriz leída
	for (int i = 0; i < *filas; i++) {
		for (int j = 0; j < *columnas; j++) {
			printf("%f ", m[i][j]);
		}
		printf("\n");
	}
}

// (Las demás funciones permanecen igual pero asegúrate de liberar la memoria en cada función)


