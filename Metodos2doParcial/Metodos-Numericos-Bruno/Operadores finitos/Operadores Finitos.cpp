#include <stdio.h>
#include <stdlib.h>

#define N 7  // Número de puntos en la tabla (ajústalo si cambia el número de puntos)

// Función para calcular las derivadas
void calcularDerivadas(double x[], double fx[], double derivada[], double h) {
	// Derivada hacia adelante en el primer punto
	derivada[0] = (fx[1] - fx[0]) / 2;
	// Derivada centrada en los puntos intermedios
	for (int i = 1; i < N - 1; i++) {
		derivada[i] = (fx[i + 1] - fx[i - 1]) / (2 * h);
	}
	
	// Derivada hacia atrás en el último punto
	derivada[N - 1] = (fx[N - 1] - fx[N - 2]) / h;
}

int main() {
	double x[N], fx[N], derivada[N];
	double h;
	FILE *file;
	
	// Abrir el archivo de texto en modo lectura
	file = fopen("tablaOp.txt", "r");
	if (file == NULL) {
		printf("Error al abrir el archivo.\n");
		return 1;
	}
	
	// Leer los valores de x y f(x) desde el archivo
	for (int i = 0; i < N; i++) {
		if (fscanf(file, "%lf %lf", &x[i], &fx[i]) != 2) {
			printf("Error al leer los datos del archivo.\n");
			fclose(file);
			return 1;
		}
	}
	
	// Cerrar el archivo después de leer los datos
	fclose(file);
	for(int i=0; i < N; i++){
		printf("%lf\n", fx[i]);
	}
	
	// Calcular h asumiendo que los puntos están uniformemente distribuidos
	h = x[1] - x[0];
	printf("h= %lf", h);
	
	// Calcular las derivadas hacia adelante, centrada y hacia atrás
	calcularDerivadas(x, fx, derivada, h);
	
	// Imprimir los resultados
	printf("\nValores de la derivada en cada punto:\n");
	
	for (int i = 0; i < N; i++) {
		printf("f'(%lf) = %lf\n", x[i], derivada[i]);
	}
	
	return 0;
}



