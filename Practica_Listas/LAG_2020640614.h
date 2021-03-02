#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _LISTA_ENLA_H_
#define _LISTA_ENLA_H_

typedef struct _Nodo {
	char modelo[20];
	char color[20];
	char placa[20];
	struct _Nodo *siguiente;
	struct _Nodo *anterior;
}Nodo;

Nodo *asignarMemoria(char *m, char *c, char *p) {
	Nodo *nuevo;
	nuevo = (Nodo *) malloc(sizeof(Nodo));
	strcpy(nuevo -> modelo, m);
	strcpy(nuevo -> color, c);
	strcpy(nuevo -> placa, p);
	nuevo -> siguiente = NULL;
    nuevo -> anterior = NULL;
	return nuevo;
}

int contarElementos(Nodo *frente) {
	int c = 0;
	if(frente == NULL) {
		printf("\nLa FILA esta vacia...\n");
	} else {
		while(frente != NULL) {
			frente = frente -> siguiente;
			c++;
		}
	}
	return c;
}

Nodo *insertInicial(Nodo *frente, char *m, char *c, char *p) {
	Nodo *nuevo;
	nuevo = asignarMemoria(m, c, p);
	if(frente != NULL) {
		nuevo -> siguiente = frente;
		frente -> anterior = nuevo; ////////////
	}

	return nuevo;
}

Nodo *insertFinal(Nodo *frente, char *m, char *c, char *p) {
    Nodo *nuevo;
    Nodo *aux;
    nuevo = asignarMemoria(m, c, p);
    if(frente == NULL) {
        frente = nuevo;
    } else {
        aux = frente;
        while(aux -> siguiente != NULL) {
            aux = aux -> siguiente;
        }
        aux -> siguiente = nuevo;
        nuevo -> anterior = aux; ///////
    }

    return frente;
}

/**
    Utilice el ordenamiento por Selección Directa
    Para la función 'ordenamiento' me apoye bastante de la siguiente bibliografía:
    https://www.geeksforgeeks.org/iterative-selection-sort-for-linked-list/
**/
void ordenamiento(Nodo *frente) {
    Nodo *temp = frente;
    Nodo *valorMin = NULL;
    Nodo *aux = NULL;

    while(temp != NULL) {
        valorMin = temp;
        aux = temp -> siguiente;
        while(aux != NULL) {
            if(valorMin -> color[0] > aux -> color[0]) { // Utilice codigo ASCII para comparar la primera letra del primer elemento
                valorMin = aux;                          // de la lista con la primera letra del elemento siguiente de la lista
            // En valorMin almaceno la dirección donde se encuentra el nodo que contiene el color con menor orden alfabetico
            }
            aux = aux -> siguiente;
        }

        // Almaceno los datos del nodo "menor" en variables para poder hacer el intercambio de datos
        char x[20], y[20], z[20];

        strcpy(x, temp -> modelo);
        strcpy(y, temp -> color);
        strcpy(z, temp -> placa);

        // Intercambio de datos
        strcpy(temp -> modelo, valorMin -> modelo);
        strcpy(temp -> color, valorMin -> color);
        strcpy(temp -> placa, valorMin -> placa);

        strcpy(valorMin -> modelo, x);
        strcpy(valorMin -> color, y);
        strcpy(valorMin -> placa, z);

        temp = temp -> siguiente;
    }
}

void mostrar(Nodo *frente) {
    if(frente == NULL) {
        printf("\nLa FILA esta vacia...");
    } else {
        while(frente != NULL) {
            printf("\nModelo: %s\tColor: %s\tPlaca: %s", frente -> modelo, frente -> color, frente -> placa);
            frente = frente -> siguiente;
        }
    }
}

void mostrarAlReves(Nodo *frente) {
    if(frente == NULL) {
        printf("\nLa FILA esta vacia...");
    } else {
        while(frente -> siguiente != NULL) {
            frente = frente -> siguiente;
        }
        while(frente != NULL) {
            printf("\nModelo: %s\tColor: %s\tPlaca: %s", frente -> modelo, frente -> color, frente -> placa);
            frente = frente -> anterior;
        }
    }
}

Nodo *leerArchivo(Nodo *frente, char *ruta) {
    FILE *archivo;
    char modelo[20], color[20], placa[20];

    archivo = fopen(ruta, "r");
	if(archivo == NULL) {
        printf("Error al abrir el archivo...\n");
        exit(-1);
	} else {
        while(!feof(archivo)) {
            fscanf(archivo, "%s %s %s", modelo, color, placa);
            frente = insertFinal(frente, modelo, color, placa);
        }
        fclose(archivo);
	}

    return frente;
}

void imprimirArchivo(Nodo *frente) {
    FILE *archivo;
    archivo = fopen("XXX.txt", "w");
    if(archivo != NULL) {
        while(frente != NULL) {
            fprintf(archivo, "%s\t%s\t%s\n", frente -> modelo, frente -> color, frente -> placa);
            frente = frente -> siguiente;
        }
    fclose(archivo);
    }
}

#endif
