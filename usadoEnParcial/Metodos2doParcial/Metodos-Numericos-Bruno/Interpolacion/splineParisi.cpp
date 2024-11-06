#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Función para leer el archivo y devolver el número de filas y los datos leídos
int lecturaArchivo(double **x, double **y) {
	FILE *fp;
	char ch;
	
	// Abre el archivo
	fp = fopen("tabla.dat", "r");
	if (fp == NULL) {
		puts("No se puede abrir el archivo");
		return -1;
	}
	
	// Contador de filas
	int filas = 0;
	char c;
	
	// Contar líneas en el archivo para determinar el número de filas
	while ((c = fgetc(fp)) != EOF) {
		if (c == '\n') {
			filas++;
		}
	}
	
	printf("Número de filas = %i\n", filas);
	
	// Cerrar y reabrir el archivo para resetear el puntero
	fclose(fp);
	fp = fopen("tabla.dat", "r");
	
	// Inicializar los arreglos para almacenar los datos
	*x = (double *)malloc(filas * sizeof(double));
	*y = (double *)malloc(filas * sizeof(double));
	
	// Leer datos en los arreglos x e y
	int i;
	for (i = 0; i < filas; i++) {
		if (fscanf(fp, "%lf %lf", &(*x)[i], &(*y)[i]) != 2) {
			printf("Error al leer los datos en la fila %d\n", i + 1);
			break;
		}
	}
	
	fclose(fp);
	
	// Imprimir la tabla para verificar los datos leídos
	printf("\nLOS ELEMENTOS DE LA TABLA SON:\n");
	for (i = 0; i < filas; i++) {
		printf("%lf \t %lf\n", (*x)[i], (*y)[i]);
	}
	
	return filas;
}

int main() {
	double *x, *y;
	int filas = lecturaArchivo(&x, &y);
	if (filas == -1) {
		return 1;
	}
	
	printf("\nSPLINE CUBICA NATURAL\n");
	
	int n = filas;
	int N = 4 * (n - 1);  // Número de ecuaciones
	
	// Crear matrices dinámicas
	double **m = (double **)malloc(N * sizeof(double *));
	for (int i = 0; i < N; i++) {
		m[i] = (double *)malloc(N * sizeof(double));
	}
	double *b = (double *)malloc(N * sizeof(double));
	double *a = (double *)malloc(N * sizeof(double));
	double aux;
	double valor;
	double resultado;
	
	printf("Cantidad de puntos: %d\n", n);
	
	// Inicializar matriz m y vector b en cero
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			m[i][j] = 0;
		}
		b[i] = 0;
	}
	
	// Establecer ecuaciones para los polinomios en cada intervalo
	for (int i = 1; i < n; i++) {
		int row1 = 2 * (i - 1);
		int row2 = 2 * (i - 1) + 1;
		
		m[row1][4 * (i - 1)]     = 1;
		m[row1][4 * (i - 1) + 1] = x[i - 1];
		m[row1][4 * (i - 1) + 2] = x[i - 1] * x[i - 1];
		m[row1][4 * (i - 1) + 3] = x[i - 1] * x[i - 1] * x[i - 1];
		b[row1] = y[i - 1];
		
		m[row2][4 * (i - 1)]     = 1;
		m[row2][4 * (i - 1) + 1] = x[i];
		m[row2][4 * (i - 1) + 2] = x[i] * x[i];
		m[row2][4 * (i - 1) + 3] = x[i] * x[i] * x[i];
		b[row2] = y[i];
	}
	
	// Derivadas primeras
	for (int i = 1; i < n - 1; i++) {
		int row = 2 * (n - 1) + (i - 1);
		
		m[row][4 * (i - 1) + 1] = 1;
		m[row][4 * (i - 1) + 2] = 2 * x[i];
		m[row][4 * (i - 1) + 3] = 3 * x[i] * x[i];
		
		m[row][4 * i + 1] = -1;
		m[row][4 * i + 2] = -2 * x[i];
		m[row][4 * i + 3] = -3 * x[i] * x[i];
	}
	
	// Derivadas segundas
	for (int i = 1; i < n - 1; i++) {
		int row = 3 * (n - 1) - 2 + i;
		
		m[row][4 * (i - 1) + 2] = 2;
		m[row][4 * (i - 1) + 3] = 6 * x[i];
		
		m[row][4 * i + 2] = -2;
		m[row][4 * i + 3] = -6 * x[i];
	}
	
	// Condiciones de spline natural
	m[N - 2][2] = 2;
	m[N - 2][3] = 6 * x[0];
	b[N - 2] = 0;
	
	m[N - 1][N - 2] = 2;
	m[N - 1][N - 1] = 6 * x[n - 1];
	b[N - 1] = 0;
	
	// Resolución de sistema lineal por eliminación gaussiana
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			double factor = m[j][i] / m[i][i];
			for (int k = i; k < N; k++) {
				m[j][k] -= factor * m[i][k];
			}
			b[j] -= factor * b[i];
		}
	}
	
	// Sustitución regresiva
	for (int i = N - 1; i >= 0; i--) {
		a[i] = b[i];
		for (int j = i + 1; j < N; j++) {
			a[i] -= m[i][j] * a[j];
		}
		a[i] /= m[i][i];
	}
	
	// Pedir valor a interpolar
	printf("Ingrese el valor que desea interpolar: ");
	scanf("%lf", &valor);
	
	// Evaluar el valor en el intervalo correcto
	for (int i = 0; i < n - 1; i++) {
		if (valor >= x[i] && valor <= x[i + 1]) {
			resultado = a[4 * i] + a[4 * i + 1] * valor + a[4 * i + 2] * valor * valor + a[4 * i + 3] * valor * valor * valor;
			printf("Interpolación para x = %lf es y = %lf\n", valor, resultado);
			break;
		}
	}
	
	// Liberar la memoria
	for (int i = 0; i < N; i++) {
		free(m[i]);
	}
	free(m);
	free(b);
	free(a);
	free(x);
	free(y);
	
	return 0;
}


