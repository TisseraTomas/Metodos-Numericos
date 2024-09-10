#include <stdio.h>
#include <math.h>


double g(double);

void PuntoFijo();


int main()
{
    PuntoFijo();
    return 0;
}

double g(double x)
{ // funcion g
    return pow(x, 5) - 3 * pow(x, 3) - 2 * pow(x, 2) + 2;
}

double devg(double x)
{ // funcion g
	return 5*pow(x, 4) - 9 * pow(x, 2) - 4 * x;
}


void PuntoFijo()
{
    // acordate que tenes que inicializarlo donde quieras, va a funcionar igual. Te puede llevar +- iteraciones pero es lo mismo

    double xViejo; // es el punto de partida digamos
    double xNuevo;
    int contador = 0;
    double error = 0;
    double tolerancia;
    printf("Ingrese la tolerancia\n"); 
    scanf("%lf", &tolerancia);
    printf("Ingrese el punto inicial\n"); 
    scanf("%lf", &xViejo);
    do
    {

        contador++;
		//(g(xViejo + 0.01) - g(xViejo)) / 0.01)
        if (fabs(devg(xViejo))>= 1) // Derivada >= 1 //CRITERIO DE CONVERGENCIA
        { 

            printf("\n\nNo cumple con el criterio de convergencia. El metodo diverge (|g'(x)|>1)");
            break;
        }
        else
        {

            xNuevo = g(xViejo);
            error = fabs(xNuevo - xViejo); //ERROR ABSOLUTO APROXIMADO
            
			xViejo = xNuevo;
        }

    } while (error > tolerancia);

    printf("\n\n\nEl punto fijo de g(x), es decir la raiz de f es: %.12f", xNuevo);
    printf("\nEl valor del error en la raiz es de: %.12f", error); //ERROR ABSOLUTO EXACTO = fabs(xNuevo - RaizExacta) 
    printf("\nLa resolucion del problema toma %d iteraciones", contador);
}
