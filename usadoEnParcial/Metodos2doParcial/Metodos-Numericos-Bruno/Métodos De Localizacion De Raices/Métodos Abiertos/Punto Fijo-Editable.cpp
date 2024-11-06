#include <stdio.h>
#include <math.h>
#include <iostream>


double g(double);

void PuntoFijo();


int main()
{
	PuntoFijo();
	return 0;
}

double g(double x)
{ // funcion g
	//return 2*x + log(x) - sin(3*x);
	//return  (-log(x) + sin(3*x))/2;
	return pow(((x+5)/2),0.5);
}

double devg(double x, double h)
{ 
	//return (3*g(x)-4*g(x-h)+ g(x-2*h))/(2*h);
	return 4*x - 1;
}


void PuntoFijo()
{
	// acordate que tenes que inicializarlo donde quieras, va a funcionar igual. Te puede llevar +- iteraciones pero es lo mismo
	
	double xViejo; // es el punto de partida digamos
	double xNuevo;
	double h = 0.01;
	int contador = 0;
	double error = 0;
	double tolerancia;
	double raizExacta= (1+ pow(41, 0.5))/4;
	printf("Ingrese la tolerancia\n"); 
	scanf("%lf", &tolerancia);
	printf("Ingrese el punto inicial\n"); 
	scanf("%lf", &xViejo);
	do
	{
		
		contador++;
		//(g(xViejo + 0.01) - g(xViejo)) / 0.01)
		//fabs(devg(xViejo, h))
		if ((g(xViejo + 0.01) - g(xViejo)) / (0.01)>= 1) // Derivada >= 1 //CRITERIO DE CONVERGENCIA
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
		
	} while (error > tolerancia && contador<7);
	
	printf("\n\n\nEl punto fijo de g(x), es decir la raiz de f es: %.12f", xNuevo);
	printf("\nEl valor del error en la raiz es de: %.12f", error);
	printf("\nRaiz Exacta: %.12f", raizExacta);
	//printf("\nEl valor del error EXACTO en la raiz es de: %.12f", fabs(xNuevo- raizExacta)); //ERROR ABSOLUTO EXACTO = fabs(xNuevo - RaizExacta) 
	printf("\nLa resolucion del problema toma %d iteraciones", contador);
}

