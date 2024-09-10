

#include <stdio.h>

#include <math.h>

double funcion(double x);
void biseccion();

int main() {
    biseccion();
    return 0;
}

double funcion(double x) {
    return pow(x,10) - 1;
}

void biseccion() {
    double a, b, tolerancia;
    int iterator = 0;

    printf("Ingrese el limite inferior del intervalo: ");
    scanf("%lf", &a);
    printf("Ingrese el limite superior del intervalo: ");
    scanf("%lf", &b);
    printf("Ingrese la tolerancia: ");
    scanf("%lf", &tolerancia);

    if (funcion(a) * funcion(b) < 0.0) {
        double c, error;

        do {
            c = (a + b) / 2;
            error = (b - a) / 2;

            if (funcion(a) * funcion(c) > 0) {
                a = c;
            } else if (funcion(a) * funcion(c) < 0) {
                b = c;
            } else {
                break;
            }

            iterator++;

        } while (error > tolerancia);

        printf("\nResultado de la raiz: %.10lf", c);
        printf("\nError estimado: %.10lf", error);
        printf("\nCantidad de iteraciones: %d\n", iterator);
        
    } else {
        printf("\nNo hay raiz o hay un numero par de ellas\n");
    }
}
