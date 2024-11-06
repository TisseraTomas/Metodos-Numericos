#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define FILAS 7

using namespace std;
#include <stdio.h>
#include <math.h>

// Función a integrar
double funcion(double x) {
	return 3 * x * x + 1;
}

void trapecioModificado() {
	double a, b;
	int n;
	
	printf("Ingresar a: ");
	scanf("%lf", &a);
	printf("Ingresar b: ");
	scanf("%lf", &b);
	printf("Ingresar n: ");
	scanf("%d", &n);
	
	double h = (b - a) / n;
	double suma1 = 0.0, suma2 = 0.0;
	
	for (int i = 0; i < n; i++) {
		double xi = a + i * h;
		double xi1 = xi + h;
		suma1 += (xi1 - xi) * funcion(xi);
		suma2 += (xi1 - xi) * (funcion(xi1) - funcion(xi)) / 2.0;
	}
	
	double integral = suma1 + suma2;
	printf("El valor de la integral con el método modificado es: %lf\n", integral);
}

int main() {
	trapecioModificado();
	return 0;
}

/*
double funcion(double x){
	return (3*pow(x,2) + 1);
}
	
void trapecioFuncion();	
int main(int argc, char *argv[]) {
	
	trapecioFuncion();
	return 0;
}


void trapecioFuncion(){
	double a,b,n; 
	printf("\nIngresar a\n");
	scanf("%lf",&a);
	printf("\nIngresar b\n");
	scanf("%lf",&b);
	printf("\nIngresar n\n");
	scanf("%lf",&n);
	double h = (b-a)/n;
	//double suma = funcion(a) + funcion (b);
	double suma=0;
	/*for(int i = 1 ; i < n ; i++){
		suma+= 2 * funcion(a + i*h);
	}
	for(int i = 0 ; i < n - 1; i++){
		
		suma+= (h*n) * funcion(a + i*h);
	}
	for(int i = 0 ; i < n - 1; i++){
		
		suma+= (1/2)* (h*n) * (funcion((a + (i+1)*h)) - funcion(a + i*h));
	}
	
	printf("\nEl valor de la integral es: %lf", suma);
	
}
*/
