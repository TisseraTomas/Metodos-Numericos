#include <iostream>
#include <stdio.h>
#include <math.h>
#define _USE_MATH_DEFINES
using namespace std;

double f (double x);	//Funcion a resolver
void Simpsonfuncion (); //Metodo

int main(int argc, char *argv[]) {
	Simpsonfuncion();
	return 0;
}

double f (double x){
	return exp(sqrt(1 + x)) * log(1 + 2 * (x * x));
}

void Simpsonfuncion (){
	double pi = 3.14159;
	
	//Inicializar datos
	double a, b, h, suma, x;
	int n;
	
	//Definir limites de integracion
	a = 0;
	b = 1;
	
	
	//Pedir datos
	printf("\nIngrese n: ");
	scanf("%d", &n);
	
	//Verificar que n sea par
	if (n % 2 != 0){
		printf ("La cantidad de intervalos debe ser par.");
	}
	
	h = (b-a)/n;
	suma = f(a)+f(b);
	
	//Calcular I
	for (int i = 1; i < n; i += 2) {
		x = a + i * h;
		suma += 4 * f(x);
	}
	
	// Calcular los términos con coeficiente 2
	for (int i = 2; i < n; i += 2) {
		x = a + i * h;
		suma += 2 * f(x);
	}
	
	// Calcular el resultado final
	suma = (h / 3) * suma;
	
	printf("Resultado: %lf\n", suma);
}
	
