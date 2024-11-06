#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FILAS 2
#define COLUMNAS 3

void calcularSumatorias(double x[], double y[], int n, double m[FILAS][COLUMNAS]);
void triangulacion(double a[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int filas, int columnas);
void retrostutitucion(double a[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int filas);
void pivot(double a[FILAS][COLUMNAS], double b[FILAS], int filas, int i);
double determinante(double a[FILAS][COLUMNAS], int filas);
double calcularSr(double x[], double y[], int n, double a, double b);
double calcularSt(double y[], int n);
double calcularCoeficienteCorrelacion(double Sr, double St);

int main(int argc, char* argv[]) {
	// Datos de entrada
	int n = 7;
	double x[] = {1.0, 1.2, 1.5, 2.0, 2.6, 2.9, 3.0};
	double y[] = {-0.236, 0.209, 0.853, 1.746, 2.231, 2.163, 2.110};
	
	// Matriz y vector para almacenar las sumatorias
	double m[FILAS][COLUMNAS];
	calcularSumatorias(x, y, n, m);
	
	// Separar la matriz y el vector de sumatorias
	double a[FILAS][FILAS+1];
	double b[FILAS];
	for (int i = 0; i < FILAS; i++) {
		for (int j = 0; j < FILAS; j++) {
			a[i][j] = m[i][j];
		}
		b[i] = m[i][FILAS];
	}
	
	// Llamar a la función de triangulación
	double* sol = (double*)malloc(FILAS * sizeof(double));
	triangulacion(a, b, sol, FILAS, FILAS + 1);
	
	// Extraer los coeficientes a y b
	double coef_a = sol[0];
	double coef_b = sol[1];
	
	// Calcular Sr, St y el coeficiente de correlación r
	double Sr = calcularSr(x, y, n, coef_a, coef_b);
	double St = calcularSt(y, n);
	double r = calcularCoeficienteCorrelacion(Sr, St);
	
	// Mostrar resultados
	printf("\nSr = %lf\n", Sr);
	printf("St = %lf\n", St);
	printf("Coeficiente de correlación r = %lf\n", r);
	
	// Liberar la memoria
	free(sol);
	
	return 0;
}

void calcularSumatorias(double x[], double y[], int n, double m[FILAS][COLUMNAS]) {
	// Inicializar las sumatorias
	double sum_sin2 = 0;
	double sum_sin_cos = 0;
	double sum_cos2 = 0;
	double sum_y_sin = 0;
	double sum_y_cos = 0;
	
	// Calcular las sumatorias
	for (int i = 0; i < n; i++) {
		double sin_x = sin(x[i]);
		double cos_x = cos(x[i]);
		
		sum_sin2 += sin_x * sin_x;
		sum_sin_cos += sin_x * cos_x;
		sum_cos2 += cos_x * cos_x;
		sum_y_sin += y[i] * sin_x;
		sum_y_cos += y[i] * cos_x;
	}
	
	// Llenar la matriz y el vector con las sumatorias
	m[0][0] = sum_sin2;
	m[0][1] = sum_sin_cos;
	m[0][2] = sum_y_sin;
	m[1][0] = sum_sin_cos;
	m[1][1] = sum_cos2;
	m[1][2] = sum_y_cos;
}

void triangulacion(double a[FILAS][FILAS+1], double b[FILAS], double x[FILAS], int filas, int columnas) {
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
	
	printf("Conjunto solución: \n");
	for (int i = 0; i < filas; ++i) {
		printf("x%d = %lf\n", i + 1, x[i]);
	}
}

void pivot(double a[FILAS][COLUMNAS], double b[FILAS], int filas, int i) {
	if (fabs(a[i][i]) < 0.0001) {
		for (int j = i + 1; j < filas; j++) {
			if (fabs(a[j][i]) > fabs(a[i][i])) {
				for (int k = i; k < filas; ++k) {
					printf("Se realizó pivoteo\n");
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

double calcularSr(double x[], double y[], int n, double a, double b) {
	double Sr = 0;
	for (int i = 0; i < n; i++) {
		double fi = a * sin(x[i]) + b * cos(x[i]); // f(xi) = a*sin(xi) + b*cos(xi)
		Sr += pow(y[i] - fi, 2);
	}
	return Sr;
}

double calcularSt(double y[], int n) {
	double promedio_y = 0;
	for (int i = 0; i < n; i++) {
		promedio_y += y[i];
	}
	promedio_y /= n;
	
	double St = 0;
	for (int i = 0; i < n; i++) {
		St += pow(y[i] - promedio_y, 2);
	}
	return St;
}

double calcularCoeficienteCorrelacion(double Sr, double St) {
	return sqrt(1 - Sr / St);
}

