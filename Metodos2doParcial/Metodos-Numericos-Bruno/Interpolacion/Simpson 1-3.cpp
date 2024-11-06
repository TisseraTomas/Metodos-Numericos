#include <stdio.h>
#include <stdlib.h>

#define MAX_POINTS 100

double simpson13(double x[], double f_prime[], int n) {
	double h = (x[n - 1] - x[0]) / (n - 1);
	double integral = f_prime[0] + f_prime[n - 1];
	
	// Suma las contribuciones de Simpson 1/3
	for (int i = 1; i < n - 1; i++) {
		if (i % 2 == 0) {
			integral += 2 * f_prime[i];
		} else {
			integral += 4 * f_prime[i];
		}
	}
	integral *= h / 3;
	return integral;
}

int main() {
	double x[MAX_POINTS], f_prime[MAX_POINTS];
	int n = 0;
	
	FILE *file = fopen("tabla.txt", "r");
	if (file == NULL) {
		printf("Error al abrir el archivo.\n");
		return 1;
	}
	
	// Leer los valores de x y f'(x) desde el archivo
	while (fscanf(file, "%lf %lf", &x[n], &f_prime[n]) == 2) {
		n++;
		if (n > MAX_POINTS) {
			printf("Se excedió el número máximo de puntos.\n");
			fclose(file);
			return 1;
		}
	}
	fclose(file);
	
	// Verifica que tengamos un número impar de puntos para aplicar Simpson 1/3
	if (n < 3 || n % 2 == 0) {
		printf("El número de puntos debe ser impar y mayor que 2 para Simpson 1/3.\n");
		return 1;
	}
	
	// Calcula la integral usando Simpson 1/3
	double resultado = simpson13(x, f_prime, n);
	printf("El valor de la integral es: %lf\n", resultado);
	
	return 0;
}


