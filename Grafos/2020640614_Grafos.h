#ifndef GRAFOS_H_INCLUDED
#define GRAFOS_H_INCLUDED
#include <string.h>

typedef struct _Nodos {
    char *dato; // cadena de caracteres
    struct _Nodos *siguiente;
} Nodos;

typedef struct _Adyacencias {
    Nodos *origen;
    Nodos *destino;
    int coste;
    struct _Adyacencias *siguiente;
} Adyacencias;

typedef struct _Grafo {
    Nodos *nodos;
    Adyacencias* adyacencias;
} Grafo;

typedef struct _ListaD {
    Nodos *nodo;
    int coste;
    struct _ListaD *siguiente;
} ListaD;

typedef struct _Lista {
    Nodos *origen;
    ListaD *destinos;
    struct _Lista *siguiente;
} Lista;

Nodos *crearNodo(char* d) {
    Nodos *nuevo = (Nodos*) malloc(sizeof(Nodos));
    nuevo->dato = (char*) malloc(sizeof(char)*(strlen(d)+1));
    strcpy(nuevo->dato, d);
    nuevo->siguiente = NULL;
    return nuevo;
}

Nodos *insertNodo(Nodos *lista, char *d) {
    Nodos* nuevo = crearNodo(d);
    if(lista == NULL)
        return nuevo;
    Nodos *aux = lista;
    if(strcmp(aux->dato, d) > 0) {
        nuevo->siguiente = aux;
        return nuevo;
    } else if(aux->siguiente == NULL){
        aux->siguiente = nuevo;
        return aux;
    } else {
        while(strcmp(aux->siguiente->dato, d) < 0) {
            aux = aux->siguiente;
            if(aux->siguiente == NULL)
                break;
        }
        nuevo->siguiente = aux->siguiente;
        aux->siguiente = nuevo;
        return lista;
    }
}

void mostrar(Nodos *lista) {
    if(lista == NULL)
        printf("La lista esta vacia...\n");
    else {
        while(lista != NULL) {
            printf("%s\n", lista->dato);
            lista = lista->siguiente;
        }
    }
}

Nodos *borrar(Nodos *lista, char* d) {
    if(lista == NULL)
        return lista;
    Nodos *aux = lista;
    if(strcmp(d,aux->dato) == 0)
    {
        aux = aux->siguiente;
        free(lista);
        return aux;
    }
    while (aux->siguiente != NULL)
    {
        if(strcmp(d, aux->siguiente->dato) == 0)
        {
            Nodos *borrar = aux->siguiente;
            aux->siguiente = aux->siguiente->siguiente;
            free(borrar);
        }
        aux = aux->siguiente;
    }
    return lista;
}

Nodos *borrarFila(Nodos* lista) {
    while(lista != NULL)
    {
        lista = borrar(lista, lista->dato);
    }
    return NULL;
}

// Busca un nodo con la palabra ingresada
Nodos *getNodo(Nodos* lista, char* dato) {
    Nodos *aux = lista;
    while(aux != NULL) {
        if(strcmp(aux->dato,dato) == 0) {
            return aux;
        }
        aux = aux->siguiente;
    }
    printf("El nodo \"%s\" no existe\n", dato);
    return NULL;
}

int contains(Nodos* lista, char *dato) {
    Nodos *aux;
    for(aux=lista; aux!=NULL; aux=aux->siguiente) {
        if(strcmp(aux->dato, dato) == 0)
            return 1;
    }
    return 0;
}

int existe(Nodos* lista, Nodos* nodo) {
    Nodos *aux = lista;
    while(aux != NULL) {
        if(aux == nodo)
            return 1;
        aux = aux->siguiente;
    }
    return 0;
}

int getIndexNodos(Nodos *lista, Nodos *nodo) {
    if(existe(lista, nodo) == 0)
        return -1;
    int i=0;
    Nodos *aux = lista;
    while(aux != nodo) {
        i++;
        aux = aux->siguiente;
    }
    return i;
}

int sizeNodos(Nodos *lista) {
    int i=0;
    Nodos *aux = lista;
    while(aux != NULL) {
        i++;
        aux = aux->siguiente;
    }
    return i;
}

Adyacencias* crearAdyacencia(Nodos* origen, Nodos* destino, int coste) {
    Adyacencias* nuevo = (Adyacencias*) malloc(sizeof(Adyacencias));
    nuevo->origen = origen;
    nuevo->destino = destino;
    nuevo->coste = coste;
    nuevo->siguiente = NULL;

    return nuevo;
}

int cmpAdyacencias(Adyacencias* ad1, Adyacencias* ad2) // Se llama en addAdyacencia
{
    if(ad1->origen == ad2->origen && ad1->destino == ad2->destino)
        return 1;
    else if(ad1->origen == ad2->destino && ad1->destino == ad2->origen)
        return -1; // YA HAY ADYACENCIA
    else
        return 0;
}

int existeEn(Adyacencias* ad, Adyacencias* ads, int dirigido) // Se llama en addAdyacencia
{
    Adyacencias *aux = ads;
    while(aux != NULL)
    {
        if(cmpAdyacencias(aux, ad) == 1)
            return 1;
        else if((cmpAdyacencias(aux,ad) == -1) && (dirigido == 0))
            return 1;
        aux = aux->siguiente;
    }
    return 0;
}

Adyacencias *addArista(Adyacencias *lista, Nodos *origen, Nodos *destino, int coste) {
    Adyacencias* nuevo = crearAdyacencia(origen, destino, coste);
    if(lista == NULL)
        return nuevo;
    Adyacencias *aux = lista;
    while(aux->siguiente != NULL) {
        aux = aux->siguiente;
    }
    aux->siguiente = nuevo;
    return lista;
}

Adyacencias *borrarAdyacencias(Adyacencias* lista) {
    Adyacencias *aux;
    while(lista != NULL) {
        aux = lista;
        lista = lista->siguiente;
        free(aux);
    }
    return NULL;
}

int **crearMatriz(Grafo grafo) {
    Nodos *nodo = grafo.nodos;
    Adyacencias *adyacencia = grafo.adyacencias;
    int cantNodos = sizeNodos(nodo);
    int **matriz = (int**) malloc(sizeof(int*) * cantNodos);
    if (matriz == NULL) {
		puts("\nError al reservar memoria para los punteros");
		exit(-1);
	}
    int *aptr = (int *) malloc(cantNodos * cantNodos * sizeof(int));
    if (aptr == NULL) {
		puts("\nError al reservar memoria para el arreglo completo.");
		exit(-1);
	}
	for (int k = 0; k < cantNodos; k++) {
		matriz[k] = aptr + (k * cantNodos);
	}
	for(int i = 0; i < cantNodos; i++) {
        for(int j = 0; j < cantNodos; j++) {
            matriz[i][j] = 0;
        }
    }
    int i,j;
    Adyacencias* aux = adyacencia;
    while(aux != NULL) {
        i = getIndexNodos(nodo, aux->origen);
        j = getIndexNodos(nodo, aux->destino);
        if(i == -1 || j == -1)
            continue;
        matriz[i][j] = aux->coste;
        aux = aux->siguiente;
    }
    return matriz;
}

int **borrarMatriz(int** matriz, int nNodos) {
    int i;
    for(i=0; i<nNodos; i++) {
        free(matriz[i]);
    }
    free(matriz);
    return NULL;
}

Lista *crearLA(Nodos *nodos) { //Lista de Adyacencia
    if(nodos == NULL)
        return NULL;
    Lista *nuevo = (Lista*) malloc(sizeof(Lista));
    nuevo->origen = nodos;
    nuevo->destinos = NULL;
    nuevo->siguiente = crearLA(nodos->siguiente);
    return nuevo;
}

ListaD *crearDestino(Nodos *nodo, int coste) {
    ListaD *nuevo = (ListaD*) malloc(sizeof(ListaD));
    nuevo->coste = coste;
    nuevo->nodo = nodo;
    nuevo->siguiente = NULL;
    return nuevo;
}

ListaD *addDestino(ListaD *destinos, Nodos *dest, int coste) {
    ListaD *nuevo = crearDestino(dest, coste);
    if(destinos == NULL) {
        return nuevo;
    }
    ListaD* aux = destinos;
    if(strcmp(aux->nodo->dato, dest->dato) > 0) {
        nuevo->siguiente = aux;
        return nuevo;
    }
    if(aux->siguiente == NULL) {
        aux->siguiente = nuevo;
        return aux;
    }
    while(strcmp(aux->siguiente->nodo->dato, dest->dato) < 0) {
        aux = aux->siguiente;
        if(aux->siguiente == NULL) {
            break;
        }
    }
    nuevo->siguiente = aux->siguiente;
    aux->siguiente = nuevo;
    return destinos;
}

Lista *setAds(Lista* lista, Adyacencias *ads) {
    Lista *auxlista = lista;
    Adyacencias *auxad;
    while(auxlista != NULL) {
        auxad = ads;
        while(auxad != NULL) {
            if(auxad->origen == auxlista->origen){
                auxlista->destinos = addDestino(auxlista->destinos, auxad->destino, auxad->coste);
            }
            auxad = auxad->siguiente;
        }
        auxlista = auxlista->siguiente;
    }
    return lista;
}

ListaD *borrarDestinos(ListaD* lista) {
    ListaD *aux;
    while(lista != NULL) {
        aux = lista;
        lista = lista->siguiente;
        free(aux);
    }
    return lista;
}

Lista *borrarLista(Lista* lista) {
    Lista *aux;
    while(lista != NULL) {
        aux = lista;
        lista = lista->siguiente;
        aux->destinos = borrarDestinos(aux->destinos);
        free(aux);
    }
    return lista;
}

Lista *crearLista(Grafo grafo) {
    Lista *lista = crearLA(grafo.nodos);
    lista = setAds(lista, grafo.adyacencias);
    return lista;
}

#endif
