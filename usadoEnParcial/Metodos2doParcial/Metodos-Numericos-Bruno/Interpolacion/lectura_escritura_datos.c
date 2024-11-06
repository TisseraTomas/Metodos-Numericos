#include <stdio.h>


	FILE *fp;
	char ch;
	
	// Abre el archivo
	fp = fopen("tabla.dat", "r");
	if (fp == NULL) {
		puts("No se puede abrir el archivo");
		return 1;
	}
	
	// Contador de filas
	int filas = 0;
	char c;
	
	// Contar líneas en el archivo para determinar el número de filas
	while ((c = fgetc(fp)) != EOF) {
		if (c == '\n') {
			filas++;
		}
	}
	
	printf("Número de filas = %i\n", filas);
	
	// Cerrar y reabrir el archivo para resetear el puntero
	fclose(fp);
	fp = fopen("tabla.dat", "r");
	
	// Inicializar los arreglos para almacenar los datos
	double x[filas];
	double y[filas];
	
	// Leer datos en los arreglos x e y
	int i;
	for (i = 0; i < filas; i++) {
		if (fscanf(fp, "%lf %lf", &x[i], &y[i]) != 2) {
			printf("Error al leer los datos en la fila %d\n", i + 1);
			break;
		}
	}
	
	fclose(fp);
	
	// Imprimir la tabla para verificar los datos leídos
	printf("\nLOS ELEMENTOS DE LA TABLA SON:\n");
	for (i = 0; i < filas; i++) {
		printf("%lf \t %lf\n", x[i], y[i]);
	}
	
	return 0; 

