#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iomanip>

double f(double);
double fPrima(double);
void NewtonRaphson();


int main (){
    NewtonRaphson();
    return 0;
}

double f(double x){
    return pow(x, x) - 5;////
}
double fPrima(double x){
    return pow(x, x)*(log(x)+1);////
}
void NewtonRaphson(){
    double xViejo , error , tolerancia , xNuevo;
    int contador = 0;
    printf("Ingrese la tolerancia\n"); 
    scanf("%lf", &tolerancia);
    printf("Ingrese el punto inicial\n"); 
    scanf("%lf", &xViejo);
    do{
        contador ++ ;
        
        if(fabs(fPrima(xViejo)) < 1e-10){ //CRITERIO DE CONVERGENCIA
            printf("\n********DERIVADA PEQUE�A********\n");
            exit(0);
        } else{
            xNuevo = xViejo - (f(xViejo)/fPrima(xViejo));
            error = fabs(xNuevo - xViejo);
            xViejo = xNuevo;
        }

    }while(error > tolerancia && contador < 10000 );
	
	printf("\n\n\nLa raiz de f es: %.12f", xNuevo);
    printf("\n\n\nLa raiz de f es: %.101f", xNuevo);
    printf("\nEl valor del error en la raiz es de: %.10lf", error);
    printf("\nLa resolucion del problema toma %d iteraciones", contador);
}

