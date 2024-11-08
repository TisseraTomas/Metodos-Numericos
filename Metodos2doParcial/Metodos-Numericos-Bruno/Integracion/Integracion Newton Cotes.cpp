#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define FILAS 7

using namespace std;

double funcion(double x){
	return (3*pow(x,2) + 1);
}
	
void trapecioFuncion();	
void trapecioTabla();

void simpsonCompuestoFuncion();
void simpsonCompuestoTabla();


bool sonEquidistantes(double arreglo[FILAS][2], int filas);
	
	
int main(int argc, char *argv[]) {
	
	//trapecioFuncion();
	trapecioTabla();
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
	double suma = funcion(a) + funcion (b);
	
	for(int i = 1 ; i < n ; i++){
		suma+= 2 * funcion(a + i*h);
	}
	
	double integral = (h/2) * suma;
	printf("\nEl valor de la integral es: %lf", integral);
	
}

void trapecioTabla(){
	double m[FILAS][2]={}; //{{1.1,-1.496075},{1.2,-1.629170},{1.3,-1.673110},{1.4,-1.620830},{1.5,-1.479430},{1.6,-1.260000},{1.7,-0.965395},{1.8,-0.565015}, {1.9,-0.140990}};
	int filas = 7;
	FILE *file;
	file = fopen("tabla.txt", "r");
	if (file == NULL) {
		printf("Error al abrir el archivo.\n");
		exit(0);
	}
	
	// Leer los valores de x y f(x) desde el archivo
	for (int i = 0; i < filas; i++) {
		if (fscanf(file, "%lf %lf", &m[i][0], &m[0][i]) != 2) {
			printf("Error al leer los datos del archivo.\n");
			fclose(file);
			exit(0);
		}
	}
	
	// Cerrar el archivo despu�s de leer los datos
	fclose(file);
	int n = filas - 1;
	bool flag = sonEquidistantes(m,filas);
	double suma; 
	if (flag){
		suma = m[0][1] + m[filas - 1][1];
		for(int i = 1 ; i < n ; i++){
			suma+= 2*m[i][1];
		}
		double integral = ((m[1][0] - m[0][0])/2)*suma;
		printf("\nLa integral es: %lf",integral);
	}else{
		printf("\nLos puntos no son equidistantes");
		suma = 0; 
		for(int i = 0 ; i < n ; i++){
			suma+= ((m[i+1][0]-m[i][0])/2)* (m[i+1][1] + m[i][1]);
		}
		
		printf("\nLa integral es: %lf",suma);
	}

}

void simpsonCompuestoFuncion(){
	double a,b;
	int n; 
	printf("\nIngrese el limite de integracion inferior\n");
	scanf("%lf",&a);
	printf("\nIngrese el limite de integracion superior\n");
	scanf("%lf",&b);
	printf("\nIngrese la cantidad de intervalos\n");
	scanf("%d",&n);
	if ((n % 2) != 0) {
		printf("El numero de intervalos debe ser par\n");
		return;
	}
	
	double h = (b-a)/n;
	double suma = funcion(a) + funcion (b);
	double x;
	for(int i = 1 ; i < (n/2) ; ++i){
		x = a + (2 * i * h);
		suma = suma + (2 * funcion(x)) + (4 * funcion(x-h));
	}
	
	suma = (h / 3) * (suma + 4 * funcion(b - h));
	
	printf("\nEl valor de la integral es: %lf", suma);
	
}

void simpsonCompuestoTabla(){
	double m[FILAS][2] = {};//{{1.1,-1.496075},{1.2,-1.629170},{1.3,-1.673110},{1.4,-1.620830},{1.5,-1.479430},{1.6,-1.260000},{1.7,-0.965395},{1.8,-0.565015}, {1.9,-0.140990}};
	int filas = 7; 
	FILE *file;
	file = fopen("tabla.txt", "r");
	if (file == NULL) {
		printf("Error al abrir el archivo.\n");
		exit(0);
	}
	
	// Leer los valores de x y f(x) desde el archivo
	for (int i = 0; i < filas; i++) {
		if (fscanf(file, "%lf %lf", &m[i][0], &m[i][1]) != 2) {
			printf("Error al leer los datos del archivo.\n");
			fclose(file);
			exit(0);
		}
	}
	
	// Cerrar el archivo despu�s de leer los datos
	fclose(file);
	int n = filas - 1;
	bool flag = sonEquidistantes(m,filas);
	if(true){
		double suma = m[0][1] + m[n][1];
		double h = (m[1][0]-m[0][0])/3;
		for(int i = 1 ; i < n-1 ; i++){
			suma+= 4*m[i][1] + 2*m[i+1][1];
		}
		double integral = h*suma;
		printf("\nEl resultado de la integral es: %lf",integral);
	}else{
		printf("\nLos puntos no son equidistantes");
		return;
	}
}





bool sonEquidistantes(double arreglo[FILAS][2], int filas){//retorna verdadero si son equidistantes
	
	double diferencia = arreglo[1][0] - arreglo[0][0];
	for (int i = 0; i < filas - 1; i++) {
		if ((arreglo[i + 1][0] - arreglo[i][0]) != diferencia) {
			return false;
		}
	}
	return true;
}
