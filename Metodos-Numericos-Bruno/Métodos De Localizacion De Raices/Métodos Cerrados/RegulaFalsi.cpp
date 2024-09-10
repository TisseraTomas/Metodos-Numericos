
#include <stdio.h>
#include <math.h>

double funcion(double x);

void regulaFalsi();

int main() {

    regulaFalsi();

    return 0;
}

double funcion(double x) {

    return  pow(x,10) - 1;

}

void regulaFalsi() {

    double a, b, tolerancia, c, error, cAnterior;
    int contador = 0;

    printf("Ingrese el limite inferior del intervalo: ");
    scanf("%lf", &a);
    printf("Ingrese el limite superior del intervalo: ");
    scanf("%lf", &b);
    printf("Ingrese la tolerancia: ");
    scanf("%lf", &tolerancia);

        if (funcion(a) * funcion(b) < 0.0) {
            do {
                contador++;
				
				cAnterior = c;  // Guardar la aproximación anterior
				
                c = (a*funcion(b) - b*funcion(a)) / (funcion(b) - funcion(a));
               

                if (funcion(a) * funcion(c) > 0) {
                    a = c;
                } else if (funcion(a) * funcion(c) < 0) {
                    b = c;
                } else {
                    break;
                }
				
				error = fabs(c - cAnterior);
                //error = (b - a) / 2;

            } while (error > tolerancia);
			
			printf("\nValor de la función en la raíz: %.10lf", funcion(c));
            printf("\nResultado de la raiz: %.10lf", c);
            printf("\nError estimado: %.10lf", error);
            printf("\nCantidad de iteraciones: %d\n", contador);
            
        } else {
            printf("\nNo hay raiz o hay un numero par de ellas\n");
        }
    
}
