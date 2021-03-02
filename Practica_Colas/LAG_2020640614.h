#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifndef _FILA_
#define _FILA_

typedef struct _Nodo {
    char nombre[20];
    char numCuenta[20];
    int saldo;
    struct _Nodo *siguiente;
}Nodo;

Nodo *asignarMemoria(char *n, char *nc, int s) {
    Nodo *nuevo;
    nuevo = (Nodo *) malloc(sizeof(Nodo));
    strcpy(nuevo -> nombre, n);
    strcpy(nuevo -> numCuenta, nc);
    nuevo -> saldo = s;
    nuevo -> siguiente = NULL;

    return nuevo;
}

Nodo *insert(Nodo *frente, char *n, char *nc, int s) {
    Nodo *nuevo;
    Nodo *aux;
    nuevo = asignarMemoria(n, nc, s);
    if(frente == NULL) {
        frente = nuevo;
    } else {
        aux = frente;
        while(aux -> siguiente != NULL) {
            aux = aux -> siguiente;
        }
        aux -> siguiente = nuevo;
    }

    return frente;
}

Nodo *delete(Nodo *frente) {
    Nodo *aux;
    aux = frente;
    if(frente != NULL) {
        frente = frente -> siguiente;
        free(aux);
    }
    return frente;
}

void mostrarFila(Nodo *frente) {
    if(frente == NULL) {
        printf("\nLa FILA esta vacia...\n");
    } else {
        while(frente != NULL) {
            printf("\n%s\t%s\t%d", frente -> nombre, frente -> numCuenta, frente -> saldo);
            frente = frente -> siguiente;
        }
    }
}

Nodo *leerArchivo(Nodo *frente, char *ruta) {
    FILE *archivo;
    char cadena[20], x[20];
	int y;

	archivo = fopen(ruta, "r");
	if(archivo == NULL) {
        printf("Error al abrir el archivo...\n");
        exit(-1);
	} else {
        while(!feof(archivo)) {
            fscanf(archivo, "%s %s %d", cadena, x, &y);
            frente = insert(frente, cadena, x, y);
        }
        fclose(archivo);
	}
    return frente;
}

void imprimirArchivo(Nodo *c, Nodo *d) {
    FILE *archivo;
    archivo = fopen("cobros.txt", "w");
    if(archivo != NULL) {
        while(c != NULL) {
            fprintf(archivo, "%s\t%s\t%d\n", c -> nombre, c -> numCuenta, c -> saldo);
            c = c -> siguiente;
        }
        fclose(archivo);
    }
    archivo = fopen("depositos.txt", "w");
    if(archivo != NULL) {
        while(d != NULL) {
            fprintf(archivo, "%s\t%s\t%d\n", d -> nombre, d -> numCuenta, d -> saldo);
            d = d -> siguiente;
        }
        fclose(archivo);
    }
}

#endif
