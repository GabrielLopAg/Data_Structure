#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#ifndef _HUFFMAN_DECO_H_
#define _HUFFMAN_DECO_H_
#define TAM_MAX 400

typedef struct _Nodo {
	char dato;
	int frecuencia;
	int flag;
	struct _Nodo *siguiente, *anterior;
	struct _Nodo *izquierda, *derecha;
}Nodo;

Nodo *asignarMemoria(char d, int f) {
	Nodo *nuevo;
	nuevo = (Nodo *) malloc(sizeof(Nodo));
	nuevo -> dato = d;
	nuevo -> frecuencia = f;
	nuevo -> flag = 0;
	nuevo -> siguiente = NULL;
    nuevo -> anterior = NULL;
    nuevo -> izquierda = NULL;
    nuevo -> derecha = NULL;
	return nuevo;
}

Nodo *insertFinal(Nodo *frente, char d, int f) {
    Nodo *nuevo;
    Nodo *aux;
    nuevo = asignarMemoria(d, f);
    if(frente == NULL) {
        frente = nuevo;
    } else {
        aux = frente;
        while(aux -> siguiente != NULL) {
            aux = aux -> siguiente;
        }
        aux -> siguiente = nuevo;
        nuevo -> anterior = aux;
    }

    return frente;
}

void mostrar(Nodo *frente) {
    if(frente == NULL) {
        printf("\nLa FILA esta vacia...");
    } else {
        while(frente != NULL) {
            printf("\nDato: %c Fre: %d", frente->dato, frente->frecuencia);
            frente = frente -> siguiente;
        }
    }
}

char *binarioToDecimal(int num) {
    int i = 0, j = 0;
    char codigo[15] = "";
    char *copia = malloc(10);
    while(num != 0) {
        if(num % 2 == 0) {
            codigo[i] = '0';
        }
        if(num % 2 == 1) {
            codigo[i] = '1';
        }
        num = num/2;
        i++;
    }
    int len = strlen(codigo);
    while(len % 7 != 0) {
        strcat(codigo, "0");
        len++;
    }
    for(i = len-1 ; i >= 0 ; i--, j++) {
        copia[j] = codigo[i];
    }

    return copia;
}

char *leerArchivoBin(char *ruta) {
    FILE *archivo;
    int decimales[60], inicio, i;
    char *aux = malloc(TAM_MAX);
    char binarios[TAM_MAX] = "";
    archivo = fopen(ruta, "rb");
    if(archivo == NULL) {
        printf("Error al abrir el archivo...\n");
        exit(-1);
	} else {
        fread(&inicio, sizeof(int), 1, archivo);
        fread(decimales, sizeof(int), inicio, archivo);

        fclose(archivo);
    }
    for(i = 0 ; i < inicio ; i++) {
        //printf("%d ", decimales[i]);
        strcat(binarios, binarioToDecimal(decimales[i]));
    }
    strcpy(aux, binarios);
    return aux;
}

Nodo *leerArchivoTxt(Nodo *frente, char *ruta) {
    FILE *archivo;
    char letra;
    int frecuencia;

    archivo = fopen(ruta, "r");
    if(archivo == NULL) {
        printf("Error al abrir el archivo...\n");
        exit(-1);
	} else {
        while(!feof(archivo)) {
            fscanf(archivo, "%c %d ", &letra, &frecuencia);
            frente = insertFinal(frente, letra, frecuencia);
        }
        fclose(archivo);
    }
    return frente;
}

Nodo *crearArbol(Nodo *frente) {
    Nodo *aux, *aux2, *raiz;
    aux = frente->siguiente;

    while(aux) {
        if(aux->dato == '*') {
            aux2 = aux->anterior;
            while(aux2 != NULL) {
                if(aux2->flag == 0) {
                    aux2->flag = 1;
                    if(aux->derecha == NULL) {
                        aux->derecha = aux2;
                        continue;
                    }
                    if(aux->izquierda == NULL) {
                        aux->izquierda = aux2;
                        break;
                    }
                }
                aux2 = aux2->anterior;
            }
        }
        raiz = aux;
        aux = aux->siguiente;
    }

    return raiz;
}

void postOrder(Nodo *raiz) {
    if(raiz != NULL) {
        postOrder(raiz -> izquierda);
        postOrder(raiz -> derecha);
        printf("%c %d ", raiz -> dato, raiz -> frecuencia);
    }
}

void imprimirFrase(char *frase) {
    FILE *archivo;
    archivo = fopen("fraseF.txt", "w");
    if(archivo != NULL)
        fprintf(archivo, "%s", frase);

    fclose(archivo);
}

void decodificar(Nodo *raiz, char *numBinarios) {
    Nodo *aux = raiz;
    char frase[TAM_MAX];
    int i = 0, len = 0;
    for(i = 0 ; i < strlen(numBinarios) ; i++) {
        if(numBinarios[i] == '0') {
            aux = aux->izquierda;
        }
        if(numBinarios[i] == '1') {
            aux = aux->derecha;
        }
        if(aux->dato != '*') {
            //printf("%c", aux->dato);
            frase[len] = aux->dato;
            len++;
            aux = raiz;
        }
    }
    printf("\nFrase: %s\n\n", frase);
    imprimirFrase(frase);
}

#endif
