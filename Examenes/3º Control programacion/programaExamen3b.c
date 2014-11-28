//Ejercicio 7: (4 puntos) Crear un programa que lea del fichero creado anteriormente (�biblioteca.bin�), de manera que almacene los datos en un array de estructuras creado de forma din�mica.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//a) CalculaElementos. Esta funci�n se encargar� e calcular cu�ntas estructuras hay almacenadas en el fichero, en funci�n del tama�o del fichero.
int CalculaElementos(File *pf);
//b) ReservaMemoria ser� la funci�n encargada de reservar memoria din�mica para el array des estructuras de tipo �FichaLibro�.
void ReservaMemoria(FichaLibro **d, int cuantos);
//c) LeerDatos ser� la funci�n encargada de leer los datos de las estructuras del fichero y almacenarlas en el array des estructuras creado anteriormente.
void LeerDatos(FichaLibro *datos, int cuantos, File *pf);
//d) OrdenarArray ser� la funci�n encargada de ordenar el array de estructuras en orden alfab�tico por el campo autor de las estructuras. Se puede utilizar cualquiera de los m�todos de ordenaci�n vistos en clase.

typedef struct EstructuraFichaLibro {
	char titulo[256];
	char autor[256];
	char ISBN[256];
	char Estante[256];
	int prestado;
	char cliente[256];
} FichaLibro;

int main() {
	FILE *pf;
	FichaLibro *datos;
	int cuantos = 0;

	pf = fopen("biblioteca.bin","rb");
	cuantos = calculaElementos();
	ReservaMemoria(&datos, cuantos);
	LeerDatos(datos, cuantos, pf);
	// OrdenarArray(datos, cuantos, pf);
	free(datos);
	fclose(pf);
	return 1;
}

int CalculaElementos(File *pf) {
	int n;

	n = fseek(pf, 0, SEEK:END);
	n = n/sizeof(FichaLibro);
	return n;
}

void ReservaMemoria(FichaLibro **d, int cuantos) {
	(*d) = (FichaLibro *)malloc( cuantos*sizeof(FichaLibro) );
}

void LeerDatos(FichaLibro *datos, int cuantos, File *pf) {
	fread(datos, sizeof(FichaLibro), cuantos, pf);
}
