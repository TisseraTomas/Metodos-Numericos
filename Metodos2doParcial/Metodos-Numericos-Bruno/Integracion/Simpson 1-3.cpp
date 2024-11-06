#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100  // M�ximo n�mero de puntos para la opci�n del archivo

// Definici�n de la funci�n de la cual queremos la derivada: f(x) = exp(sqrt(1 + x)) * log(1 + 2 * x * x)
double funcion(double x) {
	return exp(sqrt(1 + x)) * log(1 + 2 * x * x);
}

// Derivada de f(x) para el c�lculo directo (opcional, si ya tienes los valores puedes omitir esta funci�n).
double derivada(double x, double h) {
	return (funcion(x + h) - funcion(x - h)) / (2 * h);// Aqu� podr�as poner la f�rmula de la derivada si la tienes calculada, o si no, usar diferencias finitas.
	// Placeholder si tienes valores pre-calculados en el archivo
}

// M�todo de Simpson 1/3 usando valores le�dos desde un archivo
double simpson13_archivo(double x[], double fx[], int n) {
	double h = (x[n - 1] - x[0]) / (n - 1);
	double integral = fx[0] + fx[n - 1];
	
	for (int i = 1; i < n - 1; i++) {
		if (i % 2 == 0) {
			integral += 2 * fx[i];
		} else {
			integral += 4 * fx[i];
		}
	}
	
	integral *= h / 3;
	return integral;
}

// M�todo de Simpson 1/3 evaluando la funci�n de la derivada directamente
double simpson13_funcion(double a, double b, int n) {
	double h = (b - a) / n;
	double integral = derivada(a, h) + derivada(b, h);
	
	for (int i = 1; i < n; i++) {
		double x_i = a + i * h;
		if (i % 2 == 0) {
			integral += 2 * derivada(x_i, h);
		} else {
			integral += 4 * derivada(x_i, h);
		}
	}
	
	integral *= h / 3;
	return integral;
}

int main() {
	int opcion;
	printf("Seleccione el m�todo para calcular la integral:\n");
	printf("1. Leer valores desde un archivo\n");
	printf("2. Evaluar la funci�n directamente\n");
	printf("Opci�n: ");
	scanf("%d", &opcion);
	
	if (opcion == 1) {
		// Opci�n 1: Leer valores desde un archivo
		double x[MAX], fx[MAX];
		int n = 0;
		FILE *file = fopen("tabla.txt", "r");
		
		if (file == NULL) {
			printf("Error al abrir el archivo.\n");
			return 1;
		}
		
		// Leer los datos del archivo
		while (fscanf(file, "%lf %lf", &x[n], &fx[n]) == 2) {
			n++;
		}
		fclose(file);
		
		// Validar que el n�mero de puntos sea impar para Simpson 1/3
		if (n < 2 || n % 2 == 0) {
			printf("El archivo debe tener un n�mero impar de puntos (n�mero par de subintervalos).\n");
			return 1;
		}
		
		double resultado = simpson13_archivo(x, fx, n);
		printf("El valor de la integral usando la tabla es: %lf\n", resultado);
		
	} else if (opcion == 2) {
		// Opci�n 2: Evaluar la funci�n directamente
		double a, b;
		int n;
		
		printf("Ingrese el l�mite inferior a: ");
		scanf("%lf", &a);
		printf("Ingrese el l�mite superior b: ");
		scanf("%lf", &b);
		printf("Ingrese el n�mero de subintervalos n (debe ser par): ");
		scanf("%d", &n);
		
		// Validar que el n�mero de subintervalos sea par
		if (n % 2 != 0) {
			printf("El n�mero de subintervalos debe ser par para Simpson 1/3.\n");
			return 1;
		}
		
		double resultado = simpson13_funcion(a, b, n);
		printf("El valor de la integral usando la funci�n es: %lf\n", resultado);
		
	} else {
		printf("Opci�n no v�lida.\n");
	}
	
	return 0;
}




