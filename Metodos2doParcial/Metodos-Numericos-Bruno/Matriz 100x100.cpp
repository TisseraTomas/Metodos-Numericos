#include <iostream>
using namespace std;
#define N 101  // Tamaño de la matriz
void guardarMatrizEnArchivo(float matriz[100][N], const char *nombreArchivo) {
	FILE *archivo = fopen(nombreArchivo, "w");  // Abre el archivo en modo escritura ("w")
	
	if (archivo == NULL) {
		printf("No se pudo abrir el archivo.\n");
		return;
	}
	
	// Recorrer la matriz y escribir los valores en el archivo
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < N; j++) {
			fprintf(archivo, "%.1f ", matriz[i][j]);  // Escribe cada elemento seguido de un espacio
		}
		fprintf(archivo, "\n");  // Nueva línea al final de cada fila
	}
	
	fclose(archivo);  // Cerrar el archivo
	printf("Matriz guardada en %s correctamente.\n", nombreArchivo);
}
int main(int argc, char *argv[]) {
	
	float m[100][101]= {0};
	
	
	for (int i = 0; i < 100; i++) {
		if (i > 0) {
			m[i][i-1] = 1;  // Subdiagonal
		}
		if (i < 99) {
			m[i][i+1] = 1;  // Superdiagonal
		}
		m[i][i] = 2;  // Diagonal principal
	}
	
	m[0][100]= 4.5;
	for (int i = 1; i < 99; i++) {
		m[i][100] = 6;  // Valores intermedios de los términos independientes
	}
	m[99][100]= 4.5;
	
	/*for (int i = 0; i < 100; i++) {
		for (int j = 0; j < N; j++) {
			printf("%.1f ", m[i][j]);  // Escribe cada elemento seguido de un espacio
		}
		printf("\n");  // Nueva línea al final de cada fila
	}*/
	
	guardarMatrizEnArchivo(m, "matriz100x100.txt");
	return 0;
}

